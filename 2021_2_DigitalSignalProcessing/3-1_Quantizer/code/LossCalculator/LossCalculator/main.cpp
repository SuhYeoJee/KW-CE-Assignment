#include <iostream>
using namespace std;

#define oriFile		"./input/Lenna_512x512_original.raw"
#define recFile		"./input/Lenna_512x512_reconstruct.raw"
#define codeFile	"./input/Lenna_512x512_code"
#define xSize	512
#define ySize	512

int main(void) {
	FILE* ofp,*rfp;

	//image 동적할당
	unsigned char** ori = new unsigned char* [xSize];
	unsigned char** rec = new unsigned char* [xSize];
	for (int i = 0; i < xSize; i++) {
		ori[i] = new unsigned char[ySize * 3];
		rec[i] = new unsigned char[ySize * 3];
	}

	//파일 읽기
	if (fopen_s(&ofp, oriFile, "rb")) {
		cout << "[error]Can't open oriFile" << endl;
		return -1;
	}
	if (fopen_s(&rfp, recFile, "rb")) {
		cout << "[error]Can't open recFile" << endl;
		return -1;
	}
	for (int i = 0; i < xSize; i++) {
		fread(ori[i], sizeof(unsigned char), ySize * 3, ofp);
		fread(rec[i], sizeof(unsigned char), ySize * 3, rfp);
	}
	fclose(ofp);
	fclose(rfp);

	//bit per Pixel 계산
	double bitPerPixel;
	int codeSize;
	if (fopen_s(&rfp, codeFile, "rb")) {
		cout << "[error]Can't open codeFile" << endl;
		return -1;
	}
	fseek(rfp, 0, SEEK_END);
	codeSize = ftell(rfp) * 8; //bit
	// file size / # of pixel
	bitPerPixel = (double)codeSize/ (long long int)(xSize*ySize);
	fclose(rfp);

	//MSE 계산
	long long int sum=0;
	double MSE;

	for (int i = 0; i < xSize; i++) {
		for (int j = 0; j < ySize * 3; j++)
			sum += pow(ori[i][j] - rec[i][j], 2);
	}
	MSE = (double)sum / ((long long int)xSize * ySize * 3);

	//결과 출력
	cout << "codeSize(bit): " << codeSize << endl
		<<"BitPerPixel: "<<bitPerPixel<<endl
		<< "MSE: " << MSE <<endl
		<< "Loss: " << bitPerPixel + 4 * MSE << endl;

	//동적할당 해제
	for (int i = 0; i < xSize; i++) {
		delete[] ori[i];
		delete[] rec[i];
	}
	delete[] ori;
	delete[] rec;

	return 0;
}