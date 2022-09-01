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
	const int y2Size = ySize * 2;
	const int y3Size = ySize * 3;
	FILE* fp;

	//image 동적할당	//code 동적할당
	unsigned char** image = new unsigned char* [xSize];
	unsigned char** code = new unsigned char* [xSize];
	for (int i = 0; i < xSize; i++) {
		image[i] = new unsigned char[y3Size];
		code[i] = new unsigned char[ySize];
	}

	//원본 파일 읽기	
	if (fopen_s(&fp, inputFile, "rb")) {
		cout << "[error]Can't open inputFile" << endl;
		return -1;
	}
	for (int i = 0; i < xSize; i++)
		fread(image[i], sizeof(unsigned char), y3Size, fp);
	fclose(fp);

	////////////////////////////////////////////////////////////////////////////
	//초기 3차원 벡터 선택
	//image[i][j], image[i][ysize+j], image[i][y2size+j] 가 벡터로 묶임 (R,G,B)
	int vSize = (int)pow(2, N); //2^N개의 3차원 벡터
	int gap = xSize / vSize;
	unsigned int temp1 = 0;

	unsigned char** v = new unsigned char*[vSize];
	for (int i = 0; i < vSize; i++) {
		v[i] = new unsigned char[3];
		v[i][0] = temp1;
		v[i][1] = temp1;
		v[i][2] = temp1;
		temp1 += gap;
	}

	////////////////////////////////////////////////////////////////////////////
	// 양자화
	int iter = 0; //반복 횟수
	while ((temp1!=0)&&(iter<20)) {
		cout << iter++ << "번째 반복\t";
		// 그룹 분류
		for (int i = 0; i < xSize; i++) {
			for (int j = 0; j < ySize; j++) {
				int x = image[i][j],y = image[i][j + ySize],z = image[i][j + y2Size];
				unsigned int min = 0xFFFFFFFF;
				//x,y,z와 v[k][0], v[k][1], v[k][2]의 거리
				//가장 가까운 벡터 code[i][j] = k;
				for (int k = 0; k < vSize; k++) {
					unsigned int d = pow((x - v[k][0]), 2) + pow((y - v[k][1]), 2) + pow((z - v[k][2]), 2);
					if (d < min) {
						min = d;
						code[i][j] = k;
					}
				}
			}
		}

		//reconstructed vector 재설정 (각 그룹의 평균값)
		temp1 = 0; //x성분이 변경된 벡터의 수 (반복종료조건)
		for (int k = 0; k < vSize; k++) {
			int x = 0, y = 0, z = 0, c = 0;
			for (int i = 0; i < xSize; i++) {
				for (int j = 0; j < ySize; j++) {
					//k번째 벡터 그룹에 해당하는 벡터의 x,y,z성분 합
					if (code[i][j] != k) continue;
					x += image[i][j];
					y += image[i][j + ySize];
					z += image[i][j + y2Size];
					c++; //k번째 벡터 그룹에 해당하는 벡터의 수
				}
			}
			if (c == 0) continue; //그룹에 해당하는 벡터가 없는 경우
			if (v[k][0] != x / c) temp1 ++; //x성분이 변경된 벡터의 수 (반복종료조건)
			//k번째 벡터 그룹의 평균값
			v[k][0] = x / c;
			v[k][1] = y / c;
			v[k][2] = z / c;
		}
		cout << temp1 << endl;//x성분이 변경된 벡터의 수 (반복종료조건)
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
			temp1 = code[x][y++];
			space -= N;
			temp1 <<= space;
			buff += temp1;

			//다음 픽셀
			if (y >= ySize) {
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
	for (int i = 0; i < vSize; i++)
		fwrite(v[i], sizeof(unsigned char), 3, fp);
	fclose(fp);

	//동적할당 해제
	for (int i = 0; i < xSize; i++) delete[] image[i], code[i];
	for (int i = 0; i < vSize; i++) delete[] v[i];
	delete[] image, code, v;
	return 0;
}