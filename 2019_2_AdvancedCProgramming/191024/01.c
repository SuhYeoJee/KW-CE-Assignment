#include <stdio.h>

/*
struct person
{
	char name[20];
	char phonenum[20];
	int age;
};



int main(void)
{
	struct person arr[3] = {0,};
		//{"이승기","010-1212-0001",21},
		//{ "정지영","010-1313-0002",22 },
		//{ "한지수","010-1717-0003",19 },
	//};
	int i;
	for (i = 0; i < 3; i++)
	{
		printf("name: %s", arr[i].name);
		printf("  phonenum: %s", arr[i].phonenum);
		printf("  age: %d\n", arr[i].age);
		printf("%d", sizeof e1);
	}
	return 0;

}
*/


struct e1
{
	int a;
	char b[5];
	char c;
};

struct e2
{
	struct e1 aa;
	double bb;
};

int main(void)
{
	struct e1 e1;
	struct e2 e2;

	printf("%d\n", sizeof e1);
	printf("%d\n", sizeof e2);
	return 0;

}