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
	void Push(BSTNode* push); // 새 노드 추가
	int Pop(void); // 노드 삭제
	BSTNode* Front(void); //큐의 head 주소 반환

};
