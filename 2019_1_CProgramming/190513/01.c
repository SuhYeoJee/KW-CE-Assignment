# include <stdio.h>

int main(void)
{
	int arr[100];
	int sum = 0, i;

	for (i = 0; i < 100; i++)
		arr[i] = i * 10 + 10;


	for (i = 0; i < 100; i++)
		sum += arr[i];

	printf("배열요소에 저장된 값의 합: %d \n", sum);
	printf("arr[0] = %d \n", arr[0]);
	printf("arr[5] = %d \n", arr[5]);
	printf("arr[73] = %d \n", arr[73]);

	return 0;
}