#include <iostream>
#include <direct.h> //_mkdir
using namespace std;

#define inputFile		"./input/Lenna_512x512_code"
#define outputFile		"./output/Lenna_512x512_reconstruct.raw"
#define xSize	512
#define ySize	512
#define N	7	// USE N bit

int main(void) {
	FILE* fp;

	//image 동적할당
	unsigned char** image = new unsigned char* [xSize];
	for (int i = 0; i < xSize; i++) image[i] = new unsigned char[ySize * 3];

	//양자화 코드 읽기
	if (fopen_s(&fp, inputFile, "rb")) {
		cout << "[error]Can't open inputFile" << endl;
		return -1;
	}

	unsigned int buff = 0, temp;
	int space = 32;
	for (int i = 0; i < xSize; i++) {
		for (int j = 0; j < ySize*3; j++) {
			//버퍼채우기
			while (space >= 8) {
				temp = fgetc(fp);
				space -= 8;
				temp <<= space;
				buff += temp;
			}
			//픽셀에 값 저장
			image[i][j] = buff >> (32 - N);
			buff <<= N;
			space += N;
		}
	}
	fclose(fp);

	//역양자화
	int gap = (int)pow(2, 8 - N); //구간 크기 구하기
	for (int i = 0; i < xSize; i++) {
		for (int j = 0; j < ySize * 3; j++) {
			//image[i][j] = gap * (image[i][j] + 1 / 2);
			image[i][j] = gap*image[i][j]+gap*1/2;
		}
	}

	//역양자화 결과 저장
	_mkdir("./output");
	if (fopen_s(&fp, outputFile, "wb")) {
		cout << "[error]Can't open outputFile" << endl;
		return -1;
	}
	for (int i = 0; i < xSize; i++)
		fwrite(image[i], sizeof(unsigned char), ySize * 3, fp);
	fclose(fp);

	//동적할당 해제
	for (int i = 0; i < xSize; i++) delete[] image[i];
	delete[] image;

	return 0;
}