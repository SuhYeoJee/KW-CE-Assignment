#include <stdio.h>
#include <string.h>
//1:04~1:08, 1:50~2:30 44��
void format_display(char money[]);

int main(void)
{
	char money[30];


	printf("������ �� �ݾ� �Է��ϰ� Enter> ");
	scanf("%s", money);

	format_display(money);
	return 0;
}

void format_display(char money[])
{
	int len = strlen(money);
	int i=1,k,n,a;

	k = len / 3; // ��ǥ ����
	if (len % 3 == 0)
		--k;
	n = len + k;

	for (k;k>0;k--) //��ǥ�� ������ŭ �ݺ�
	{
		for (a = 1; a < 4; a++) //3���� ���ڸ� �̵�
			money[len - i + k] = money[len - i++];
		money[len - i + k] = ','; // ���ڻ��� , ����
	}

	for (i = 0; i < n; i++) //���ڿ� ���
		printf("%c", money[i]);
}