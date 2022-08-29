#include <stdio.h>

int main(void)
{
	char str1[] = "My String"; //문자열 변수로 저장
	char*str2 = "Your String"; //문자열 상수로 저장
	printf("%s %s %p \n", str1, str2,str2);

	str2 = "Our String";
	printf("%s %s %p \n", str1, str2,str2);

	str1[0] = 'X';
	// str2[0] = 'X';
	printf("%s %s \n", str1, str2);
	return 0;
}