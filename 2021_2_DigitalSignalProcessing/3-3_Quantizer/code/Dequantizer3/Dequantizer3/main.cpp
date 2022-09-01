#include <iostream>
#include <direct.h> //_mkdir
using namespace std;

#define inputFile		"./input/Lenna_512x512_code"
#define codebookFile	"./input/Lenna_512x512_codebook"
#define outputFile		"./output/Lenna_512x512_reconstruct.raw"
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

	////////////////////////////////////////////////////////////////////////////

	//����ȭ �ڵ� �б�
	if (fopen_s(&fp, inputFile, "rb")) {
		cout << "[error]Can't open inputFile" << endl;
		return -1;
	}

	unsigned int buff = 0, temp;
	int space = 32;
	unsigned char mask = 255 >> (8 - N);
	for (int i = 0; i < xSize; i++) {
		for (int j = 0; j < ySize; j++) {
			//����ä���
			while (space >= 8) {
				temp = fgetc(fp);
				space -= 8;
				temp <<= space;
				buff += temp;
			}
			//�ȼ��� �� ����
			code[i][j] = (buff >> (32 - N)) & (mask);
			buff <<= N;
			space += N;
		}
	}
	fclose(fp);

	//�ڵ�� �б�
	int vSize = (int)pow(2, N);
	unsigned char** v = new unsigned char* [vSize];
	if (fopen_s(&fp, codebookFile, "rb")) {
		cout << "[error]Can't open codebookFile" << endl;
		return -1;
	}
	for (int i = 0; i < vSize; i++) {
		v[i] = new unsigned char[3];
		fread(v[i], sizeof(unsigned char), 3, fp);
	}
	fclose(fp);

	////////////////////////////////////////////////////////////////////////////

	//������ȭ
	int k;
	for (int i = 0; i < xSize; i++) {
		for (int j = 0; j < ySize; j++) {
			k = code[i][j];	// 1 ~ L-1
			image[i][j] = v[k][0];
			image[i][j+ySize] = v[k][1];
			image[i][j+y2Size] = v[k][2];
		}
	}

	////////////////////////////////////////////////////////////////////////////

	//������ȭ ��� ����
	_mkdir("./output");
	if (fopen_s(&fp, outputFile, "wb")) {
		cout << "[error]Can't open outputFile" << endl;
		return -1;
	}
	for (int i = 0; i < xSize; i++)
		fwrite(image[i], sizeof(unsigned char), y3Size, fp);
	fclose(fp);

	//�����Ҵ� ����
	for (int i = 0; i < xSize; i++) delete[] image[i], code[i];
	for (int i = 0; i < vSize; i++) delete[] v[i];
	delete[] image, code, v;

	return 0;
}