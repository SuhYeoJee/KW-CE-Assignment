# include <stdio.h>
// 09:37~ 09:44

void Swap3(int*ptr1, int*ptr2, int*ptr3) //값을 뒤바꾸는 함수
{
	int temp = *ptr1;
	*ptr1 = *ptr3;
	*ptr3 = *ptr2;
	*ptr2 = temp;
}

int main(void)
{
	int num1 = 1, num2 = 2, num3 = 3; //변수에 값 저장

	printf("세 변수의 값 %d %d %d \n", num1, num2, num3);
	Swap3(&num1, &num2, &num3); //함수 호출
	printf("변수의 새 값 %d %d %d \n", num1, num2, num3);
	return 0;
}