# include <stdio.h>

int main(void)
{
	char arr[30];
	int i,s=0;

	printf("영단어 입력\n");
	scanf("%s", &arr);

	for (i = 0; arr[i] != NULL; i++)
		s++;


	printf("입력한 영단어의 길이는 %d\n", s);
	return 0;
}