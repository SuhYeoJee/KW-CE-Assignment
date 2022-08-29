#include <stdio.h>
// 3:15 ~ 5:34 (2시간 15분)
void Yeo(int(*ptr1)[24], int haeng); // arr[7][0~11] 사이 '여' 모양으로 저장
void Jee(int(*ptr1)[24], int haeng); // arr[7][12~23] 사이 '지' 모양으로 저장
void Printarr(int(*arr)[24], int haeng); // 배열을 출력

int main(void)
{
	int arr[7][24] = { 0 }; // 배열선언, 0으로 초기화
	int haeng = sizeof(arr) / sizeof(arr[0]); //배열의 행
	int(*ptr)[24] = &arr;
	int i = 0;

	for (i = 0; i < haeng; i++) // i를 1씩 증가시키며 Yeo 함수 호출
		Yeo(ptr, i);
	Printarr(arr, haeng);
	return 0;
}

void Yeo(int(*ptr1)[24], int haeng) 
{ // 대칭형태임을 이용, 글자부분에 @기호, 나머지 공백기호 저장
	int a;
	if ((haeng == 0) || (haeng == 6)) 
		for (a = 0; a < 12; a++)
			ptr1[haeng][a] = ((2 < a && a < 6) || a == 11) ? 64 : 32;
	if ((haeng == 1) || (haeng == 5))
		for (a = 0; a < 12; a++)
			ptr1[haeng][a] = (a == 2 || a == 6 || a == 11) ? 64 : 32;
	if ((haeng == 2) || (haeng == 4))
		for (a = 0; a < 12; a++)
			ptr1[haeng][a] = (a == 1 || a == 7 || (8 < a&&a < 12)) ? 64 : 32;
	if (haeng == 3)
		for (a = 0; a < 12; a++)
			ptr1[haeng][a] = (a == 1 || a == 7 || a == 11) ? 64 : 32;
	Jee(ptr1, haeng);
}

void Jee(int(*ptr2)[24], int haeng)
{ //글자부분에 @기호, 나머지 공백기호 저장
	int a;
	if (haeng == 0)
		for (a = 12; a < 24; a++)
			ptr2[haeng][a] = ((12 < a && a < 20) || a == 22) ? 64 : 32;
	if (haeng == 1)
		for (a = 12; a < 24; a++)
			ptr2[haeng][a] = (a == 18 || a == 22) ? 64 : 32;
	if (haeng == 2)
		for (a = 12; a < 24; a++)
			ptr2[haeng][a] = (a == 17 || a == 22) ? 64 : 32;
	if (haeng == 3)
		for (a = 12; a < 24; a++)
			ptr2[haeng][a] = (a == 16 || a == 22) ? 64 : 32;
	if (haeng == 4)
		for (a = 12; a < 24; a++)
			ptr2[haeng][a] = (a == 15 || a == 17 || a == 22) ? 64 : 32;
	if (haeng == 5)
		for (a = 12; a < 24; a++)
			ptr2[haeng][a] = (a == 14 || a == 18 || a == 22) ? 64 : 32;
	if (haeng == 6)
		for (a = 12; a < 24; a++)
			ptr2[haeng][a] = (a == 13 || a == 19 || a == 22) ? 64 : 32;
}

void Printarr(int(*arr)[24], int haeng)
{
	int i, j;
	printf("\n");
	for (i = 0; i < haeng; i++)
	{
		for (j = 0; j < 24; j++)
			printf("%c", arr[i][j]);
		printf("\n");
	}
}