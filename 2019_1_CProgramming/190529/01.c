# include <stdio.h>

int main(void)
{
	char *p = "apple";  // *p는 apple의 맨 처음 글자인 a의 위치로 초기화
	char str[20];
	int i;

	printf("*p is %c.\n", *p);  
	printf("Last character of apple is %c.\n", *("apple" + 4));  // *("apple" +4) = *(p+4), apple의 마지막 문자 'e'

	printf("Enter a string.\n");
	scanf("%s", str);  //문자열을 입력받아 배열str에 저장

	printf("%s\n", str);
	for (i = 0; str[i] != '\0'; i++)  //배열을 처음부터 끝까지 하나씩 출력
		printf("%c", str[i]);
	printf("\n");
	return 0;
}