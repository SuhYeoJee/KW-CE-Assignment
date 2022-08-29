#include <iostream>
#include <Windows.h>
#include "Stone.h"
#include "Board.h"
using namespace std;

int main(void) {
	setlocale(LC_ALL, ""); // 특수문자 출력 wcout, wchar_t

	int player = 1, turn = -1;
	int x = 0, y = 0, win = 0;
	OthelloBoard m_Board;
	m_Board.SetBoard();
	
	while (1) {
		cout << "Player" << player << endl;
		m_Board.PrintBoard();
		if (m_Board.IsSkip(player)) {
			cout << "No valid move." << endl;
			system("PAUSE");
			system("cls");
			if ((x == -1) && (y == -1)) { // 프로그램 종료
				win = m_Board.IsEnd(1);
				break;
			}
			x = -1; y = -1;
		}
		else {
			cout << endl << "Select Position: ";
			cin >> x; cin >> y;
			system("cls");
			if ((x == -1) && (y == -1)) { // 프로그램 종료
				cout << "Game End!" << endl;
				m_Board.DeleteBoard();
				return 0;
			}
			if (!m_Board.NewStone(player, x, y)) continue;
		}
		if (win = m_Board.IsEnd(0)) break;
		player += (turn *= -1);
	}
	 //결과 출력
	m_Board.PrintBoard();
	if (win == 3)
		cout << "Draw" << endl;
	else
		cout << "Player" << win << " win!" << endl;

	m_Board.DeleteBoard();
	return 0;
}