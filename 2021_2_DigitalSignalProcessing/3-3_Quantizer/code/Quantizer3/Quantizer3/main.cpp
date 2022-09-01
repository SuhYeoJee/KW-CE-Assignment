#include <iostream>
#include <direct.h> //_mkdir
using namespace std;

#define inputFile		"./input/Lenna_512x512_original.raw"
#define outputFile		"./output/Lenna_512x512_code"
#define codebookFile	"./output/Lenna_512x512_codebook"
#define xSize	512
#define ySize	512
#define N	7	// USE N bit

int main(void) {
	const int y2Size = ySize * 2;
	const int y3Size = ySize * 3;
	FILE* fp;

	//image �����Ҵ�	//code �����Ҵ�
	unsigned char** image = new unsigned char* [xSize];
	unsigned char** code = new unsigned char* [xSize];
	for (int i = 0; i < xSize; i++) {
		image[i] = new unsigned char[y3Size];
		code[i] = new unsigned char[ySize];
	}

	//���� ���� �б�	
	if (fopen_s(&fp, inputFile, "rb")) {
		cout << "[error]Can't open inputFile" << endl;
		return -1;
	}
	for (int i = 0; i < xSize; i++)
		fread(image[i], sizeof(unsigned char), y3Size, fp);
	fclose(fp);

	////////////////////////////////////////////////////////////////////////////
	//�ʱ� 3���� ���� ����
	//image[i][j], image[i][ysize+j], image[i][y2size+j] �� ���ͷ� ���� (R,G,B)
	int vSize = (int)pow(2, N); //2^N���� 3���� ����
	int gap = xSize / vSize;
	unsigned int temp1 = 0;

	unsigned char** v = new unsigned char*[vSize];
	for (int i = 0; i < vSize; i++) {
		v[i] = new unsigned char[3];
		v[i][0] = temp1;
		v[i][1] = temp1;
		v[i][2] = temp1;
		temp1 += gap;
	}

	////////////////////////////////////////////////////////////////////////////
	// ����ȭ
	int iter = 0; //�ݺ� Ƚ��
	while ((temp1!=0)&&(iter<20)) {
		cout << iter++ << "��° �ݺ�\t";
		// �׷� �з�
		for (int i = 0; i < xSize; i++) {
			for (int j = 0; j < ySize; j++) {
				int x = image[i][j],y = image[i][j + ySize],z = image[i][j + y2Size];
				unsigned int min = 0xFFFFFFFF;
				//x,y,z�� v[k][0], v[k][1], v[k][2]�� �Ÿ�
				//���� ����� ���� code[i][j] = k;
				for (int k = 0; k < vSize; k++) {
					unsigned int d = pow((x - v[k][0]), 2) + pow((y - v[k][1]), 2) + pow((z - v[k][2]), 2);
					if (d < min) {
						min = d;
						code[i][j] = k;
					}
				}
			}
		}

		//reconstructed vector �缳�� (�� �׷��� ��հ�)
		temp1 = 0; //x������ ����� ������ �� (�ݺ���������)
		for (int k = 0; k < vSize; k++) {
			int x = 0, y = 0, z = 0, c = 0;
			for (int i = 0; i < xSize; i++) {
				for (int j = 0; j < ySize; j++) {
					//k��° ���� �׷쿡 �ش��ϴ� ������ x,y,z���� ��
					if (code[i][j] != k) continue;
					x += image[i][j];
					y += image[i][j + ySize];
					z += image[i][j + y2Size];
					c++; //k��° ���� �׷쿡 �ش��ϴ� ������ ��
				}
			}
			if (c == 0) continue; //�׷쿡 �ش��ϴ� ���Ͱ� ���� ���
			if (v[k][0] != x / c) temp1 ++; //x������ ����� ������ �� (�ݺ���������)
			//k��° ���� �׷��� ��հ�
			v[k][0] = x / c;
			v[k][1] = y / c;
			v[k][2] = z / c;
		}
		cout << temp1 << endl;//x������ ����� ������ �� (�ݺ���������)
	}

	////////////////////////////////////////////////////////////////////////////

	//��� ����
	_mkdir("./output"); //output ���丮 ����
	if (fopen_s(&fp, outputFile, "wb")) {
		cout << "[error]Can't open outputFile" << endl;
		return -1;
	}

	unsigned int buff = 0;
	unsigned char ch;
	int space = 32; //���� ����� 
	int x = 0, y = 0;

	while (1) {
		//����� > N�� �� ���� ä���
		while ((space >= N) && (x < xSize)) {
			temp1 = code[x][y++];
			space -= N;
			temp1 <<= space;
			buff += temp1;

			//���� �ȼ�
			if (y >= ySize) {
				x++; y = 0;
				if (x >= xSize) { //��� �ȼ� ����
					space = 0;
				}
			}
		}
		//���۰� ������ �� 1byte��ŭ ���Ͽ� ����
		ch = buff >> (32 - 8);
		buff <<= 8;
		space += 8;
		fputc(ch, fp);

		//��� ���� ���� �Ϸ�
		if ((x >= xSize) && (space == 32)) break;
	}
	fclose(fp);


	//codebook����
	if (fopen_s(&fp, codebookFile, "wb")) {
		cout << "[error]Can't open codebookFile" << endl;
		return -1;
	}
	for (int i = 0; i < vSize; i++)
		fwrite(v[i], sizeof(unsigned char), 3, fp);
	fclose(fp);

	//�����Ҵ� ����
	for (int i = 0; i < xSize; i++) delete[] image[i], code[i];
	for (int i = 0; i < vSize; i++) delete[] v[i];
	delete[] image, code, v;
	return 0;
}