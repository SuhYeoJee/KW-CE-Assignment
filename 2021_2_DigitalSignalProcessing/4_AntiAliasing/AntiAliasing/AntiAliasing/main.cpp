#include <iostream>
#include <direct.h> //_mkdir
using namespace std;

#define originalFile			"./input/PartyScene_832x480_yuv420_8bit_frame120.yuv"
#define antialiasedFile			"./output/a_PartyScene_832x480_yuv420_8bit_frame120.yuv"
#define f_downsampledFile		"./output/df_PartyScene_832x480_yuv420_8bit_frame120.yuv"
#define downsampledFile			"./output/d_PartyScene_832x480_yuv420_8bit_frame120.yuv"
#define f_reconstructedFile		"./output/rf_PartyScene_832x480_yuv420_8bit_frame120.yuv"
#define reconstructedFile		"./output/r_PartyScene_832x480_yuv420_8bit_frame120.yuv" 

#define xSize	832	
#define ySize	480

void downsampling(unsigned char** ori, unsigned char** res, unsigned char** d) {
	int y = 0, x = 0;
	for (int i = 0; i < ySize; i++) {
		for (int j = 0; j < xSize; j++) {
			res[i][j] = 0;
			if ((i % 2) && (j % 2)) {
				res[i][j] = ori[i][j];
				d[y][x++] = ori[i][j]; //다운샘플링으로 축소된 결과 저장
				if (x == xSize) {
					x = 0; y++;
				}
			}
		}
	}
	return;
}

void upsampling(unsigned char** img) {
	int temp[6], t[6];
	int res;
	
	for (int i = 1; i < ySize; i += 2) {//가로줄 six tab 필터
		for (int j = 0; j < xSize; j += 2) {
			t[0] = j - 5; t[1] = j - 3; t[2] = j - 1;
			t[3] = j + 1; t[4] = j + 3; t[5] = j + 5;
			for (int k = 0; k < 6; k++) {
				t[k] = (t[k] < 0) ? 0 :t[k];
				t[k] = (t[k] < xSize) ? t[k] : xSize-1;
			}
			temp[0] = img[i][t[0]];	temp[1] = img[i][t[1]];	temp[2] = img[i][t[2]];
			temp[3] = img[i][t[3]];	temp[4] = img[i][t[4]];	temp[5] = img[i][t[5]];
			res = ((temp[0] - (5 * temp[1]) + (20 * temp[2]) + (20 * temp[3]) - (5 * temp[4]) + temp[5]) >> 5);
			img[i][j] = (res > 255) ? 255 : res;
		}
	}
	
	for (int i = 0; i < ySize; i += 2) {//세로줄 six tab 필터
		for (int j =1; j < xSize; j += 2) {
			t[0] = i - 5; t[1] = i - 3; t[2] = i - 1;
			t[3] = i + 1; t[4] = i + 3; t[5] = i + 5;
			for (int k = 0; k < 6; k++) {
				t[k] = (t[k] < 0) ? 0 : t[k];
				t[k] = (t[k] < ySize) ? t[k] : ySize - 1;
			}
			temp[0] = img[t[0]][j];	temp[1] = img[t[1]][j];	temp[2] = img[t[2]][j];
			temp[3] = img[t[3]][j];	temp[4] = img[t[4]][j];	temp[5] = img[t[5]][j];
			res = ((temp[0] - (5 * temp[1]) + (20 * temp[2]) + (20 * temp[3]) - (5 * temp[4]) + temp[5]) >> 5);
			img[i][j] = (res > 255) ? 255 : res;
		}
	}
	
	for (int i = 0; i < ySize; i += 2) {//가로줄 six tab 필터
		for (int j = 0; j < xSize; j += 2) {
			t[0] = j - 5; t[1] = j - 3; t[2] = j - 1;
			t[3] = j + 1; t[4] = j + 3; t[5] = j + 5;
			for (int k = 0; k < 6; k++) {
				t[k] = (t[k] < 0) ? 0 : t[k];
				t[k] = (t[k] < xSize) ? t[k] : xSize - 1;
			}
			temp[0] = img[i][t[0]];	temp[1] = img[i][t[1]];	temp[2] = img[i][t[2]];
			temp[3] = img[i][t[3]];	temp[4] = img[i][t[4]];	temp[5] = img[i][t[5]];
			res = ((temp[0] - (5 * temp[1]) + (20 * temp[2]) + (20 * temp[3]) - (5 * temp[4]) + temp[5]) >> 5);
			img[i][j] = (res > 255) ? 255 : res;
		}
	}
	return;
}

void gaussian(unsigned char** ori, unsigned char **res) {
	int filter[5][5] = { {1,4,7,4,1},
						{4,16,26,16,4},
						{7,26,41,26,7},
						{4,16,26,16,4},
						{1,4,7,4,1} };
	int sum, a, b;
	
	for (int i = 0; i < ySize; i++) {
		for (int j = 0; j < xSize; j++) {
			sum = 0;
			for (int y = -2; y < 3; y++) {
				for (int x = -2; x < 3; x++) {
					a = i + y; b = j + x;
					if (a < 0) a = 0;
					else if (a > ySize-1) a = ySize-1;
					if (b < 0) b = 0;
					else if (b > xSize-1) b = xSize - 1;

					sum += filter[y+2][x+2] * ori[a][b];
				}
			}
			res[i][j] = (char)round(sum/273) ;
		}
	}
}

void MSE(unsigned char** ori, unsigned char** rec) {
	double sum = 0, MSE;

	for (int i = 0; i < ySize; i++) {
		for (int j = 0; j < xSize; j++)
			sum += pow(ori[i][j] - rec[i][j], 2);
	}
	MSE = (double)sum / (xSize * ySize);

	cout << "MSE: " << MSE << endl; //결과 출력
	return;
}


int main(void) {
	int yuvSize = ySize * 1.5;

	//메모리 할당
	unsigned char** original = new unsigned char* [yuvSize];		//원본이미지
	unsigned char** antialiased = new unsigned char* [yuvSize];		//가우시안 필터 적용한 이미지
	unsigned char** reconstructed = new unsigned char* [yuvSize];	//필터 적용 없이 복원한 이미지
	unsigned char** f_reconstructed = new unsigned char* [yuvSize];	//필터 적용 후 복원한 이미지
	unsigned char** downsampled = new unsigned char* [ySize];		//필터 적용 없이 다운샘플링한 이미지
	unsigned char** f_downsampled = new unsigned char* [ySize];		//필터 적용 후 다운샘플링한 이미지
	for (int i = 0; i < yuvSize; i++) {
		original[i] = new unsigned char[xSize];
		antialiased[i] = new unsigned char[xSize];
		reconstructed[i] = new unsigned char[xSize];
		f_reconstructed[i] = new unsigned char[xSize];
	}
	for (int i = 0; i < ySize; i++) {
		downsampled[i] = new unsigned char[xSize];
		f_downsampled[i] = new unsigned char[xSize];
	}

	FILE* fp1, *fp2, *fp3;
	//입력 파일 읽기
	fopen_s(&fp1, originalFile, "rb");
	for (int i = 0; i < yuvSize; i++)
		fread(original[i], sizeof(unsigned char), xSize, fp1);
	fclose(fp1);

	/////////////////////////////////////////////////////////////////////////////////

	downsampling(original,reconstructed,downsampled);	//필터 적용 없이 다운샘플링
	upsampling(reconstructed);							//필터 적용 없이 업샘플링

	gaussian(original, antialiased);							//가우시안 필터 적용
	downsampling(antialiased, f_reconstructed,f_downsampled);	//필터 적용 후 다운샘플링
	upsampling(f_reconstructed);								//필터 적용 후 업샘플링

	cout << "reconstructed:" << endl;	//MSE계산
	MSE(original, reconstructed);	
	cout << "f_reconstructed:" << endl;
	MSE(original, f_reconstructed);

	/////////////////////////////////////////////////////////////////////////////////

	//u,v채널 복사
	for (int i = ySize; i < yuvSize; i++) {
		for(int j = 0; j < xSize; j++) {
			antialiased[i][j] = original[i][j];
			reconstructed[i][j] = original[i][j];
			f_reconstructed[i][j] = original[i][j];
		}
	}

	/////////////////////////////////////////////////////////////////////////////////

	//output 디렉토리 생성
	_mkdir("./output");

	//파일 쓰기
	fopen_s(&fp1, antialiasedFile, "wb"); //필터 적용 결과
	fopen_s(&fp2, reconstructedFile, "wb"); //필터 적용없이 복원한 결과
	fopen_s(&fp3, f_reconstructedFile, "wb"); //필터 적용 후 복원한 결과
	for (int i = 0; i < yuvSize; i++) {
		fwrite(antialiased[i], sizeof(unsigned char), xSize, fp1);
		fwrite(reconstructed[i], sizeof(unsigned char), xSize, fp2);
		fwrite(f_reconstructed[i], sizeof(unsigned char), xSize, fp3);
	}	
	fclose(fp1); fclose(fp2); fclose(fp3);

	fopen_s(&fp1, downsampledFile, "wb"); //필터 적용없이 다운샘플링 결과
	fopen_s(&fp2, f_downsampledFile, "wb"); //필터 적용 후 다운샘플링한 결과
	for (int i = 0; i < ySize; i++) {
		fwrite(downsampled[i], sizeof(unsigned char), xSize, fp1);
		fwrite(f_downsampled[i], sizeof(unsigned char), xSize, fp2);
	}
	fclose(fp1); fclose(fp2);

	//메모리 해제
	for (int i = 0; i < yuvSize; i++)
		delete[] original[i],antialiased[i] , reconstructed[i], f_reconstructed[i];
	for (int i = 0; i < ySize; i++)
		delete[] downsampled[i],f_downsampled[i];
	delete[] original, antialiased, downsampled, f_downsampled, reconstructed, f_reconstructed;
	return 0;
}