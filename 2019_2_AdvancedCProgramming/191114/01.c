#include <stdio.h>
//1:34~1:46

int main(void)
{
	char ch, *cp;
	int num, *ip;
	float f_num, *fp;
	double d_num, *dp;

	ch = 'A'; num = 100; //각각 변수에 값을 저장함
	f_num = 5.6; d_num = 17.5;

	cp = &ch; //각각 포인터에 변수의 주소를 저장함
	ip = &num;
	fp = &f_num;
	dp = &d_num;

	printf("1 증가하기 전 변수와 포인터 변수.\n"); //변수에 저장된 값과 포인터 변수에 저장된 주소를 출력
	printf("변수들의 값: %5c %5d %10.2f %10.2lf \n", ch, num, f_num, d_num);
	printf("포인터 변수에 저장된 주소 : %p %p %p %p \n\n", cp, ip, fp, dp);
	
	ch++; num++; f_num++; d_num++; //변수에 저장된 값에 1을 더함
	cp++; ip++; fp++; dp++; //포인터변수에 저장된 값에 1을 더함

	printf("1 증가한 후 변수와 포인터 변수.\n");
	printf("변수들의 값: %5c %5d %10.2f %10.2lf \n", ch, num, f_num, d_num); // 위에서 출력된 값에 +1 값이 출력됨
	printf("포인터 변수에 저장된 주소 : %p %p %p %p \n\n", cp, ip, fp, dp); // 위에서 출력된 값에 +4 값이 출력됨

	return 0;
}