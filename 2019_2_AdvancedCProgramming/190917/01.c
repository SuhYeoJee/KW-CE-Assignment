# include <stdio.h>
// 12:30~12:37 7��
int main(void)
{
	int a[] = { 1,2,3,4 };
	int * p=a;

	
	//printf("%d", *p++); // 1, ���� �����ʹ� a[1] ����Ŵ
	//printf("%d", (*p)++); //1, ���� a[0]=2
	//printf("%d", *++p); //2, �����Ͱ� a[1] ����Ŵ
	printf("%d ", ++*p); //2, ���� a[0]=2
	
	printf("%d ", *p);
	printf("%d ", a[0]);
	return 0;
}