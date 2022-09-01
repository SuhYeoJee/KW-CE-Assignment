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
	FILE* fp;

	//image �����Ҵ�
	unsigned char** image = new unsigned char* [xSize];
	for (int i = 0; i < xSize; i++) image[i] = new unsigned char[ySize * 3];

	////////////////////////////////////////////////////////////////////////////

	//����ȭ �ڵ� �б�
	if (fopen_s(&fp, inputFile, "rb")) {
		cout << "[error]Can't open inputFile" << endl;
		return -1;
	}

	unsigned int buff = 0, temp;
	int space = 32;
	unsigned char mask = 255>>(8-N);
	for (int i = 0; i < xSize; i++) {
		for (int j = 0; j < ySize*3; j++) {
			//����ä���
			while (space >= 8) {
				temp = fgetc(fp);
				space -= 8;
				temp <<= space;
				buff += temp;
			}
			//�ȼ��� �� ����
			image[i][j] = (buff >> (32 - N))&(mask);
			buff <<= N;
			space += N;
		}
	}
	fclose(fp);

	//�ڵ�� �б�
	int L = (int)pow(2, N) + 1;
	int* r = new int[L];	//r0 ������

	if (fopen_s(&fp, codebookFile, "rb")) {
		cout << "[error]Can't open codebookFile" << endl;
		return -1;
	}
	fread(r, sizeof(int), L, fp);
	fclose(fp);

	////////////////////////////////////////////////////////////////////////////

	//������ȭ
	int u;
	for (int i = 0; i < xSize; i++) {
		for (int j = 0; j < ySize * 3; j++) {
			u = image[i][j]+1;	// 1 ~ L-1
			image[i][j] = r[u];
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
		fwrite(image[i], sizeof(unsigned char), ySize * 3, fp);
	fclose(fp);

	//�����Ҵ� ����
	for (int i = 0; i < xSize; i++) delete[] image[i];
	delete[] image;

	return 0;
}