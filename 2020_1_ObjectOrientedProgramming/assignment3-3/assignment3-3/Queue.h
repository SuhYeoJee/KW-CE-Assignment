#pragma once
#include "Node.h"

class Queue {
private:
	BSTNode* head;
	BSTNode* tail;
	int size;
public:
	Queue();
	~Queue();

	bool IsEmpty(void);
	void Push(BSTNode* push); // �� ��� �߰�
	int Pop(void); // ��� ����
	BSTNode* Front(void); //ť�� head �ּ� ��ȯ

};
