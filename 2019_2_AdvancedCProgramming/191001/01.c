#include <stdio.h>
/*
int main(void)
{
	char arr1[3]; //char�� ���� 3���� �̷���� �迭
	char *arr2[3];//char�� ������ ���� 3���� �̷���� �迭 (������ �迭)
	char (*arr3)[3];//char�� ����3���� �迭�� ����Ű�� ������ ���� (�迭 ������)

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