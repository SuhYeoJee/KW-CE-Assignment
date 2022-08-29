#include <stdio.h>
#include <string.h>

int main(void)
{
	char* str1 = "Okay Buddy"; //*str1은 문자열의 제일 첫 문자 O의 위치
	char str2[15] = "Bless you";

	printf("strlen(str1) is %d.\n",strlen(str1)); //str1에 저장된 문자열의 길이 출력
	printf("strlen(str2) is %d.\n", strlen(str2)); //str2에 저장된 문자열의 길이 출력
	printf("sizeof(str1) is %d.\n", sizeof(str1)); //str1의 크기 출력
	printf("sizeof(str2) is %d.\n", sizeof(str2)); //str2의 크기 출력
	return 0;
}