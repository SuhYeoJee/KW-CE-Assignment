# include <stdio.h>
// 09:13~09:15
int main(void)
{
	int arr[5] = { 1, 2, 3, 4, 5 };
	int * ptr = &arr[4];
	int i,num1=0;

	for (i = 0; i < 5; i++)
	{
		num1 += *ptr; //정수를 더함
		ptr--;  //prt에 저장된 값을 감소시킴
	}

	printf("%d", num1); //결과 확인
	return 0;
}