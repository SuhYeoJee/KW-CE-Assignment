#include <stdio.h>

void ShowData(const int *ptr) //const���� ������ ���� ptr�� ����Ű�� ���� �������� ����
{
	int *rptr = ptr;
	printf("%d \n", *rptr);
	*rptr = 20;  // rptr�� ���� ptr�� ����Ű�� ���� ������ �� ����
}


int main(void)
{
	int num = 10;
	int*ptr = &num;
	ShowData(ptr);
	return 0;
}