#include <stdio.h>

struct stu
{
	unsigned int hak;
	char name[20];
};

struct ce  //구조체안의 구조체 정의
{
	struct stu a; 
	char grade;
};

int main(void)
{
	struct ce ex1; //ex1이 갖는 변수 3개 (ex1.a.hak,ex1.a.name, ex1.grade)
	printf("학번, 이름, 학년\n");
	scanf("%d %s %d", &ex1.a.hak, ex1.a.name, &ex1.grade); //참조 형태 주의

	printf("%d %s %d", ex1.a.hak,ex1.a.name, ex1.grade);
	return 0;
}