#include <stdio.h>

int main(void)
{
	int arr[3] = { 0,1,2 };
	printf("배열의 이름: %p \n", arr);
	printf("첫 번째 요소: %p,%d\n", &arr[0], &arr[0]);
	printf("두 번째 요소: %p,%d\n", &arr[1], &arr[1]);
	printf("세 번째 요소: %p,%d\n", &arr[2], &arr[2]);
	return 0;
}