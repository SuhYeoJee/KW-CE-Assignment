#include <iostream>
#include "Queue.h"
#include "Node.h"
#include "BST.h"
using namespace std;

BST::BST() {
	root = nullptr;
}

BST::~BST() {
// postoder + delete
// �ٿ��� �ٱ� ������ ����
	Dtor(root);
}
void BST::Dtor(BSTNode* node) {
	if (node == nullptr)
		return;
	Dtor(node->GetLeft());
	Dtor(node->GetRight());
	delete node;
}

// BST�� �� ��� �߰�
//[return: �Է¿���(-1), ��������(0)]
bool BST::Add(int _data) {
	BSTNode* add = new BSTNode;
	add->SetData(_data);

	if (root == nullptr) { // ù ��� �߰�
		root = add;
	}
	else {
		// �� ����� �θ� ã��
		BSTNode* temp = root;
		while (temp != nullptr) { 
			if (add->GetData() == temp->GetData()) {
				cout << "Invalid input" << endl;
				return false;
			}
			add->SetParent(temp);
			temp = (add->GetData() < temp->GetData()) ? temp->GetLeft(): temp->GetRight();
		}
		// ��� ����
		temp = add->GetParent();
		(add->GetData() < temp->GetData()) ? temp->SetLeft(add) : temp->SetRight(add);
	}
	return true;
}

// private ���� ��ȯ
BSTNode* BST::GetRoot(void) { return root; }
Queue* BST::GetQueue(void) { return &queue; }

// Ʈ�� ��ȸ - ����Լ�
void BST::Preorder(BSTNode* node) {
	// node -> left subtree -> right subtree
	if (node == nullptr)
		return;
	queue.Push(node);
	Preorder(node->GetLeft());
	Preorder(node->GetRight());
}
void BST::Inorder(BSTNode* node) {
	// left subtree -> node -> right subtree
	if (node == nullptr)
		return;
	Inorder(node->GetLeft());
	queue.Push(node);
	Inorder(node->GetRight());
}
void BST::Postorder(BSTNode* node) {
	// left subtree -> right subtree -> node
	if (node == nullptr)
		return;
	Postorder(node->GetLeft());
	Postorder(node->GetRight());
	queue.Push(node);
}

