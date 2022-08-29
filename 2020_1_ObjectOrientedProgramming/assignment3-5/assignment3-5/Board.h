#pragma once
#include "Block.h"

class MyBoard {
private:
	MyBlock* m_pHead;
public:
	MyBoard(); // 보드 생성 (block할당), 좌표할당
	~MyBoard(); // MyBlock 메모리 해제

	MyBlock* gotoxy(int x, int y); //(x,y)이동
	void print(void); // 보드 출력
	int IsEnd(void); // 종료조건 확인
	bool IsFull(void);

	// 랜덤 2 생성 함수
		// 2를 만들 자리가 있는가? IsEnd
		// 무작위 좌표(num == 0 )에 2 생성
	bool random2(void);

	// 동작
	bool Up();
	bool Down();
	bool Left();
	bool Right();

};
