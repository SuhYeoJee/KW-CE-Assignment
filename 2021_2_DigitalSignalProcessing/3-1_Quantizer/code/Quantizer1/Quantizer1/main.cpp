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

	//image 동적할당
	unsigned char** image = new unsigned char* [xSize];
	for (int i = 0; i < xSize; i++) image[i] = new unsigned char[ySize * 3];
	
	//원본 파일 읽기	
	if (fopen_s(&fp, inputFile, "rb")) {
		cout << "[error]Can't open inputFile" << endl;
		return -1;
	}
	for (int i = 0; i < xSize; i++)
		fread(image[i], sizeof(unsigned char), ySize * 3, fp);
	fclose(fp);

	//양자화
	int gap = (int)pow(2, 8 - N); //구간 크기 구하기
	for (int i = 0; i < xSize; i++) {
		for (int j = 0; j < ySize * 3; j++)
			image[i][j] /= gap;
	}

	//결과 저장
	_mkdir("./output"); //output 디렉토리 생성
	if (fopen_s(&fp, outputFile, "wb")) {
		cout << "[error]Can't open outputFile" << endl;
		return -1;
	}

	unsigned int buff = 0, temp;
	unsigned char ch;
	int space = 32; //버퍼 빈공간 
	int x = 0, y = 0;

	while (1) {
		//빈공간 > N일 때 버퍼 채우기
		while ((space >= N) && (x < xSize)) {
			temp = image[x][y++];
			space -= N;
			temp <<= space;
			buff += temp;

			//다음 픽셀
			if (y >= ySize * 3) {
				x++; y = 0;
				if (x >= xSize) { //모든 픽셀 읽음
					space = 0;
				}
			}
		}
		//버퍼가 차있을 때 1byte만큼 파일에 쓰기
		ch = buff >> (32 - 8);
		buff <<= 8;
		space += 8;
		fputc(ch, fp);

		//모든 내용 쓰기 완료
		if ((x >= xSize) && (space == 32)) break;
	}
	fclose(fp);

	//동적할당 해제
	for (int i = 0; i < xSize; i++) delete[] image[i];
	delete[] image;

	return 0;
}