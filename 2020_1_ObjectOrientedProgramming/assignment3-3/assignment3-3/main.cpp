#include <iostream>
#include "Queue.h"
#include "Node.h"
#include "BST.h"
using namespace std;

int main(void) {
	BST BST;
	int size, data;

	// BST 생성
	cout << "Enter Input Size: ";
	cin >> size; cin.ignore();
	cout << "Enter a number: ";
	while (size--) {
		cin >> data;
		if (!BST.Add(data)) // [오류] 중복되는 정수 입력
			return -1;
	}
	cin.ignore(10, '\n');

	int select;
	while (1) {
		select = 0;
		cout << endl; // 메뉴출력
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
			BST.Preorder(BST.GetRoot()); // 큐에 순회결과 저장
			while (!BST.GetQueue()->IsEmpty()) // 큐의 내용 모두 출력
				cout << BST.GetQueue()->Pop() << " ";
			cout << endl;
			break;
		case(2):
			cout << "Inorder:";
			BST.Inorder(BST.GetRoot());// 큐에 순회결과 저장
			while (!BST.GetQueue()->IsEmpty()) // 큐의 내용 모두 출력
				cout << BST.GetQueue()->Pop() << " ";
			cout << endl;
			break;
		case(3):
			cout << "Postorder:";
			BST.Postorder(BST.GetRoot());// 큐에 순회결과 저장
			while (!BST.GetQueue()->IsEmpty())// 큐의 내용 모두 출력
				cout << BST.GetQueue()->Pop() << " ";
			cout << endl;
			break;
		case(4):
			cout << "End of Program." << endl;
			return 0;
		default: //[오류] 1~4 가 입력되지 않음
			cout << "Invalid input";
			break;
		}
	}
}