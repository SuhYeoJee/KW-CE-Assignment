#include <stdio.h>
//2:13~2:19
typedef struct point
{
	int x;
	int y;
}POINT;

struct rectangle
{
	int width;
	POINT p[2]; //����ü�迭
};

int main(void)
{

	int a, b;

	struct rectangle rect;
	POINT rightTop = { 7,10 };
	POINT leftDown = { 3,5 };

	rect.p[0] = rightTop; //rect.p[0]�� ������ ���� ��
	rect.p[1] = leftDown; //rect.p[1]�� ���� �Ʒ��� �� ����

	a = rect.p[0].x - rect.p[1].x; //a�� ���� ���� ����
	b = rect.p[0].y - rect.p[1].y; //b�� ���� ���� ����

	printf("����: %d, ����:%d, �簢���� ����: %d �̴�.\n", a, b, a*b);
	return 0;
}