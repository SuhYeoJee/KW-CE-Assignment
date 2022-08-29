#include <stdio.h>

int main(void)
{
	char arr[7][7] = {0};
	int i, j;
	int A=sizeof(arr)/sizeof(arr[0]), B=sizeof(arr[0])/sizeof(arr[0][0]);

	for (i = 0; i < A; i++)
	{
		for (j = 0; j < B; j++)
		{
			printf(" ");
			if (j == i) //(j == A-i-1) 
				printf("*");
		}
		printf("\n");
	}
	return 0;
}