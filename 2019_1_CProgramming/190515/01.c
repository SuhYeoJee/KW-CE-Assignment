#include <stdio.h> // 10:52 ~ 11:28

int main(void)
{
	char str[50];
	int i,a,b=0;

	printf("영단어 입력: ");
	scanf("%s", str);
	printf("입력한 영단어: %s\n", str);

	for (i = 0; str[i] != '\0'; i++)  //영단어의 글자 수
		b++;
	b -= 1;  //마지막 인덱스

	for (i = 0; i!=b; i++)  //순서 뒤집기
	{
		a = str[i];
		str[i] = str[b];
		str[b] = a;
		b--;
	}
	printf("뒤집은 영단어: %s\n", str);

	return 0;
}