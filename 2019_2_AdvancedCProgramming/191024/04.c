#include <stdio.h>

#pragma pack(2)

struct e1
{
	char a;
	int b;
	double c;
	char d;
};


struct e2
{
	char a;
	char d;
	int b;
	double c;
};

int main(void)
{
	struct e1 e1;
	struct e2 e2;

	printf("e1 크기와 각 요소의 주소값: %d\n", sizeof e1);
	printf("%p %p %p %p\n", &e1.a, &e1.b, &e1.c, &e1.d);
	printf("각 요소의 크기: %d %d %d %d\n\n",
		sizeof(e1.a), sizeof(e1.b), sizeof(e1.c), sizeof(e1.d));

	printf("e2 크기와 각 요소의 주소값: %d\n", sizeof e2);
	printf("%p %p %p %p\n", &e2.a, &e2.d, &e2.b, &e2.c);
	printf("각 요소의 크기: %d %d %d %d\n\n",
		sizeof(e2.a), sizeof(e2.d), sizeof(e2.b), sizeof(e2.c));

	return 0;
}