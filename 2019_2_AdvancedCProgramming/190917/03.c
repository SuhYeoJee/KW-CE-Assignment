#include <stdio.h>
#include <string.h>
//1:04~1:08, 1:50~2:30 44분
void format_display(char money[]);

int main(void)
{
	char money[30];


	printf("단위를 뺀 금액 입력하고 Enter> ");
	scanf("%s", money);

	format_display(money);
	return 0;
}

void format_display(char money[])
{
	int len = strlen(money);
	int i=1,k,n,a;

	k = len / 3; // 쉼표 개수
	if (len % 3 == 0)
		--k;
	n = len + k;

	for (k;k>0;k--) //쉼표의 개수만큼 반복
	{
		for (a = 1; a < 4; a++) //3개의 숫자를 이동
			money[len - i + k] = money[len - i++];
		money[len - i + k] = ','; // 숫자사이 , 삽입
	}

	for (i = 0; i < n; i++) //문자열 출력
		printf("%c", money[i]);
}