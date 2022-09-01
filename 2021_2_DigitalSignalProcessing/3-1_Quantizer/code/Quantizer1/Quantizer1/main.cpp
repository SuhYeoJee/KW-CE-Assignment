#include <iostream>
#include <direct.h> //_mkdir
using namespace std;

#define inputFile		"./input/Lenna_512x512_original.raw"
#define outputFile		"./output/Lenna_512x512_code"
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

	//����ȭ
	int gap = (int)pow(2, 8 - N); //���� ũ�� ���ϱ�
	for (int i = 0; i < xSize; i++) {
		for (int j = 0; j < ySize * 3; j++)
			image[i][j] /= gap;
	}

	//��� ����
	_mkdir("./output"); //output ���丮 ����
	if (fopen_s(&fp, outputFile, "wb")) {
		cout << "[error]Can't open outputFile" << endl;
		return -1;
	}

	unsigned int buff = 0, temp;
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

	//�����Ҵ� ����
	for (int i = 0; i < xSize; i++) delete[] image[i];
	delete[] image;

	return 0;
}