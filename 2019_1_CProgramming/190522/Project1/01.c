# include <stdio.h>
// 08:54 ~ 09:07
int main(void)
{
	int arr[5] = { 1, 2, 3, 4, 5 };
	int * ptr = &arr[0];
	int i;

	for (i=0; i<5;i++)  //ptr�� ����� �� +2
	{
		*ptr += 2;
		ptr++;
	}

	for (i=0; i<5; i++)  //��� Ȯ��
	printf("%d ", arr[i]);
	return 0;
}