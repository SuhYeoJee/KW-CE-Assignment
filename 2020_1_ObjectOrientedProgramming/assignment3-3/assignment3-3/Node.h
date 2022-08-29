#pragma once

class BSTNode {
private:
	BSTNode* parent;
	BSTNode* left;
	BSTNode* right;
	BSTNode* next;
	int data;

public:
	BSTNode();
	BSTNode(int _data);
	~BSTNode();

	// private ���� ������ ����
	void SetParent(BSTNode* _parent);
	void SetLeft(BSTNode* _left);
	void SetRight(BSTNode* _right);
	void SetNext(BSTNode* _next);
	void SetData(int _data);

	// private ���� ��ȯ
	BSTNode* GetParent(void);
	BSTNode* GetLeft(void);
	BSTNode* GetRight(void);
	BSTNode* GetNext(void);
	int GetData(void);
};
