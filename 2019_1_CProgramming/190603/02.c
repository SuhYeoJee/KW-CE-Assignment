# include <stdio.h>
// 09:37~ 09:44

void Swap3(int*ptr1, int*ptr2, int*ptr3) //���� �ڹٲٴ� �Լ�
{
	int temp = *ptr1;
	*ptr1 = *ptr3;
	*ptr3 = *ptr2;
	*ptr2 = temp;
}

int main(void)
{
	int num1 = 1, num2 = 2, num3 = 3; //������ �� ����

	printf("�� ������ �� %d %d %d \n", num1, num2, num3);
	Swap3(&num1, &num2, &num3); //�Լ� ȣ��
	printf("������ �� �� %d %d %d \n", num1, num2, num3);
	return 0;
}