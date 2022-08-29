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
	POINT p[2]; //구조체배열
};

int main(void)
{

	int a, b;

	struct rectangle rect;
	POINT rightTop = { 7,10 };
	POINT leftDown = { 3,5 };

	rect.p[0] = rightTop; //rect.p[0]에 오른쪽 위의 점
	rect.p[1] = leftDown; //rect.p[1]에 왼쪽 아래의 점 저장

	a = rect.p[0].x - rect.p[1].x; //a에 가로 길이 저장
	b = rect.p[0].y - rect.p[1].y; //b에 세로 길이 저장

	printf("가로: %d, 세로:%d, 사각형의 넓이: %d 이다.\n", a, b, a*b);
	return 0;
}