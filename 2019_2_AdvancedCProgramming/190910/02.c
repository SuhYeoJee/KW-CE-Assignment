#include <stdio.h>

int main(void)
{
	char str1[] = "My String";
	char * str2 = "Your String";
	printf("%s %p %s %p\n", str1, str1, str2, str2);

	str2 = "Our String";
	printf("%s %p %s %p\n", str1, str1, str2, str2);
	
	str1[0] = 'X';
	//str2[0] = 'X';
	printf("%s %p %s %p\n", str1, str1, str2, str2);

	return 0;
}