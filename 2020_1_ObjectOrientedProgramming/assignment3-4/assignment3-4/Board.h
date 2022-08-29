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

	OthelloBoard* gotoxy(int x, int y); // x,y ĭ���� ������ �̵�

	void SetBoard(void);// ���Ḯ��Ʈ ����, �ʱ� ����
	void PrintBoard(void);// ���� ���

	// �� �� ����
	bool NewStone(int player, int x, int y);
	bool IsPossible(int player, int x, int y); // ���� Ȯ��
	void SetStone(int player, int x, int y); // ����
	void Turn(int player, OthelloBoard* temp); // ������

	int IsEnd(int end);// �������� Ȯ��
	bool IsSkip(int player); // ���ʸ� �ǳ� �ٴ��� Ȯ��
	void DeleteBoard(void);// ����Ʈ ����

	// ���⿡ ���� �Ǵ� �Լ�
	bool IsPossible_R(int player, OthelloBoard* add);
	bool IsPossible_L(int player, OthelloBoard* add);
	bool IsPossible_U(int player, OthelloBoard* add);
	bool IsPossible_D(int player, OthelloBoard* add);
	bool IsPossible_UR(int player, OthelloBoard* add);
	bool IsPossible_UL(int player, OthelloBoard* add);
	bool IsPossible_DR(int player, OthelloBoard* add);
	bool IsPossible_DL(int player, OthelloBoard* add);

	// ���⿡ ���� ������ �Լ�
	void Turn_R(OthelloBoard* add);
	void Turn_L(OthelloBoard* add);
	void Turn_U(OthelloBoard* add);
	void Turn_D(OthelloBoard* add);
	void Turn_UR(OthelloBoard* add);
	void Turn_UL(OthelloBoard* add);
	void Turn_DR(OthelloBoard* add);
	void Turn_DL(OthelloBoard* add);

};
