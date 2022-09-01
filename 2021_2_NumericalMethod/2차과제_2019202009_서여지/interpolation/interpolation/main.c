#include <stdio.h>
#include <math.h>

#define input				"./Input image/Barbara_128x128_yuv400_8bit.raw"
//#define input				"./Input image/Couple_128x128_yuv400_8bit.raw"
//#define input				"./Input image/Lena_128x128_yuv400_8bit.raw"
#define original			"./Original image/Barbara_512x512_yuv400_8bit.raw"
//#define original			"./Original image/Couple_512x512_yuv400_8bit.raw"
//#define original			"./Original image/Lena_512x512_yuv400_8bit.raw"
#define output				"./output_Barbara_512x512_yuv400_8bit.raw"
//#define output			"./output_Couple_512x512_yuv400_8bit.raw"
//#define output			"./output_Lena_512x512_yuv400_8bit.raw"
#define method 'B'	// bilinear
//#define method 'L'	// 3th Lagrange
//#define method 'S'	// six-tap

#define inputSize 128
#define outputSize 512

void bilinear(unsigned char** inputImage, unsigned char** outputImage) {
	int i, j;
	unsigned char a, b; //2개의 값 이용

	printf("bilinear interpolation\n");

	for (i = 2; i < outputSize-4; i += 4) {		//가로줄 bilinear 보간
		for (j = 2; j < outputSize-4; j += 4) {
			a = outputImage[i][j]; b = outputImage[i][j + 4];
			outputImage[i][j + 1] = a + (((b - a) * 1) >> 2);
			outputImage[i][j + 2] = a + (((b - a) * 2) >> 2);
			outputImage[i][j + 3] = a + (((b - a) * 3) >> 2);
		}
	}
	for (j = 0; j < outputSize; j ++) {			//세로줄 bilinear 보간
		for (i = 2; i < outputSize - 4; i +=4) {
			a = outputImage[i][j]; b = outputImage[i+4][j];
			outputImage[i+1][j] = a + (((b - a) * 1) >> 2);
			outputImage[i+2][j] = a + (((b - a) * 2) >> 2);
			outputImage[i+3][j] = a + (((b - a) * 3) >> 2);
		}
	}
	return;
}

unsigned char lagrangeFunc(int x, unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
	int A,B,C,D,K; //fixed point
	
	// f(x)L(x) 계산
	A = (a * (((x - 4) * (x - 8) * (x - 12)) / (-3))) << 9;
	B=(b * ((x) * (x - 8) * (x - 12))) << 9;
	C=(c * ((x) * (x - 4) * (x - 12)) * (-1)) << 9;
	D= (d * (((x) * (x - 4) * (x - 8)) / (3))) << 9;
	K = A + B + C + D;

	return  (K << 16) ? (K >> 16) + 1 : (K >> 16);
}

void lagrange(unsigned char** inputImage, unsigned char** outputImage) {
	int i, j;
	unsigned char a, b, c, d; //4개의 점을 이용함

	printf("3th Lagrange interpolation\n");

	for (i = 2; i < outputSize - 4; i += 4) {	//가로줄 lagrange 보간
		for (j = 2; j < outputSize - 12; j += 12) {
			a = outputImage[i][j]; b = outputImage[i][j + 4];
			c = outputImage[i][j + 8]; d = outputImage[i][j + 12];
			outputImage[i][j + 1] = lagrangeFunc(1, a, b, c, d);
			outputImage[i][j + 2] = lagrangeFunc(2, a, b, c, d);
			outputImage[i][j + 3] = lagrangeFunc(3, a, b, c, d);
			outputImage[i][j + 5] = lagrangeFunc(5, a, b, c, d);
			outputImage[i][j + 6] = lagrangeFunc(6, a, b, c, d);
			outputImage[i][j + 7] = lagrangeFunc(7, a, b, c, d);
			outputImage[i][j + 9] = lagrangeFunc(9, a, b, c, d);
			outputImage[i][j + 10] = lagrangeFunc(10, a, b, c, d);
			outputImage[i][j + 11] = lagrangeFunc(11, a, b, c, d);
			if (j == outputSize - 18) j -= 8;
		}
	}

	for (j = 0; j < outputSize; j++) {		//세로줄 lagrange 보간
		for (i = 2; i < outputSize - 12; i += 12) {
			a = outputImage[i][j]; b = outputImage[i+4][j];
			c = outputImage[i+8][j]; d = outputImage[i+12][j];
			outputImage[i+1][j] = lagrangeFunc(1, a, b, c, d);
			outputImage[i+2][j] = lagrangeFunc(2, a, b, c, d);
			outputImage[i+3][j] = lagrangeFunc(3, a, b, c, d);
			outputImage[i+5][j] = lagrangeFunc(5, a, b, c, d);
			outputImage[i+6][j] = lagrangeFunc(6, a, b, c, d);
			outputImage[i+7][j] = lagrangeFunc(7, a, b, c, d);
			outputImage[i+9][j] = lagrangeFunc(9, a, b, c, d);
			outputImage[i+10][j] = lagrangeFunc(10, a, b, c, d);
			outputImage[i+11][j] = lagrangeFunc(11, a, b, c, d);
			if (i == outputSize - 18) i -= 8;
		}
	}
	return;
}

void sixTab(unsigned char** inputImage, unsigned char** outputImage) {
	int i, j;
	unsigned char a, b, c, d,e,f;	//6개의 점 이용

	printf("six-tab interpolation\n");

	for (i = 2; i < outputSize - 4; i += 4) { //가로줄 six tab 필터
		for (j = 2; j < outputSize - 20; j += 4) {
			a = outputImage[i][j]; b = outputImage[i][j + 4];
			c = outputImage[i][j + 8]; d = outputImage[i][j + 12];
			e = outputImage[i][j + 16]; f = outputImage[i][j + 20];
			outputImage[i][j + 10] = ((a - (5 * b) + (20 * c) + (20 * d) - (5 * e) + f)>>5);
		}
	}

	for (j = 2; j < outputSize - 4; j += 4) { //세로줄 six tab 필터
		for (i = 2; i< outputSize - 20; i += 4) {
			a = outputImage[i][j]; b = outputImage[i+ 4][j ];
			c = outputImage[i+ 8][j ]; d = outputImage[i+ 12][j ];
			e = outputImage[i+ 16][j ]; f = outputImage[i+ 20][j ];
			outputImage[i+ 10][j ] = ((a - (5 * b) + (20 * c) + (20 * d) - (5 * e) + f) >> 5);
		}
		if (outputImage[2][j+2]) j -= 2;
	}

	for (i = 12; i < outputSize - 10; i += 2) { //가로줄 보간
		for (j = 12; j < outputSize - 10; j += 2) {
			a = outputImage[i][j]; b = outputImage[i][j + 2];
			outputImage[i][j + 1] = ((a+b)>>1);
		}
	}
	for (j = 12; j < outputSize - 10; j++) { //세로줄 보간
		for (i = 12; i < outputSize - 10; i += 2) {
			a = outputImage[i][j]; b = outputImage[i+2][j];
			outputImage[i+1][j] = ((a + b) >>1);
		}
	}

	return 0;
}

void performance(unsigned char** outputImage) {
	FILE* fp;
	unsigned char** originalImage;
	int i, j;
	long long int sum = 0;
	double MSE, PSNR, RMSE;

	//메모리 할당
	originalImage = (unsigned char**)malloc(sizeof(char*) * outputSize);
	for (i = 0; i < outputSize; i++)
		originalImage[i] = (unsigned char*)malloc(sizeof(char) * outputSize);

	//원본 파일 읽기
	fopen_s(&fp, original, "rb");
	for (i = 0; i < outputSize; i++)
		fread(originalImage[i], sizeof(unsigned char), outputSize, fp);
	fclose(fp);

	//MSE 계산
	for (int i = 0; i < outputSize; i++) {
		for (int j = 0; j < outputSize; j++)
			sum += pow(originalImage[i][j] - outputImage[i][j], 2);
	}
	MSE = (double)sum / ((long long int)outputSize * outputSize);

	PSNR = 10*log10(pow(255,2)/MSE);
	RMSE = sqrt(MSE);
	printf("PSNR: %lf\nRMSE: %lf\n", PSNR, RMSE);

	//메모리 해제
	for (i = 0; i < outputSize; i++)
		free(originalImage[i]);
	free(originalImage);

	return;
}

int main(void) {
	FILE* fp;
	unsigned char** inputImage;
	unsigned char** outputImage;
	int i,j;

	//메모리 할당
	inputImage = (unsigned char**)malloc(sizeof(char*) * inputSize);
	outputImage = (unsigned char**)malloc(sizeof(char*) * outputSize);
	for (i = 0; i < inputSize; i++)
		inputImage[i] = (unsigned char*)malloc(sizeof(char) * inputSize);
	for (i = 0; i < outputSize; i++)
		outputImage[i] = (unsigned char*)malloc(sizeof(char) * outputSize);

	//입력 파일 읽기
	fopen_s(&fp, input, "rb");
	for (i = 0; i < inputSize; i++)
		fread(inputImage[i], sizeof(unsigned char), inputSize, fp);
	fclose(fp);

	//512*512크기의 배열에 128*128 값을 원래 자리에 저장함 //(2,2), (2,6),,,
	for (i = 0; i < outputSize; i++) {
		for (j = 0; j < outputSize; j++) {
			outputImage[i][j] = 0;
		}
	}
	for (i = 2; i < outputSize; i+=4) {
		for (j = 2; j < outputSize; j+=4) {
			outputImage[i][j] = inputImage[(i-2)>>2][(j-2)>>2];
		}
	}

	//나머지 픽셀의 값 보간
	if (method == 'B') bilinear(inputImage, outputImage);
	else if (method == 'L')lagrange(inputImage, outputImage);
	else if (method == 'S')sixTab(inputImage, outputImage);
	else return -1;

	//파일 쓰기
	fopen_s(&fp, output, "wb");
	for (i = 0; i < outputSize; i++)
		fwrite(outputImage[i], sizeof(unsigned char), outputSize, fp);
	fclose(fp);

	//PSNR, RMSE 출력
	performance(outputImage);

	//메모리 해제
	for (i = 0; i < inputSize; i++)
		free(inputImage[i]);
	for (i = 0; i < outputSize; i++)
		free(outputImage[i]);
	free(inputImage);
	free(outputImage);
	return 0;
}