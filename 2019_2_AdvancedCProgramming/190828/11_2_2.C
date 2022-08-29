#include <stdio.h>

int main(void)
{
	char arr[30],a=0;
	int i, s=0;

	printf("영단어 입력\n");
	scanf("%s", &arr);

	for (i = 0; arr[i] != NULL; i++)
		s++;
	s -= 1;
	for (i = 0; i<=s-i; i++)
	{
		a = arr[s-i];
		arr[s-i] = arr[i];
		arr[i] = a;
	}

	for (i = 0; arr[i] != NULL; i++)
		printf("%c", arr[i]);

	return 0;
}