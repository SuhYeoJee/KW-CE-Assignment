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

	printf("점1의 좌표 입력: ");
	scanf("%d %d", &(p1.xpos), &(p1.ypos));

	printf("점2의 좌표 입력: ");
	scanf("%d %d", &(p2.xpos), &(p2.ypos));

	x = p2.xpos - p1.xpos; //직사각형의 가로 길이 구하기
	y = p2.ypos - p1.ypos; //직사각형의 세로 길이 구하기

	ar = (x*y > 0) ? x*y : (x*y)*(-1); //가로와 세로를 곱한 값이 음수이면 *-1
	printf("사각형의 넓이: %d \n", ar);

	return 0;
}