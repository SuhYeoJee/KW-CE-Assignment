#include <stdio.h>

struct stu
{
	unsigned int hak;
	char name[20];
};

struct ce  //����ü���� ����ü ����
{
	struct stu a; 
	char grade;
};

int main(void)
{
	struct ce ex1; //ex1�� ���� ���� 3�� (ex1.a.hak,ex1.a.name, ex1.grade)
	printf("�й�, �̸�, �г�\n");
	scanf("%d %s %d", &ex1.a.hak, ex1.a.name, &ex1.grade); //���� ���� ����

	printf("%d %s %d", ex1.a.hak,ex1.a.name, ex1.grade);
	return 0;
}