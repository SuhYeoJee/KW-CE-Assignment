#include <iostream>
#include "Block.h"
#include "Board.h"
#include <cstdlib>
#include <ctime>
#include "pch.h"

using namespace std;

MyBoard::MyBoard() {
	m_pHead = nullptr;
	MyBlock* add = nullptr;
	MyBlock* rl_temp = nullptr;
	MyBlock* ud_temp = nullptr;
	
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {

			add = new MyBlock;
			add->SetX(i); add->SetY(j);

			if ((i == 0) && (j == 0)) { // (0,0) ����
				this->m_pHead = add;
			}
			if (j != 0) { // (x,0) ����, �¿� ���� 
				rl_temp->SetRight(add);
				add->SetLeft(rl_temp);
				rl_temp = rl_temp->GetRight();
			}
			else { // (x,0)�� ���
				rl_temp = add;
			}
			if (i != 0) { // (0.y) ����, ���� ����
				ud_temp->SetDown(add);
				add->SetUp(ud_temp);
				ud_temp = ud_temp->GetRight();
			}
		}
		while (rl_temp->GetLeft()) rl_temp = rl_temp->GetLeft();
		ud_temp = rl_temp;
	}
}

MyBoard::~MyBoard() {
	MyBlock* del;
	for (int x = 3; x >= 0; x--) {
		for (int y = 3; y >= 0; y--) {
			del = gotoxy(x, y);
			delete del;
		}
	}
}

MyBlock* MyBoard::getHead(void) { return m_pHead; }
void MyBoard::setHead(MyBlock* temp) { m_pHead = temp; }

// [return: (x,y)�� MyBlock �ּ�]
MyBlock* MyBoard::gotoxy(int x, int y) {
	MyBlock* temp = m_pHead;
	for (int i = 0; i < x; i++) temp = temp->GetDown();
	for (int i = 0; i < y; i++) temp = temp->GetRight();
	return temp;
}

// �ؽ�Ʈ ���Ͽ� ���� ���
void MyBoard::print(void) {
	ofstream fout("log.txt", ios::app);
	MyBlock* temp;
	fout << "[result]" << endl;
	for (int x = 0; x <4; x++) {
		fout << "[  ";
		for (int y = 0; y <4; y++) {
			temp = gotoxy(x, y);
			fout.width(6); fout << left;
			if (temp->GetNum() == 0) fout << "_";
			else fout << temp->GetNum();
		}
		fout << "]" << endl;
	}
	fout << endl;
	fout.close();
	return;
}
// �� ĭ Ȯ��
// [return: ����(true), �� ĭ�� ����(false)]
bool MyBoard::IsFull(void) {
	MyBlock* temp;
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			temp = gotoxy(x, y);
			if (temp->GetNum() == 0) return false; // �� ĭ�� �ִ� ���
		}
	}
	return true; 

}
// �������� Ȯ��
// [return: ���(0), ��(1), ��(2)]
int MyBoard::IsEnd(void) {
	MyBlock* temp;
	int count = 0;
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			temp = gotoxy(x, y);
			if (temp->GetNum() == 2048) // ��
				return 1;
			if (temp->GetNum() == 0)
				count++;
		}
	}
	if (count != 0) return 0; // �� ĭ�� �ִ� ��� ���

	// ���� ���� ���޾� �����ϴ� ��� ���
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			temp = gotoxy(x, y);
			if (temp->GetUp()) {
				if (temp->GetNum() == temp->GetUp()->GetNum()) return 0;
			}
			if (temp->GetDown()) {
				if (temp->GetNum() == temp->GetDown()->GetNum()) return 0;
			}
			if (temp->GetLeft()) {
				if (temp->GetNum() == temp->GetLeft()->GetNum()) return 0;
			}
			if (temp->GetRight()) {
				if (temp->GetNum() == temp->GetRight()->GetNum()) return 0;
			}

		}
	}
	return 2;// ��
}

// ���� 2 ����
// [return: ����(false), ��������(true)]
bool MyBoard::random2(void) {
	MyBlock* temp = nullptr;
	int x, y;
	srand((unsigned int)time(NULL));
	while(1) {
		if (IsEnd()) return false; // [����] 2�� ������ ĭ�� ����
		x = rand() % (4); y = rand() % (4);
		temp = gotoxy(x, y);
		if (temp->GetNum()==0) {
			temp->SetNum(2);
			return true;
		}
	}
}

// ����
bool MyBoard::Up(void) {
	MyBlock* temp, *ban;
	bool change = false; // ���� ���� ������ true ������ false
	for (int y = 0; y < 4; y++) { 
		// �� ���� ���� �ݺ��� ����
		ban = nullptr;
		for (int x = 1; x < 4; x++) { //(0,y) ����
			temp = gotoxy(x, y);
			if (temp->GetNum() == 0) continue; // �� ���� �̵����� ����

			// ���� �� ��ŭ ���� �̵�.
			while (temp->GetUp()->GetNum() == 0) {
				temp->GetUp()->SetNum(temp->GetNum());
				temp->SetNum(0);
				temp = temp->GetUp();
				change = true;
				if (!temp->GetUp()) break; // (0,y)�� �� �� �̻� ���� ���� ����
			}
			if (!temp->GetUp()) continue; // (0,y)�� �� �� �̻� ���� ���� ����

			// ���ڰ� ���� ���� ����
			if (temp->GetNum() == temp->GetUp()->GetNum()) {
				if (temp->GetUp() == ban) continue;
				temp->GetUp()->SetNum(temp->GetNum() * 2);
				temp->SetNum(0);
				change = true;
				ban = temp->GetUp(); // �̹� ���࿡�� ������ �ڸ��� ���̻� ������ ����
			}
		}
	}
	return change;
}
bool MyBoard::Down(void) {
	MyBlock* temp, * ban;
	bool change = false; // ���� ���� ������ true ������ false
	for (int y = 0; y < 4; y++) {
		// �� ���� ���� �ݺ��� ����
		ban = nullptr;
		for (int x = 2; x >= 0; x--) { //(3,y) ����
			temp = gotoxy(x, y);
			if (temp->GetNum() == 0) continue; // �� ���� �̵����� ����

			// �Ʒ��� �� ��ŭ �Ʒ��� �̵�.
			while (temp->GetDown()->GetNum() == 0) {
				temp->GetDown()->SetNum(temp->GetNum());
				temp->SetNum(0);
				temp = temp->GetDown();
				change = true;
				if (!temp->GetDown()) break; // (3,y)�� �� �� �̻� �Ʒ��� ���� ����
			}
			if (!temp->GetDown()) continue; // (3,y)�� �� �� �̻� �Ʒ��� ���� ����

			// ���ڰ� ���� ���� ����
			if (temp->GetNum() == temp->GetDown()->GetNum()) {
				if (temp->GetDown() == ban) continue;
				temp->GetDown()->SetNum(temp->GetNum() * 2);
				temp->SetNum(0);
				change = true;
				ban = temp->GetDown(); // �̹� ���࿡�� ������ �ڸ��� ���̻� ������ ����
			}
		}
	}
	return change;
}
bool MyBoard::Left(void) {
	cout << "LEFT!" << endl;
	MyBlock* temp, * ban;
	bool change = false; // ���� ���� ������ true ������ false
	for (int x = 0; x < 4; x++) {
		// �� �࿡ ���� �ݺ��� ����
		ban = nullptr;
		for (int y = 1; y < 4; y++) { //(x,0) ����
			temp = gotoxy(x, y);
			if (temp->GetNum() == 0) continue; // �� ���� �̵����� ����

			// ������ �� ��ŭ �������� �̵�.
			while (temp->GetLeft()->GetNum() == 0) {
				temp->GetLeft()->SetNum(temp->GetNum());
				temp->SetNum(0);
				temp = temp->GetLeft();
				change = true;
				if (!temp->GetLeft()) break; // (x,0)�� �� �� �̻� ���ʿ� ���� ����
			}
			if (!temp->GetLeft()) continue; // (x,0)�� �� �� �̻� ���ʿ� ���� ����

			// ���ڰ� ���� ���� ����
			if (temp->GetNum() == temp->GetLeft()->GetNum()) {
				if (temp->GetLeft() == ban) continue;
				temp->GetLeft()->SetNum(temp->GetNum() * 2);
				temp->SetNum(0);
				change = true;
				ban = temp->GetLeft(); // �̹� ���࿡�� ������ �ڸ��� ���̻� ������ ����
			}
		}
	}
	return change;
}
bool MyBoard::Right(void) {
	MyBlock* temp, * ban;
	bool change = false; // ���� ���� ������ true ������ false
	for (int x = 0; x < 4; x++) {
		// �� �࿡ ���� �ݺ��� ����
		ban = nullptr;
		for (int y = 2; y >= 0; y--) { //(x,3) ����
			temp = gotoxy(x, y);
			if (temp->GetNum() == 0) continue; // �� ���� �̵����� ����

			// �������� �� ��ŭ ���������� �̵�.
			while (temp->GetRight()->GetNum() == 0) {
				temp->GetRight()->SetNum(temp->GetNum());
				temp->SetNum(0);
				temp = temp->GetRight();
				change = true;
				if (!temp->GetRight()) break; // (x,3)�� �� �� �̻� �����ʿ� ���� ����
			}
			if (!temp->GetRight()) continue; // (x,3)�� �� �� �̻� �����ʿ� ���� ����

			// ���ڰ� ���� ���� ����
			if (temp->GetNum() == temp->GetRight()->GetNum()) {
				if (temp->GetRight() == ban) continue;
				temp->GetRight()->SetNum(temp->GetNum() * 2);
				temp->SetNum(0);
				change = true;
				ban = temp->GetRight(); // �̹� ���࿡�� ������ �ڸ��� ���̻� ������ ����
			}
		}
	}
	return change;
}

void MyBoard::TurnCW(void) {
	MyBlock* temp, *turn;
	for (int x = 3; x >= 0; x--) {
		for (int y = 3; y >= 0; y--) {
		turn = gotoxy(x,y);
		temp = turn->GetRight();
		turn->SetRight(turn->GetUp());
		turn->SetUp(turn->GetLeft());
		turn->SetLeft(turn->GetDown());
		turn->SetDown(temp);
		}
	}
	temp = getHead();
	for (int i = 0; i < 3; i++)temp = temp->GetLeft();
	this->setHead(temp);
	return;
}
void MyBoard::TurnCCW(void) {
	MyBlock* temp, * turn;
	for (int x = 3; x >= 0; x--) {
		for (int y = 3; y >= 0; y--) {
			turn = gotoxy(x, y);
			temp = turn->GetRight();
			turn->SetRight(turn->GetDown());
			turn->SetDown(turn->GetLeft());
			turn->SetLeft(turn->GetUp());
			turn->SetUp(temp);
		}
	}
	temp = getHead();
	for (int i = 0; i < 3; i++)temp = temp->GetUp();
	this->setHead(temp);
	return;
}