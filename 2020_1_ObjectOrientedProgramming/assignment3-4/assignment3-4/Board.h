#pragma once
#include "Stone.h"

class OthelloBoard {
private:
	OthelloStone* m_pStone;
	OthelloBoard* m_pHead;
	OthelloBoard* m_pUp;
	OthelloBoard* m_pDown;
	OthelloBoard* m_pLeft;
	OthelloBoard* m_pRight;

public:
	OthelloBoard();
	~OthelloBoard();

	OthelloBoard* gotoxy(int x, int y); // x,y 칸으로 포인터 이동

	void SetBoard(void);// 연결리스트 생성, 초기 설정
	void PrintBoard(void);// 보드 출력

	// 새 돌 놓기
	bool NewStone(int player, int x, int y);
	bool IsPossible(int player, int x, int y); // 조건 확인
	void SetStone(int player, int x, int y); // 생성
	void Turn(int player, OthelloBoard* temp); // 뒤집기

	int IsEnd(int end);// 종료조건 확인
	bool IsSkip(int player); // 차례를 건너 뛰는지 확인
	void DeleteBoard(void);// 리스트 해제

	// 방향에 따른 판단 함수
	bool IsPossible_R(int player, OthelloBoard* add);
	bool IsPossible_L(int player, OthelloBoard* add);
	bool IsPossible_U(int player, OthelloBoard* add);
	bool IsPossible_D(int player, OthelloBoard* add);
	bool IsPossible_UR(int player, OthelloBoard* add);
	bool IsPossible_UL(int player, OthelloBoard* add);
	bool IsPossible_DR(int player, OthelloBoard* add);
	bool IsPossible_DL(int player, OthelloBoard* add);

	// 방향에 따른 뒤집기 함수
	void Turn_R(OthelloBoard* add);
	void Turn_L(OthelloBoard* add);
	void Turn_U(OthelloBoard* add);
	void Turn_D(OthelloBoard* add);
	void Turn_UR(OthelloBoard* add);
	void Turn_UL(OthelloBoard* add);
	void Turn_DR(OthelloBoard* add);
	void Turn_DL(OthelloBoard* add);

};
