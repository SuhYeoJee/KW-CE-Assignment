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
// 잎에서 줄기 순서로 삭제
	Dtor(root);
}
void BST::Dtor(BSTNode* node) {
	if (node == nullptr)
		return;
	Dtor(node->GetLeft());
	Dtor(node->GetRight());
	delete node;
}

// BST에 새 노드 추가
//[return: 입력오류(-1), 정상종료(0)]
bool BST::Add(int _data) {
	BSTNode* add = new BSTNode;
	add->SetData(_data);

	if (root == nullptr) { // 첫 노드 추가
		root = add;
	}
	else {
		// 새 노드의 부모를 찾음
		BSTNode* temp = root;
		while (temp != nullptr) { 
			if (add->GetData() == temp->GetData()) {
				cout << "Invalid input" << endl;
				return false;
			}
			add->SetParent(temp);
			temp = (add->GetData() < temp->GetData()) ? temp->GetLeft(): temp->GetRight();
		}
		// 노드 삽입
		temp = add->GetParent();
		(add->GetData() < temp->GetData()) ? temp->SetLeft(add) : temp->SetRight(add);
	}
	return true;
}

// private 영역 반환
BSTNode* BST::GetRoot(void) { return root; }
Queue* BST::GetQueue(void) { return &queue; }

// 트리 순회 - 재귀함수
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

