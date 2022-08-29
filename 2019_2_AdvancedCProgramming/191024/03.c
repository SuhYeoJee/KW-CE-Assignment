#include <stdio.h>

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

struct e3
{
	int a;
	char b[5];
	char c;
};


struct e4
{
	struct e3 aa;
	char bb;
};

int main(void)
{
	struct e1 e1;
	struct e2 e2;
	struct e3 e3;
	struct e4 e4;

	printf("e1 ũ��� �� ����� �ּҰ�: %d\n", sizeof e1);
	printf("%p %p %p %p\n", &e1.a, &e1.b, &e1.c, &e1.d);
	printf("�� ����� ũ��: %d %d %d %d\n\n", 
		sizeof(e1.a), sizeof(e1.b), sizeof(e1.c), sizeof(e1.d));

	printf("e2 ũ��� �� ����� �ּҰ�: %d\n", sizeof e2);
	printf("%p %p %p %p\n", &e2.a, &e2.d, &e2.b, &e2.c);
	printf("�� ����� ũ��: %d %d %d %d\n\n",
		sizeof(e2.a), sizeof(e2.d), sizeof(e2.b), sizeof(e2.c));


	printf("e3 ũ��� �� ����� �ּҰ�: %d\n", sizeof e3);
	printf("%p %p %p\n", &e3.a, &e3.b, &e3.c);
	printf("�� ����� ũ��: %d %d %d\n\n",
		sizeof(e3.a), sizeof(e3.b), sizeof(e3.c));


	printf("e4 ũ��� �� ����� �ּҰ�: %d\n", sizeof e4);
	printf("%p %p %p %p\n", &e4.aa.a, &e4.aa.b, &e4.aa.c, &e4.bb);
	printf("�� ����� ũ��: %d %d %d %d\n\n",
		sizeof(e4.aa.a), sizeof(e4.aa.b), sizeof(e4.aa.c), sizeof(e4.bb));


	return 0;

}