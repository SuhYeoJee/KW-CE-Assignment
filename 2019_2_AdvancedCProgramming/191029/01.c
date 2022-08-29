#include <stdio.h>

typedef struct point
{
	int xpos;
	int ypos;
} Point;

void SwapPoint(Point *pos1, Point * pos2);

int main(void)
{
	Point pos1 = { 2,4 }; //구조체 초기화
	Point pos2 = { 5,7 };

	SwapPoint(&pos1, &pos2);

	printf("pos1.xpos: %d \npos1.ypos: %d\n\n", pos1.xpos, pos1.ypos); //결과출력
	printf("pos2.xpos: %d \npos2.ypos: %d\n", pos2.xpos, pos2.ypos);

	return 0;
}

void SwapPoint(Point *pos1, Point * pos2) //값 변경
{
	Point pos3;

	pos3 = *pos2;
	*pos2 = *pos1;
	*pos1 = pos3;
}
