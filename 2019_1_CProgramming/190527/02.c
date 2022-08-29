# include <stdio.h>
// 9:33~10:05 + 12:50~01:04

void BP(int s[])  // 10자리 정수 배열을 출력하는 함수
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

	for (i = 0; i < 10; i++)  // 배열 입력
	{
		printf("0~9 사이의 숫자 한 번씩 입력하기 %d 번째: ", i+1);
		scanf("%d", &s[i]);
	}

	printf("정렬 전 배열 ==> ");
	BP(s);
	
	for (b=0; b < 9; b++)  // 배열 정렬
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

	printf("정렬 후 배열 ==> ");
	BP(s);

	return 0;
}

