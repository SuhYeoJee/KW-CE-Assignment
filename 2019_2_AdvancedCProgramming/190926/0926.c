#include <stdio.h>
// 3:15 ~ 5:04 ~

void yeo(int(*ptr1)[12], int haeng);
void jee(int(*ptr1)[12], int haeng);
int main(void)
{
	char arr[7][12] = { 0 };
	int haeng = sizeof(arr) / sizeof(arr[0]);
	int(*ptr)[12] = &arr;
	int i = 0;

	for (i = 0; i < haeng; i++)
	{
		yeo(ptr, i);
	}
}

void yeo(int(*ptr1)[12], int haeng)
{
	int a,c;
	if ((haeng == 0 )|| (haeng == 6))
	{
		for (a = 0; a < 12; a++)
		{
			c = ((2<a && a<6 )|| a == 11) ? 64 :32;
			printf("%c",c);
		}
	}
	if ((haeng == 1) || (haeng == 5))
	{
		for (a = 0; a < 12; a++)
		{
			c = (a==2||a==6||a==11) ? 64 : 32;
			printf("%c", c);
		}
	}
	if ((haeng == 2) || (haeng == 4))
	{
		for (a = 0; a < 12; a++)
		{
			c = (a == 1 || a == 7 || (8<a&&a<12)) ? 64 : 32;
			printf("%c", c);
		}
	}
	if (haeng == 3)
	{
		for (a = 0; a < 12; a++)
		{
			c = (a == 1 || a == 7 || a == 11) ? 64 : 32;
			printf("%c", c);
		}
	}
	jee(ptr1,haeng);
}

void jee(int(*ptr2)[12], int haeng)
{
	int a, c;
	if (haeng == 0)
	{
		for (a = 0; a < 12; a++)
		{
			c = ((0< a && a < 8) || a == 10) ? 64 : 32;
			printf("%c", c);
		}
	}
	if (haeng == 1)
	{
		for (a = 0; a < 12; a++)
		{
			c = (a==6|| a == 10) ? 64 : 32;
			printf("%c", c);
		}
	}
	if (haeng == 2)
	{
		for (a = 0; a < 12; a++)
		{
			c = (a == 5 || a == 10) ? 64 : 32;
			printf("%c", c);
		}
	}
	if (haeng == 3)
	{
		for (a = 0; a < 12; a++)
		{
			c = (a == 4
 || a == 10) ? 64 : 32;
			printf("%c", c);
		}
	}
	if (haeng == 4)
	{
		for (a = 0; a < 12; a++)
		{
			c = (a == 3||a==5 || a == 10) ? 64 : 32;
			printf("%c", c);
		}
	}
	if (haeng == 5)
	{
		for (a = 0; a < 12; a++)
		{
			c = (a ==2|| a == 6 || a == 10) ? 64 : 32;
			printf("%c", c);
		}
	}
	if (haeng == 6)
	{
		for (a = 0; a < 12; a++)
		{
			c = (a == 1 || a == 7 || a == 10) ? 64 : 32;
			printf("%c", c);
		}
	}
	printf("\n");
}
