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
	FILE* fp;

	//image �����Ҵ�
	unsigned char** image = new unsigned char* [xSize];
	for (int i = 0; i < xSize; i++) image[i] = new unsigned char[ySize * 3];

	//���� ���� �б�	
	if (fopen_s(&fp, inputFile, "rb")) {
		cout << "[error]Can't open inputFile" << endl;
		return -1;
	}
	for (int i = 0; i < xSize; i++)
		fread(image[i], sizeof(unsigned char), ySize * 3, fp);
	fclose(fp);

	////////////////////////////////////////////////////////////////////////////

	//��
	int p[256] = { 0};
	for (int i = 0; i < xSize; i++) {
		for (int j = 0; j < ySize*3; j++) {
			p[(int)image[i][j]]++;
		}
	}

	//�ʱ� di ���
	int gap = (int)pow(2, 8 - N); //���� ũ�� ���ϱ�
	int L = (int)pow(2, N)+1;
	int* d = new int[L];
	int* r = new int[L];
	unsigned int temp = 0, temp2=1;

	for (int i = 0; i < L; i++) { //di �ʱⰪ = �յ�
		d[i] = temp;	//d[0] = 0(min)	d[L-1] = 256(MAX)
		temp += gap;
	}
	r[0] = 0;	//r0 ������

	////////////////////////////////////////////////////////////////////////////

	//ri�� di�� �ݺ� ���
	while(temp2){
		//ri - ������ ��� ������ ��հ�
		for (int i = 1; i < L; i++) {
			temp = 0; temp2 = 0;
			for (int j = d[i-1]; j < d[i]; j++) {
				temp += j * p[j];	//���� �� * Ȯ��
				temp2 += p[j];		//Ȯ��
			}
			r[i] = (temp2 == 0) ? d[i-1]: round((double)temp / temp2); //Ȯ���� 0�� ��� d[i-1]�� ���� ���
		}

		temp2 = 0; //iteration
		//di - ri�� ri+1�� ��հ�
		for (int i = 1; i < L-1; i++) {
			temp = d[i];
			d[i] = round(((double)r[i] + r[i + 1]) / 2);
			if (temp != d[i]) temp2++;
		}
	}

	////////////////////////////////////////////////////////////////////////////

	//�̹��� ���� ����
	for (int i = 0; i < xSize; i++) {
		for (int j = 0; j < ySize * 3; j++) { //3ä��, ��� �ȼ��� ���� ����
			temp = image[i][j];
			for (int u = 1; u < L; u++) {
				if (d[u] > temp) {
					image[i][j] = u-1;	// u: 0~L-2
					break;
				}
			}
		}
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
			temp = image[x][y++];
			space -= N;
			temp <<= space;
			buff += temp;

			//���� �ȼ�
			if (y >= ySize * 3) {
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
	fwrite(r, sizeof(int), L, fp);
	fclose(fp);


	//�����Ҵ� ����
	for (int i = 0; i < xSize; i++) delete[] image[i];
	delete[] image;

	return 0;
}