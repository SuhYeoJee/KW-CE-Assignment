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
	printf("합계를 원하는 정수를 입력하세요: ");
	scanf("%d", &a);
	printf("1부터 %d까지의 합: %d", a, sumFunc(a));
}