# include <stdio.h>

int main(void)
{
	int *a, aa;
	char *b, bb;
	double *c, cc;
	int*d[3] = { &aa,&bb,&cc }; //�迭d ���� aa,bb,cc�� �ּڰ��� ����

	printf("%d \n", sizeof(a)); //int�� �����ͺ��� a�� ũ�� ���
	printf("%d \n", sizeof(b)); //char�� �����ͺ��� b�� ũ�� ���
	printf("%d \n", sizeof(c)); //double�� �����ͺ��� c�� ũ�� ���

	printf("\n");

	printf("%#p \n", d); //d�� ������ ��� &d[0]�� ����
	printf("\n");
	printf("%#p \n", d[0]); // d[0] == &aa
	printf("%#p \n", &d[0]); //�迭 d�� ù ��° ���� ��ġ ��� 
	printf("\n");
	printf("%#p \n", d[1]); // d[1] == &bb
	printf("%#p \n", &d[1]); //�迭 d�� �� ��° ��ġ ��� d[0]+4
	printf("\n");
	printf("%#p \n", d[2]); // d[2] == &cc
	printf("%#p \n", &d[2]); //�迭 d�� ������ ��ġ ��� d[1] +4

	printf("\n");

	printf("printf(\"%%#p \\n\", d[0]); �� ���� ��\n");
	printf("%#p \n", &aa);
	printf("%#p \n", *d);
	printf("\n");

	printf("printf(\"%%#p \\n\", d[1]); �� ���� ��\n");
	printf("%#p \n", &bb);
	printf("%#p \n", *(d+1));
	printf("\n");

	printf("printf(\"%%#p \\n\", d[2]); �� ���� ��\n");
	printf("%#p \n", &cc);
	printf("%#p \n", *(d+2));
}