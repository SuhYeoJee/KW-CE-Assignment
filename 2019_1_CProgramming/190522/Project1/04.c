# include <stdio.h>
// 09:16~09:24
int main(void)
{
	int arr[6] = { 1, 2, 3, 4, 5, 6 };
	int * ptr1 = &arr[0];
	int * ptr2 = &arr[5];
	int i, num1;

	for (i = 0; i < 3; i++) //3�� �ݺ�
	{
		num1 = *ptr1;
		*ptr1 = *ptr2;
		*ptr2 = num1;

		ptr1++; ptr2--; //������ �̵�
	}

	for (i = 0; i < 6; i++) //��� Ȯ��
		printf("%d ", arr[i]);

	return 0;
}
