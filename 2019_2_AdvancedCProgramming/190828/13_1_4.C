#include <stdio.h>

int main(void)
{
	int arr[6] = { 1,2,3,4,5,6 };
	int *ptr1, *ptr2;
	int i,k;
	ptr1 = &arr[0]; ptr2 = &arr[5];

	for (i = 0;i<3; i++)
	{
		k = *ptr1;
		*(ptr1++) = *ptr2;
		*(ptr2--) = k;
	}

	for (i = 0; i < 6; i++)
		printf("%d", arr[i]);

	return 0;
}