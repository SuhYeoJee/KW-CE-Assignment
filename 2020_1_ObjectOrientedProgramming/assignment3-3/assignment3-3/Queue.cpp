#include <iostream>
#include "Queue.h"
using namespace std;

Queue::Queue() {
	head = nullptr;
	tail = nullptr;
	size = 0;
}

Queue::~Queue() {
	BSTNode* temp;
	while (size--) {
		temp = head;
		head = head->GetNext();
		delete temp;
	}
}

//[return: 큐가 비었을때(1), 노드가 있을 때(0)]
bool Queue::IsEmpty(void) {
	return (size == 0) ? true : false;
}

// 큐에 새 노드 추가
void Queue::Push(BSTNode* push) {
	if (size == 0) { // 큐의 첫 노드인 경우
		head = push;
		tail = push;
	}
	else { // 기존에 노드가 있는 경우
		tail->SetNext(push);
		tail = push;
	}
	tail->SetNext(nullptr);
	size++;
	return;
}

// 노드 삭제
// [return: 큐가 비었을 때(-1), 정상종료(삭제된 노드의 data)]
int Queue::Pop(void) {
	if (IsEmpty() == 1) return -1;

	BSTNode* pop= head;
	int data = head->GetData();
	head = head->GetNext();

	size--;
	return data;
}

// head 주소 반환
BSTNode* Queue::Front(void) {
	return head;
}