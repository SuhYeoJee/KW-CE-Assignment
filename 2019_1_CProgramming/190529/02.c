#include <stdio.h>
#include <string.h>

int main(void)
{
	char* str1 = "Okay Buddy"; //*str1�� ���ڿ��� ���� ù ���� O�� ��ġ
	char str2[15] = "Bless you";

	printf("strlen(str1) is %d.\n",strlen(str1)); //str1�� ����� ���ڿ��� ���� ���
	printf("strlen(str2) is %d.\n", strlen(str2)); //str2�� ����� ���ڿ��� ���� ���
	printf("sizeof(str1) is %d.\n", sizeof(str1)); //str1�� ũ�� ���
	printf("sizeof(str2) is %d.\n", sizeof(str2)); //str2�� ũ�� ���
	return 0;
}