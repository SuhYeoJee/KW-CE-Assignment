#include <stdio.h>

struct point
{
	int xpos;
	int ypos;
};

int main(void)
{
	struct point p1, p2;
	int x, y, ar;

	printf("��1�� ��ǥ �Է�: ");
	scanf("%d %d", &(p1.xpos), &(p1.ypos));

	printf("��2�� ��ǥ �Է�: ");
	scanf("%d %d", &(p2.xpos), &(p2.ypos));

	x = p2.xpos - p1.xpos; //���簢���� ���� ���� ���ϱ�
	y = p2.ypos - p1.ypos; //���簢���� ���� ���� ���ϱ�

	ar = (x*y > 0) ? x*y : (x*y)*(-1); //���ο� ���θ� ���� ���� �����̸� *-1
	printf("�簢���� ����: %d \n", ar);

	return 0;
}