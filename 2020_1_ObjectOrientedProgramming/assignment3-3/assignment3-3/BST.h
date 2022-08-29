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

	// BST�� �� ��� �߰�
	bool Add(int _data);

	// private ���� ��ȯ
	BSTNode* GetRoot(void);
	Queue* GetQueue(void);

	// Ʈ�� ��ȸ
	void Preorder(BSTNode* node);
	void Inorder(BSTNode* node);
	void Postorder(BSTNode* node);

};