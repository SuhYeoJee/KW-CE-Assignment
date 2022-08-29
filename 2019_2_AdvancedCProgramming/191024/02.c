#include <stdio.h>

struct point
{
	int xpos;
	int ypos;
	struct point * ptr1; //앞에 연결되는 주소 저장
	struct point * ptr2; //뒤에 연결되는 주소 저장
};

int main(void)
{
	struct point pos1 = { 1,1 };
	struct point pos2 = { 2,2 };
	struct point pos3 = { 3,3 };

	pos1.ptr1 = &pos3; pos1.ptr2 = &pos2; //앞, 뒤 연결
	pos2.ptr1 = &pos1; pos2.ptr2 = &pos3;
	pos3.ptr1 = &pos2; pos3.ptr2 = &pos1;

	printf("점의 연결 관계\n");
	printf("[%d, %d] - [%d, %d] - [%d, %d]\n",
		pos1.ptr1->xpos, pos1.ptr1->ypos, pos1.xpos, pos1.ypos,
		pos1.ptr2->xpos, pos1.ptr2->ypos);
	printf("[%d, %d] - [%d, %d] - [%d, %d]\n",
		pos2.ptr1->xpos, pos2.ptr1->ypos, pos2.xpos, pos2.ypos,
		pos2.ptr2->xpos, pos2.ptr2->ypos);
	printf("[%d, %d] - [%d, %d] - [%d, %d]\n",
		pos3.ptr1->xpos, pos3.ptr1->ypos, pos3.xpos, pos3.ypos,
		pos3.ptr2->xpos, pos3.ptr2->ypos);

	return 0;
}