#include <stdio.h>

void print_arr(int(*ar)[3]);

int main(void)
{
	int ary[4][3] = { 1,2,3,4,5,6,7,8,9,10,11,12 };

	print_arr(ary);
	return 0;
}

void print_arr(int(*ar)[3])
{
	int i,j;

	for (j=0;j<4;j++) //4행 반복
	{
		for (i = 0; i<3; i++) //3열 반복
			printf("%3d ", ar[j][i]);
		printf("\n");
	}
}