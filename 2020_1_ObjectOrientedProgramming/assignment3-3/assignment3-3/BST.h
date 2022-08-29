#pragma once
#include "Queue.h"
#include "Node.h"

class BST {
private:
	BSTNode* root;
	Queue queue;
public:
	BST();
	~BST();
	void Dtor(BSTNode* node);

	// BST에 새 노드 추가
	bool Add(int _data);

	// private 영역 반환
	BSTNode* GetRoot(void);
	Queue* GetQueue(void);

	// 트리 순회
	void Preorder(BSTNode* node);
	void Inorder(BSTNode* node);
	void Postorder(BSTNode* node);

};