# include <stdio.h>
// 9:33~10:05 + 12:50~01:04

void BP(int s[])  // 10�ڸ� ���� �迭�� ����ϴ� �Լ�
{
	int i;
	for (i = 0; i < 10; i++)
		printf("%d ", s[i]);
	printf("\n");
}

int main(void)
{
	int s[10];
	int* p=s;
	int i,a,b;

	for (i = 0; i < 10; i++)  // �迭 �Է�
	{
		printf("0~9 ������ ���� �� ���� �Է��ϱ� %d ��°: ", i+1);
		scanf("%d", &s[i]);
	}

	printf("���� �� �迭 ==> ");
	BP(s);
	
	for (b=0; b < 9; b++)  // �迭 ����
	{
		for (i = 1; b+i <10; i++)
		{
			if (*(p + b) < *(p + b + i))
				continue;
			else
			{
				a = *(p + b + i);
				*(p + b + i) = *(p + b);
				*(p + b) = a;
			}

		}
	}

	printf("���� �� �迭 ==> ");
	BP(s);

	return 0;
}

