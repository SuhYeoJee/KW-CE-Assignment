#include <iostream>
#include "Block.h"
#include "Board.h"
#include <Windows.h>
using namespace std;

int main(void) {

	MyBoard m_Board;
	
	int win = 0;
	cout << "[Start]" << endl;
	m_Board.random2();

	while (1) {
		int select = 0;

		// ���� ���
		cout << "[Board]" << endl;
		m_Board.print();

		// �޴� ���, �Է�
		cout << endl<<"[Menu]" << endl;
		cout << "1.Up\t2.Down\t3.Left\t4.Right" << endl;
		cout << "Input>>";
		cin >> select; cin.ignore();

		switch (select)
		{
		case(1): //UP
			if ((!m_Board.Up())&&(m_Board.IsFull()))
				break;
			m_Board.random2();
			break;
		case(2): //DOWN
			if ((!m_Board.Down()) && (m_Board.IsFull()))
				break;
			m_Board.random2();
			break;
		case(3): //Left
			if ((!m_Board.Left()) && (m_Board.IsFull()))
				break;
			m_Board.random2();
			break;
		case(4): //RIGHT
			if ((!m_Board.Right()) && (m_Board.IsFull()))
				break;
			m_Board.random2();
			break;
		case(-1):
			cout << "[program exit]" << endl;
			return 0;
		default: // [����] -1Ȥ�� 1~4�� �Էµ��� ���� ���
			cout << "Invalid input" << endl;
			break;
		}
		cout << endl << "==============" << endl << endl;
		// ���� �Ǻ�
		if ((win = m_Board.IsEnd()) !=0) break;
	}

	m_Board.print();

	if (win == 1)  // ��
		cout <<endl<< "Win!" << endl;
	else if (win == 2) // ��
		cout <<endl<< "Lose!" << endl;

	cout << "[program exit]" << endl;

	return 0;
}

