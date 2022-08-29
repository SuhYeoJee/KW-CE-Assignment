#include <stdio.h>

int main(void)
{
	char arr[30];
	int brr[8];
	int i, M, a;

	printf("영단어 입력\n");
	scanf("%s", &arr);

	M = arr[0];
	for (i = 0; arr[i] != NULL; i++)
		M = (M > arr[i]) ? M : arr[i];
	printf("%c %d\n", M, M);

	printf("이진수 출력\n");
	for (i = 0; i < 8; i++)
	{
		brr[i] = M % 2;
		M = (M - M % 2) / 2;
	}

	for (i = 0; i < 8; i++)
		printf("%d", brr[i]);
	printf("\n");

	for (i = 0; i <4; i++)
	{
		a = brr[7 - i];
		brr[7 - i] = brr[i];
		brr[i] = a;
	}

	for (i = 0; i<8; i++)
		printf("%d", brr[i]);


	return 0;
}