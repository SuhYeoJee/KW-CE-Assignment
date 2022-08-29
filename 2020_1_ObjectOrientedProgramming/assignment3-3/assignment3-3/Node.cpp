#include <iostream>
#include "Node.h"
using namespace std;

BSTNode::BSTNode() {
	parent = nullptr;
	left = nullptr;
	right = nullptr;
	next = nullptr;
	data = NULL;
}
BSTNode::BSTNode(int _data) {
	parent = nullptr;
	left = nullptr;
	right = nullptr;
	next = nullptr;
	data = _data;
}
BSTNode::~BSTNode() {}

// private 영역 변수값 지정
void BSTNode::SetParent(BSTNode* _parent) { parent = _parent; return; }
void BSTNode::SetLeft(BSTNode* _left) { left = _left; return; }
void BSTNode::SetRight(BSTNode* _right) { right = _right; return; }
void BSTNode::SetNext(BSTNode* _next) { next = _next; return; }
void BSTNode::SetData(int _data) { data = _data; return; }

// private 영역 반환
BSTNode* BSTNode::GetParent(void) { return parent; }
BSTNode* BSTNode::GetLeft(void) { return left; }
BSTNode* BSTNode::GetRight(void) { return right; }
BSTNode* BSTNode::GetNext(void) { return next; }
int BSTNode::GetData(void) { return data; }