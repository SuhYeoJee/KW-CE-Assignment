#include <stdio.h>

int main(void)
{
	int arr[3] = { 0,1,2 };
	printf("�迭�� �̸�: %p \n", arr);
	printf("ù ��° ���: %p,%d\n", &arr[0], &arr[0]);
	printf("�� ��° ���: %p,%d\n", &arr[1], &arr[1]);
	printf("�� ��° ���: %p,%d\n", &arr[2], &arr[2]);
	return 0;
}