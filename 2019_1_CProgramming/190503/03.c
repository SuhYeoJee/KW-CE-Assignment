# include <stdio.h>

int main(void)
{
	int a, b;
	for (a = 0; a < 10; a++)   // 10줄 출력
	{
		b = 9 - a;          // 공백 개수 계산
		for (; b > 0; b--)
			printf(" ");
		b = 2 * a + 1;          // * 개수 계산
		for (; b > 0; b--)
			printf("*");
		printf("\n");
	}
	return 0;
}
