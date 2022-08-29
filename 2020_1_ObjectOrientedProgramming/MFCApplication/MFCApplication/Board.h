#pragma once
#include "Block.h"
#include <fstream>

class MyBoard {
private:
	MyBlock* m_pHead;
public:
	MyBoard(); // ���� ���� (block�Ҵ�), ��ǥ�Ҵ�
	~MyBoard(); // MyBlock �޸� ����

	MyBlock* gotoxy(int x, int y); //(x,y)�̵�

	MyBlock* getHead(void);
	void setHead(MyBlock* temp);
	void print(void); // ���� ���
	int IsEnd(void); // �������� Ȯ��
	bool IsFull(void);

	// ���� 2 ���� �Լ�
		// 2�� ���� �ڸ��� �ִ°�? IsEnd
		// ������ ��ǥ(num == 0 )�� 2 ����
	bool random2(void);

	// ����
	bool Up();
	bool Down();
	bool Left();
	bool Right();

	void TurnCW();
	void TurnCCW();
};