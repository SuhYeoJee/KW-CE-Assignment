#include <stdio.h>
/*
int main(void)
{
	char arr1[3]; //char형 변수 3개로 이루어진 배열
	char *arr2[3];//char형 포인터 변수 3개로 이루어진 배열 (포인터 배열)
	char (*arr3)[3];//char형 변수3개의 배열을 가리키는 포인터 변수 (배열 포인터)

	printf("%d\n", sizeof(arr1));
	printf("%d\n", sizeof(arr2));
	printf("%d\n", sizeof(arr3));
}
*/
int main(void)
{
	int a, b, c, d, e, f;
	//char arr[3];
	//char *arr1[3];
	//char(*arr1)[3]=arr;
	char arr[2][3];
	char(*arr1)[3]=arr;

	printf("%d\n", arr1);
	printf("%d\n", &arr1);
	printf("%d\n", arr1+1);
	printf("%d\n", &arr1+1);
}