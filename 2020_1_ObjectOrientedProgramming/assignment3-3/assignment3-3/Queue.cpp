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

//[return: ť�� �������(1), ��尡 ���� ��(0)]
bool Queue::IsEmpty(void) {
	return (size == 0) ? true : false;
}

// ť�� �� ��� �߰�
void Queue::Push(BSTNode* push) {
	if (size == 0) { // ť�� ù ����� ���
		head = push;
		tail = push;
	}
	else { // ������ ��尡 �ִ� ���
		tail->SetNext(push);
		tail = push;
	}
	tail->SetNext(nullptr);
	size++;
	return;
}

// ��� ����
// [return: ť�� ����� ��(-1), ��������(������ ����� data)]
int Queue::Pop(void) {
	if (IsEmpty() == 1) return -1;

	BSTNode* pop= head;
	int data = head->GetData();
	head = head->GetNext();

	size--;
	return data;
}

// head �ּ� ��ȯ
BSTNode* Queue::Front(void) {
	return head;
}