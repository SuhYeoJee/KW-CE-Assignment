# include <stdio.h>

// 8진수, 10진수, 16진수로 표현하기

int main(void)
{
	int result;
	int num1=0x21, num2=0x12, num3=021, num4=012;

	printf("0x21의 8진수 정수 값: %o \n", num1);
	printf("0x21의 10진수 정수 값: %d \n",num1);
	printf("0x21의 16진수 정수 값: %x \n\n", num1);
	
	printf("0x12의 8진수 정수 값: %o \n", num2);
	printf("0x12의 10진수 정수 값: %d \n", num2);
	printf("0x12의 16진수 정수 값: %x \n\n", num2);

	printf("%o + %o  = %o \n", num1, num2, num1 + num2);
	printf("%d + %d  = %d \n", num1, num2, num1 + num2);
	printf("%x + %x  = %x \n\n", num1, num2, num1 + num2);

	printf("021의 8진수 정수 값: %o \n", num3);
	printf("021의 10진수 정수 값: %d \n", num3);
	printf("021의 16진수 정수 값: %x \n\n", num3);

	printf("012의 8진수 정수 값: %o \n", num4);
	printf("012의 10진수 정수 값: %d \n", num4);
	printf("012의 16진수 정수 값: %x \n\n", num4);

	printf("%o + %o  = %o \n", num1, num2, num3 + num4);
	printf("%d + %d  = %d \n", num1, num2, num3 + num4);
	printf("%#x + %#x  = %#x \n", num1, num2, num3 + num4);

	return 0;
}
