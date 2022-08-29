#include <iostream>
#include "classList.h"
using namespace std;
#define _CRT_SECURE_NO_WARNINGS

int main(void) 
{
	List cafe;
	char str[60];

	while (1) {
		int select = 0;
		int err=0;

		cout << endl<<endl<<"1. LOAD" << endl;
		cout << "2. PRINT" << endl;
		cout << "3. INSERT" << endl;
		cout << "4. Category SEARCH" << endl;
		cout << "5. Menu SEARCH" << endl;
		cout << "6. DELETE" << endl;
		cout << "7. End of Program!" << endl;
		cout << "Select Number: ";
		cin >> select; cin.ignore();

		cout << endl;
		switch (select)
		{
		case(1): // LOAD: ���Ͽ��� ����Ʈ�� �о����
			err = cafe.add();
			if ( err == -1)
				cout << "No \"input.txt\" File" << endl;
			else
				cout << "LOAD Success!";
			break;

		case(2): // PRINT: ����Ʈ�� ���� ��� ���
			cafe.printList();
			break;

		case(3): // INSERT: ����Ʈ�� �ϳ��� �޴� �߰�
			cout << "Enter Category, Menu and Price: ";
			cin.getline(str, 60, '\n');
			err = cafe.add(str);
			if (err == -1) //[����]�Է��� ����Ȯ�Ѱ��
				cout << "Invalid input" << endl;
			else if (err == 0)
				cout << "Insert Success!" << endl;
			break;
		case(4): // Category SEARCH: ī�װ� ���
			cout << "Enter Category which you want to find: ";
			cin >> str; cin.ignore(50, '\n');
			err = cafe.printList(cafe.find(str));
			if(err ==-1) // [����] ī�װ��� ���� ���
				cout << "No category" << endl;
			break;
		case(5): // Menu SEARCH: �޴� ���
			cout << "Enter Menu which you want to find: ";
			cin >> str; cin.ignore(50, '\n');
			err = cafe.printMenu(str);
			if (err == -1) // [����] �޴��� ���� ���
				cout << "No Menu" << endl;
			break;
		case(6): // DELETE: �޴� ����
			cout << "Enter Menu which you want to delete: ";
			cin >> str; cin.ignore(50, '\n');
			err = cafe.deleteMenu(str);
			if (err == -1)// [����] �޴��� ���� ���
				cout << "No Menu" << endl;
			else if(err == 0)
				cout << "Delete Success!" << endl;
			break;
		case(7): // End of Program: ����
			cout << "End of Program." << endl;
			return 0;
		default: // [����] 1~7�� �Է����� ����
			cout << "Invalid input" << endl;
			break;
		}
	}
}
