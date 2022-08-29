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
		printf("0~9사이의 숫자 한번씩 입력하기 %d번째: ", i + 1);
		scanf("%d", &s[i]);
	}

	printf("정렬 전 배열 a==>");
	for (i = 0; i < 10; i++)
	{
		printf("%d ",s[i]);
	}

	// 배열 정렬
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

	printf("\n정렬 후 배열 a==>");
	for (i = 0; i < 10; i++)
	{
		printf("%d ", s[i]);
	}
	printf("\n");
	return 0;
}