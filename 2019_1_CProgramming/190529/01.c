# include <stdio.h>

int main(void)
{
	char *p = "apple";  // *p�� apple�� �� ó�� ������ a�� ��ġ�� �ʱ�ȭ
	char str[20];
	int i;

	printf("*p is %c.\n", *p);  
	printf("Last character of apple is %c.\n", *("apple" + 4));  // *("apple" +4) = *(p+4), apple�� ������ ���� 'e'

	printf("Enter a string.\n");
	scanf("%s", str);  //���ڿ��� �Է¹޾� �迭str�� ����

	printf("%s\n", str);
	for (i = 0; str[i] != '\0'; i++)  //�迭�� ó������ ������ �ϳ��� ���
		printf("%c", str[i]);
	printf("\n");
	return 0;
}