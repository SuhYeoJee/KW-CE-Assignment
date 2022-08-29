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

		// 보드 출력
		cout << "[Board]" << endl;
		m_Board.print();

		// 메뉴 출력, 입력
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
		default: // [오류] -1혹은 1~4가 입력되지 않은 경우
			cout << "Invalid input" << endl;
			break;
		}
		cout << endl << "==============" << endl << endl;
		// 종료 판별
		if ((win = m_Board.IsEnd()) !=0) break;
	}

	m_Board.print();

	if (win == 1)  // 승
		cout <<endl<< "Win!" << endl;
	else if (win == 2) // 패
		cout <<endl<< "Lose!" << endl;

	cout << "[program exit]" << endl;

	return 0;
}

