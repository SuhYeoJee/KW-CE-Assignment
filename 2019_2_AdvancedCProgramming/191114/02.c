#include <stdio.h>
//1:47~2:12
int main(void)
{
	int i,j;
	int s[10];
	int t;
	int *ptr;

	for (i = 0; i < 10; i++)
	{
		printf("0~9������ ���� �ѹ��� �Է��ϱ� %d��°: ", i + 1);
		scanf("%d", &s[i]);
	}

	printf("���� �� �迭 a==>");
	for (i = 0; i < 10; i++)
	{
		printf("%d ",s[i]);
	}

	// �迭 ����
	for (i = 0; i < 9; i++) //i(1~8)
	{
		ptr = s;
		for (j = i+1; j < 10; j++) //j(1~9,2~9,3~9,4~9...)
		{
			if (*(ptr+i) < *(ptr + j));
			else
			{
				t = *(ptr+i);
				*(ptr+i) = *(ptr + j);
				*(ptr + j) = t;
			}
		}
	}

	printf("\n���� �� �迭 a==>");
	for (i = 0; i < 10; i++)
	{
		printf("%d ", s[i]);
	}
	printf("\n");
	return 0;
}