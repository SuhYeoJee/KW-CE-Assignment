#include <stdio.h>

void ShowData(const int *ptr) //const변수 선언을 통해 ptr이 가르키는 값을 수정하지 않음
{
	int *rptr = ptr;
	printf("%d \n", *rptr);
	*rptr = 20;  // rptr을 통해 ptr이 가르키는 값을 수정할 수 있음
}


int main(void)
{
	int num = 10;
	int*ptr = &num;
	ShowData(ptr);
	return 0;
}