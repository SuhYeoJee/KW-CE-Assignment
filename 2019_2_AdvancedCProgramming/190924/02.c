#include <stdio.h>

int main(void)
{
	int a = 10, b = 20;
	int *pa = &a, *pb = &b;
	int **ppa = &pa, **ppb = &pb;
	int *pt;

	pt = *ppa;
	*ppa = *ppb;
	*ppb = pt;

	printf("a: %9p *pa: %9p **ppa: %9p\n", &a, &(*pa), &(**ppa));
	printf("b: %9p *pb: %9p **ppb: %9p\n", &b, &(*pb), &(**ppb));
	printf("*pt: %9p", &(*pt));

	return 0;
}