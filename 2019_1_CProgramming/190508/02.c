# include <stdio.h>

int sumFunc(int count)
{
	if (count == 1)
		return 1;
	else
		return count + sumFunc(count - 1);
}


int main(void)
{
	int a;
	printf("�հ踦 ���ϴ� ������ �Է��ϼ���: ");
	scanf("%d", &a);
	printf("1���� %d������ ��: %d", a, sumFunc(a));
}