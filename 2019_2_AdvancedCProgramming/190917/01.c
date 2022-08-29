# include <stdio.h>
// 12:30~12:37 7분
int main(void)
{
	int a[] = { 1,2,3,4 };
	int * p=a;

	
	//printf("%d", *p++); // 1, 이후 포인터는 a[1] 가르킴
	//printf("%d", (*p)++); //1, 이후 a[0]=2
	//printf("%d", *++p); //2, 포인터가 a[1] 가르킴
	printf("%d ", ++*p); //2, 이후 a[0]=2
	
	printf("%d ", *p);
	printf("%d ", a[0]);
	return 0;
}