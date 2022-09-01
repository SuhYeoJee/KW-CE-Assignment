#include <iostream>
#include <direct.h> //_mkdir
using namespace std;

#define originalFile		"./input/Barbara_512x512_yuv400_8bit.raw"
#define coefficientFile		"./output/coefficient_Barbara_512x512_yuv400_8bit.raw"
#define reconstructedFile	"./output/reconstructed_Barbara_512x512_yuv400_8bit.raw"

#define inputSize	512

//////////////////
///	LL	//	HL	//
//////////////////
///	LH	//	HH	//
//////////////////

void haarInverse(int** coeff, int imgSize) {
	int** temp = new int* [imgSize];
	for (int i = 0; i < imgSize; i++) temp[i] = new int[imgSize];
	int halfSize = imgSize >> 1;

	for (int x = 0; x < imgSize; x++) {//vertical
		for (int y = 0; y < halfSize; y++) {
			temp[y << 1][x] = coeff[y][x] + coeff[y + halfSize][x];
			temp[(y << 1) + 1][x] = coeff[y][x] - coeff[y + halfSize][x];
		}
	}
	for (int y = 0; y < imgSize; y++) {//horizontal
		for (int x = 0; x < halfSize; x++) {
			coeff[y][x << 1] = temp[y][x] + temp[y][x + halfSize];
			coeff[y][(x << 1) + 1] = temp[y][x] - temp[y][x + halfSize];
		}
	}

	for (int i = 0; i < imgSize; i++) delete[] temp[i];
	delete[] temp;
	return;
}

void haarWavelet(unsigned char**output, int k, int** coeff, int imgSize) {
	int** temp = new int* [imgSize];
	for (int i = 0; i < imgSize; i++) temp[i] = new int[imgSize];
	int halfSize = imgSize >> 1;

	//0 ~ 255 -> -128 ~ 128
	//fixed point "0000_0000_00.00_0000"
	for (int y = 0; y < imgSize; y++) {//������ 2 tab ����
		for (int x = 0; x < halfSize; x++) {
			temp[y][x] = (coeff[y][x << 1] >> 1) + (coeff[y][(x << 1) + 1] >> 1); //Low-pass
			temp[y][x + halfSize] = (coeff[y][x << 1] >> 1) - (coeff[y][(x << 1) + 1] >> 1); //High-pass
		}
	}
	for (int x = 0; x < halfSize; x++) {//������ 2tab ����
		for (int y = 0; y < halfSize; y++) {
			coeff[y][x] = (temp[y << 1][x] >> 1) + (temp[(y << 1) + 1][x] >> 1);//LL
			coeff[y + halfSize][x] = (temp[y << 1][x] >> 1) - (temp[(y << 1) + 1][x] >> 1);//LH
			coeff[y][x + halfSize] = (temp[y << 1][x + halfSize] >> 1) + (temp[(y << 1) + 1][x + halfSize] >> 1);//HL
			coeff[y + halfSize][x + halfSize] = (temp[y << 1][x + halfSize] >> 1) - (temp[(y << 1) + 1][x + halfSize] >> 1);//HH
		}
	}

	//LH, HL, HH k-bit����ȭ
	int gap = (int)((255 + 128) << 6) / (2 << (k - 1));
	int gapLL = (int)((255) << 6) / (2 << (k-1));
	for (int x = 0; x < halfSize; x++) {
		for (int y = 0; y < halfSize; y++) {
			output[y][x] = coeff[y][x]/gapLL;
			output[y + halfSize][x] = (coeff[y+ halfSize][x] + 128) / gap;
			output[y][x + halfSize] = (coeff[y][x+ halfSize] + 128) / gap;
			output[y + halfSize][x + halfSize] = (coeff[y+ halfSize][x+ halfSize] + 128) / gap;
		}
	}

	for (int i = 0; i < imgSize; i++) delete[] temp[i];
	delete[] temp;
	return;
}


void MSE(unsigned char** ori, unsigned char** rec) {
	double sum = 0, MSE;

	for (int i = 0; i < inputSize; i++) {
		for (int j = 0; j < inputSize; j++)
			sum += pow(ori[i][j] - rec[i][j], 2);
	}
	MSE = (double)sum / (inputSize * inputSize);

	cout << "MSE: " << MSE << endl; //��� ���
	return;
}

int main(void) {
	FILE* fp1, *fp2;

	//�����Ҵ�
	unsigned char** original = new unsigned char* [inputSize];
	int** coeff_signed = new int* [inputSize];
	unsigned char** coefficient = new unsigned char* [inputSize];
	unsigned char** reconstructed = new unsigned char* [inputSize];
	for (int i = 0; i < inputSize; i++) {
		original[i] = new unsigned char[inputSize];
		coeff_signed[i] = new int[inputSize];
		coefficient[i] = new unsigned char[inputSize];
		reconstructed[i] = new unsigned char[inputSize];
	}

	//���� ���� �б�	
	if (fopen_s(&fp1, originalFile, "rb")) {
		cout << "[error]Can't open inputFile" << endl;
		return -1;
	}
	for (int i = 0; i < inputSize; i++) {
		fread(original[i], sizeof(unsigned char), inputSize, fp1);
		for (int j = 0; j < inputSize; j++)
			coeff_signed[i][j] = original[i][j]<<6;
	}
	fclose(fp1);

	//////////////////////////////////////////////////////////////////////////////
	//fixed point "0000_0000_00.00_0000"

	//coeff_signed ������ ������ ���� ����ȭ
	//LL3: 0 ~ 255		ELSE: -128 ~ 128

	haarWavelet(coefficient, 8, coeff_signed, inputSize);
	haarWavelet(coefficient, 8, coeff_signed, inputSize >> 1);
	haarWavelet(coefficient, 8, coeff_signed, inputSize >> 2);

	haarInverse(coeff_signed, inputSize >> 2);
	haarInverse(coeff_signed, inputSize >> 1);
	haarInverse(coeff_signed, inputSize);

	for (int i = 0; i < inputSize; i++) {
		for (int j = 0; j < inputSize; j++) {
			reconstructed[i][j] = coeff_signed[i][j] >> 6;
		}
	}
	//////////////////////////////////////////////////////////////////////////////
	//MSE
	MSE(original, reconstructed);
	//////////////////////////////////////////////////////////////////////////////
	//��� ����
	_mkdir("./output"); //output ���丮 ����

	//���� ����
	fopen_s(&fp1, coefficientFile, "wb");
	fopen_s(&fp2, reconstructedFile, "wb");
	for (int i = 0; i < inputSize; i++) {
		fwrite(coefficient[i], sizeof(unsigned char), inputSize, fp1);
		fwrite(reconstructed[i], sizeof(unsigned char), inputSize, fp2);
	}
	fclose(fp1); fclose(fp2);

	//�޸� ����
	for (int i = 0; i < inputSize; i++)
		delete[] original[i], coefficient[i], reconstructed[i], coeff_signed[i];
	delete[] original, coefficient, reconstructed, coeff_signed;
	return 0;
}