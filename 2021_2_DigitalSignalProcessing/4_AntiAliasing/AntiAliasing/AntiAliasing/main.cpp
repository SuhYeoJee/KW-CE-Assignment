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
				d[y][x++] = ori[i][j]; //�ٿ���ø����� ��ҵ� ��� ����
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
	
	for (int i = 1; i < ySize; i += 2) {//������ six tab ����
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
	
	for (int i = 0; i < ySize; i += 2) {//������ six tab ����
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
	
	for (int i = 0; i < ySize; i += 2) {//������ six tab ����
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

	cout << "MSE: " << MSE << endl; //��� ���
	return;
}


int main(void) {
	int yuvSize = ySize * 1.5;

	//�޸� �Ҵ�
	unsigned char** original = new unsigned char* [yuvSize];		//�����̹���
	unsigned char** antialiased = new unsigned char* [yuvSize];		//����þ� ���� ������ �̹���
	unsigned char** reconstructed = new unsigned char* [yuvSize];	//���� ���� ���� ������ �̹���
	unsigned char** f_reconstructed = new unsigned char* [yuvSize];	//���� ���� �� ������ �̹���
	unsigned char** downsampled = new unsigned char* [ySize];		//���� ���� ���� �ٿ���ø��� �̹���
	unsigned char** f_downsampled = new unsigned char* [ySize];		//���� ���� �� �ٿ���ø��� �̹���
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
	//�Է� ���� �б�
	fopen_s(&fp1, originalFile, "rb");
	for (int i = 0; i < yuvSize; i++)
		fread(original[i], sizeof(unsigned char), xSize, fp1);
	fclose(fp1);

	/////////////////////////////////////////////////////////////////////////////////

	downsampling(original,reconstructed,downsampled);	//���� ���� ���� �ٿ���ø�
	upsampling(reconstructed);							//���� ���� ���� �����ø�

	gaussian(original, antialiased);							//����þ� ���� ����
	downsampling(antialiased, f_reconstructed,f_downsampled);	//���� ���� �� �ٿ���ø�
	upsampling(f_reconstructed);								//���� ���� �� �����ø�

	cout << "reconstructed:" << endl;	//MSE���
	MSE(original, reconstructed);	
	cout << "f_reconstructed:" << endl;
	MSE(original, f_reconstructed);

	/////////////////////////////////////////////////////////////////////////////////

	//u,vä�� ����
	for (int i = ySize; i < yuvSize; i++) {
		for(int j = 0; j < xSize; j++) {
			antialiased[i][j] = original[i][j];
			reconstructed[i][j] = original[i][j];
			f_reconstructed[i][j] = original[i][j];
		}
	}

	/////////////////////////////////////////////////////////////////////////////////

	//output ���丮 ����
	_mkdir("./output");

	//���� ����
	fopen_s(&fp1, antialiasedFile, "wb"); //���� ���� ���
	fopen_s(&fp2, reconstructedFile, "wb"); //���� ������� ������ ���
	fopen_s(&fp3, f_reconstructedFile, "wb"); //���� ���� �� ������ ���
	for (int i = 0; i < yuvSize; i++) {
		fwrite(antialiased[i], sizeof(unsigned char), xSize, fp1);
		fwrite(reconstructed[i], sizeof(unsigned char), xSize, fp2);
		fwrite(f_reconstructed[i], sizeof(unsigned char), xSize, fp3);
	}	
	fclose(fp1); fclose(fp2); fclose(fp3);

	fopen_s(&fp1, downsampledFile, "wb"); //���� ������� �ٿ���ø� ���
	fopen_s(&fp2, f_downsampledFile, "wb"); //���� ���� �� �ٿ���ø��� ���
	for (int i = 0; i < ySize; i++) {
		fwrite(downsampled[i], sizeof(unsigned char), xSize, fp1);
		fwrite(f_downsampled[i], sizeof(unsigned char), xSize, fp2);
	}
	fclose(fp1); fclose(fp2);

	//�޸� ����
	for (int i = 0; i < yuvSize; i++)
		delete[] original[i],antialiased[i] , reconstructed[i], f_reconstructed[i];
	for (int i = 0; i < ySize; i++)
		delete[] downsampled[i],f_downsampled[i];
	delete[] original, antialiased, downsampled, f_downsampled, reconstructed, f_reconstructed;
	return 0;
}