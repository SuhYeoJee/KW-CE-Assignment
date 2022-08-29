#include <iostream>
#include "Queue.h"
#include "Node.h"
#include "BST.h"
using namespace std;

int main(void) {
	BST BST;
	int size, data;

	// BST ����
	cout << "Enter Input Size: ";
	cin >> size; cin.ignore();
	cout << "Enter a number: ";
	while (size--) {
		cin >> data;
		if (!BST.Add(data)) // [����] �ߺ��Ǵ� ���� �Է�
			return -1;
	}
	cin.ignore(10, '\n');

	int select;
	while (1) {
		select = 0;
		cout << endl; // �޴����
		cout << "1. Preorder" << endl;
		cout << "2. Inorder" << endl;
		cout << "3. Postorder" << endl;
		cout << "4. Exit" << endl;
		cout << "Select Number: ";
		cin >> select; cin.ignore();
		cout << endl;

		switch (select)
		{
		case(1):
			cout << "Preorder:";
			BST.Preorder(BST.GetRoot()); // ť�� ��ȸ��� ����
			while (!BST.GetQueue()->IsEmpty()) // ť�� ���� ��� ���
				cout << BST.GetQueue()->Pop() << " ";
			cout << endl;
			break;
		case(2):
			cout << "Inorder:";
			BST.Inorder(BST.GetRoot());// ť�� ��ȸ��� ����
			while (!BST.GetQueue()->IsEmpty()) // ť�� ���� ��� ���
				cout << BST.GetQueue()->Pop() << " ";
			cout << endl;
			break;
		case(3):
			cout << "Postorder:";
			BST.Postorder(BST.GetRoot());// ť�� ��ȸ��� ����
			while (!BST.GetQueue()->IsEmpty())// ť�� ���� ��� ���
				cout << BST.GetQueue()->Pop() << " ";
			cout << endl;
			break;
		case(4):
			cout << "End of Program." << endl;
			return 0;
		default: //[����] 1~4 �� �Էµ��� ����
			cout << "Invalid input";
			break;
		}
	}
}