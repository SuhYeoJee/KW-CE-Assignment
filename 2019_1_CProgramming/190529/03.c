# include <stdio.h>

int main(void)
{
	int *a, aa;
	char *b, bb;
	double *c, cc;
	int*d[3] = { &aa,&bb,&cc }; //배열d 에는 aa,bb,cc의 주솟값이 저장

	printf("%d \n", sizeof(a)); //int형 포인터변수 a의 크기 출력
	printf("%d \n", sizeof(b)); //char형 포인터변수 b의 크기 출력
	printf("%d \n", sizeof(c)); //double형 포인터변수 c의 크기 출력

	printf("\n");

	printf("%#p \n", d); //d의 포인터 출력 &d[0]과 같음
	printf("\n");
	printf("%#p \n", d[0]); // d[0] == &aa
	printf("%#p \n", &d[0]); //배열 d의 첫 번째 성분 위치 출력 
	printf("\n");
	printf("%#p \n", d[1]); // d[1] == &bb
	printf("%#p \n", &d[1]); //배열 d의 두 번째 위치 출력 d[0]+4
	printf("\n");
	printf("%#p \n", d[2]); // d[2] == &cc
	printf("%#p \n", &d[2]); //배열 d의 마지막 위치 출력 d[1] +4

	printf("\n");

	printf("printf(\"%%#p \\n\", d[0]); 와 같은 값\n");
	printf("%#p \n", &aa);
	printf("%#p \n", *d);
	printf("\n");

	printf("printf(\"%%#p \\n\", d[1]); 와 같은 값\n");
	printf("%#p \n", &bb);
	printf("%#p \n", *(d+1));
	printf("\n");

	printf("printf(\"%%#p \\n\", d[2]); 와 같은 값\n");
	printf("%#p \n", &cc);
	printf("%#p \n", *(d+2));
}