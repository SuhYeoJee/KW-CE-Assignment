#include <stdio.h>
//12:37~1:03 26분

void merge(int *A, int*B, int*C, int size);

int main(void)
{
	int A[] = { 1,3,4,6 };
	int B[] = { 2,5,7,8 };
	int C[8];

	merge(A, B, C, sizeof(C) / sizeof(int));
	return 0;
}

void merge(int *A, int*B, int*C, int size)
{
	int a=0, b=0, i;

	for (i=0;i<size;i++)
	{ //비교해서 작은 값 복사
		C[i] = (A[a] < B[b]) ? A[a] : B[b];
		if (A[a] < B[b])
			a++;
		else
			b++;

		if (a == 4) //A가 끝남
		{
			while (b < 4) // 나머지 복사
				C[++i] = B[b++];
		}
		else if (b == 4) //B가 끝남
		{
			while (a < 4) // 나머지 복사
				C[++i] = A[a++];
		}

	}
	//결과 출력
	printf("A[]=");
	for (i=0;i<4;i++)
		printf(" %d", A[i]);
	printf("\n");
	printf("B[]=");
	for (i = 0; i<4; i++)
		printf(" %d", B[i]);
	printf("\n");
	printf("C[]=");
	for (i = 0; i<size; i++)
		printf(" %d", C[i]);
	printf("\n");
}