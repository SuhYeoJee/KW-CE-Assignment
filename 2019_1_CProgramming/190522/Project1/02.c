# include <stdio.h>
// 09:08~09:12
int main(void)
{
	int arr[5] = { 1, 2, 3, 4, 5 };
	int * ptr = &arr[0];
	int i;

	for (i = 0; i < 5; i++)
	{
		*(ptr+i) += 2; // ptr+i �� �ּ� ���� ��ȯ
	}

	for (i = 0; i < 5; i++) //��� Ȯ��
		printf("%d ", arr[i]);
	return 0;
}