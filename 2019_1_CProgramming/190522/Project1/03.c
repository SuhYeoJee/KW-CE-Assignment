# include <stdio.h>
// 09:13~09:15
int main(void)
{
	int arr[5] = { 1, 2, 3, 4, 5 };
	int * ptr = &arr[4];
	int i,num1=0;

	for (i = 0; i < 5; i++)
	{
		num1 += *ptr; //������ ����
		ptr--;  //prt�� ����� ���� ���ҽ�Ŵ
	}

	printf("%d", num1); //��� Ȯ��
	return 0;
}