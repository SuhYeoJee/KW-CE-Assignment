#include <stdio.h>

int main(void)
{
	int arr[] = { 11,22,33 };
	int *ptr = arr;

	printf("%d %d %d\n", *ptr, *(ptr + 1), *(ptr + 2)); // 11 22 33
	
	printf("%d",*ptr++); //11
	printf("%d",*ptr++); //22
	printf("%d",*ptr--); //33
	printf("%d",*ptr--); //22
	printf("%d",*ptr); printf("\n\n"); //11
	
	printf("%d",*(ptr++)); //11
	printf("%d",*(ptr++)); //22
	printf("%d",*(ptr--)); //33
	printf("%d",*(ptr--)); //22
	printf("%d",*ptr); printf("\n\n"); //11

	printf("%d",*(++ptr)); //22
	printf("%d",*(++ptr)); //33
	printf("%d",*(--ptr)); //22
	printf("%d",*(--ptr)); //11
	printf("%d",*ptr); printf("\n\n"); //11
	
	return 0;
}