# include <stdio.h>

int main(void)
{
	int a, b;
	for (a = 0; a < 10; a++)   // 10�� ���
	{
		b = 9 - a;          // ���� ���� ���
		for (; b > 0; b--)
			printf(" ");
		b = 2 * a + 1;          // * ���� ���
		for (; b > 0; b--)
			printf("*");
		printf("\n");
	}
	return 0;
}
