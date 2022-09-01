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

	////////////////////////////////////////////////////////////////////////////

	//빈도
	int p[256] = { 0};
	for (int i = 0; i < xSize; i++) {
		for (int j = 0; j < ySize*3; j++) {
			p[(int)image[i][j]]++;
		}
	}

	//초기 di 계산
	int gap = (int)pow(2, 8 - N); //구간 크기 구하기
	int L = (int)pow(2, N)+1;
	int* d = new int[L];
	int* r = new int[L];
	unsigned int temp = 0, temp2=1;

	for (int i = 0; i < L; i++) { //di 초기값 = 균등
		d[i] = temp;	//d[0] = 0(min)	d[L-1] = 256(MAX)
		temp += gap;
	}
	r[0] = 0;	//r0 사용안함

	////////////////////////////////////////////////////////////////////////////

	//ri와 di를 반복 계산
	while(temp2){
		//ri - 구간내 모든 샘플의 평균값
		for (int i = 1; i < L; i++) {
			temp = 0; temp2 = 0;
			for (int j = d[i-1]; j < d[i]; j++) {
				temp += j * p[j];	//샘플 값 * 확률
				temp2 += p[j];		//확률
			}
			r[i] = (temp2 == 0) ? d[i-1]: round((double)temp / temp2); //확률이 0인 경우 d[i-1]값 임의 사용
		}

		temp2 = 0; //iteration
		//di - ri와 ri+1의 평균값
		for (int i = 1; i < L-1; i++) {
			temp = d[i];
			d[i] = round(((double)r[i] + r[i + 1]) / 2);
			if (temp != d[i]) temp2++;
		}
	}

	////////////////////////////////////////////////////////////////////////////

	//이미지 값에 적용
	for (int i = 0; i < xSize; i++) {
		for (int j = 0; j < ySize * 3; j++) { //3채널, 모든 픽셀의 값에 대해
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

	//결과 저장
	_mkdir("./output"); //output 디렉토리 생성
	if (fopen_s(&fp, outputFile, "wb")) {
		cout << "[error]Can't open outputFile" << endl;
		return -1;
	}

	unsigned int buff = 0;
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


	//codebook저장
	if (fopen_s(&fp, codebookFile, "wb")) {
		cout << "[error]Can't open codebookFile" << endl;
		return -1;
	}
	fwrite(r, sizeof(int), L, fp);
	fclose(fp);


	//동적할당 해제
	for (int i = 0; i < xSize; i++) delete[] image[i];
	delete[] image;

	return 0;
}