#include <stdio.h>

/*
int main(void)
{
	int ch1, ch2;

	ch1 = getchar();
	ch2 = fgetc(stdin);

	putchar(ch1);
	fputc(ch2, stdout);
	return 0;
}*/

/*
int main(void)
{
	int ch;

	while (1)
	{
		ch = getchar();
		if (ch == EOF)
			break;
		putchar(ch);
	}
	return 0;
}*/

/*
int main(void)
{
	//char *str = "aaa";
	//char *str2 = "aaa";

	printf("%d\n%d\n%c\n", "str", "str"+1,*("str"+1));
	return 0;
	
}*/

int main(void)
{
	int a;
	a = getchar();
	a = (a < 107) ? a + 32 : a - 32;
	putchar(a);
	return 0;
}