#include <iostream>
#include "Stone.h"
#include "Board.h"

using namespace std;

OthelloBoard::OthelloBoard() {
	OthelloStone* m_pStone = nullptr;
	OthelloBoard* m_pHead = nullptr;
	OthelloBoard* m_pUp = nullptr;
	OthelloBoard* m_pDown = nullptr;
	OthelloBoard* m_pLeft = nullptr;
	OthelloBoard* m_pRight = nullptr;
}

OthelloBoard::~OthelloBoard() {
	// ĭ�� ���� �ִٸ� �޸� ����
	if (this->m_pStone)
		delete this->m_pStone;
}

// x,y ĭ���� ������ �̵�
OthelloBoard* OthelloBoard::gotoxy(int x, int y) {
	OthelloBoard* temp = m_pHead;
	for (int i = 1; i < x; i++) temp = temp->m_pRight;
	for (int i = 1; i < y; i++) temp = temp->m_pUp;
	return temp;
}

//���� ����, �ʱ� �� ����
void OthelloBoard::SetBoard(void) {
	// ���� ����
	m_pHead = this;
	OthelloBoard* rl_temp = m_pHead;
	OthelloBoard* ud_temp = m_pHead;
	OthelloBoard* add = nullptr;

	for (int i = 1; i < 9; i++) {
		for (int j = 2; j < 9; j++) {
			// ������ ĭ ����
			add = new OthelloBoard;
			add->m_pHead = this; // ��� ����
			rl_temp->m_pRight = add; //�¿� ����
			add->m_pLeft = rl_temp;
			if (i > 1) {
				ud_temp->m_pUp = add;// ���Ʒ� ����
				add->m_pDown = ud_temp;
				if (ud_temp->m_pRight) ud_temp = ud_temp->m_pRight;
			}
			rl_temp = add;
		}
		if (i == 8) break; // ��ü ����Ʈ ���� ����

		// rl_temp ��ġ �ʱ�ȭ
		while (rl_temp->m_pLeft)
			rl_temp = rl_temp->m_pLeft;

		// ud_temp ��ġ �ʱ�ȭ
		while (ud_temp->m_pLeft)
			ud_temp = ud_temp->m_pLeft;
		if (ud_temp->m_pUp) { ud_temp = ud_temp->m_pUp; }

		// ���� ����
		add = new OthelloBoard;
		add->m_pHead = this;
		ud_temp->m_pUp = add; add->m_pDown = ud_temp;
		rl_temp = add;
		ud_temp = ud_temp->m_pRight;
	}

	// �ʱ� �� ����
	SetStone(1, 4, 4);
	SetStone(1, 5, 5);
	SetStone(2, 4, 5);
	SetStone(2, 5, 4);

	return;
}

// ���� ���
void OthelloBoard::PrintBoard(void) {
	OthelloBoard* temp = gotoxy(1, 8);
	wchar_t ch; // Ư������ ��� wcout, wchar_t
	// ��� ���� (1,8) -> (8,8) -> (1,7) -> (8,7) ->
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++) {
			if (temp->m_pStone) // ���� ���� ���
				ch = (temp->m_pStone->GetColor() == 'b') ? L'��' : L'��';
			else
				ch = L'��'; // ĭ�� �� ���
			wcout << ch;
			if (temp->m_pRight) temp = temp->m_pRight;
		}
		cout << endl;
		while (temp->m_pLeft) temp = temp->m_pLeft;
		if (temp->m_pDown) temp = temp->m_pDown;
	}
	return;
}


//�� �� ����
//[return: ���� �Ҹ���(false), ��������(true)]
bool OthelloBoard::NewStone(int player, int x, int y) {

	// ���Ǽ��� ����
	if (!IsPossible(player, x, y)) { //[����] ���� �Ҹ���
		cout << "Wrong position!" << endl;
		return false; 
	}
	OthelloBoard* add = gotoxy(x, y);// �� ���� ���� �ڸ��� �̵�
	SetStone(player, x, y);// �� �� ����
	Turn(player, add);// ��� �� ������
	return true;
}
// ���� ���� �� �ִ��� �Ǵ�
// [return: �Ұ���(false), ����(true)]
bool OthelloBoard::IsPossible(int player, int x, int y) {

	// [����] �������� ���� ���� ��ǥ
	if ((x < 1) || (x > 8)) return false;
	if ((y < 1) || (y > 8)) return false;

	OthelloBoard* add = gotoxy(x, y);// �� ���� ���� �ڸ��� �̵�

	if (add->m_pStone) return false;// [����] �̹� ���� �ִ� ���

	// �� �������� ������ �� �ִ��� Ȯ��
	if (IsPossible_R(player, add)) return true;
	if (IsPossible_L(player, add)) return true;
	if (IsPossible_U(player, add)) return true;
	if (IsPossible_D(player, add)) return true;
	if (IsPossible_UR(player, add)) return true;
	if (IsPossible_UL(player, add)) return true;
	if (IsPossible_DR(player, add)) return true;
	if (IsPossible_DL(player, add)) return true;
	return false;
}
// OthelloStone ����
void OthelloBoard::SetStone(int player, int x, int y) {
	// �� ���� ���� �ڸ�
	OthelloBoard* add = gotoxy(x, y);

	// (x,y)�� �� �� ����
	OthelloStone* n_stone = new OthelloStone;
	n_stone->SetColor(player);
	add->m_pStone = n_stone;
}
// ����� ���� ���������
void OthelloBoard::Turn(int player, OthelloBoard* temp) {
	// �� �������� ��� �� ������
	if (IsPossible_R(player, temp)) { Turn_R(temp); }
	if (IsPossible_L(player, temp)) { Turn_L(temp); }
	if (IsPossible_U(player, temp)) { Turn_U(temp); }
	if (IsPossible_D(player, temp)) { Turn_D(temp); }
	if (IsPossible_UR(player, temp)) { Turn_UR(temp); }
	if (IsPossible_UL(player, temp)) { Turn_UL(temp); }
	if (IsPossible_DR(player, temp)) { Turn_DR(temp); }
	if (IsPossible_DL(player, temp)) { Turn_DL(temp); }
	return;
}


// �������� Ȯ��
// [return: ������� ����(0), p1�¸�(1), p2�¸�(2), ���(3)]
int OthelloBoard::IsEnd(int end) {
	// end ==1 ������ ����
	OthelloBoard* temp = m_pHead;
	int b = 0, w = 0;
	char color;
	// �浹�� �鵹�� �� ���
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (!temp->m_pStone) {
				if (temp->m_pRight) temp = temp->m_pRight;
				continue; // ĭ�� ���� ���� ���
			}
			color = temp->m_pStone->GetColor();
			if (color == 'b') b++;
			else if (color == 'w') w++;
			if (temp->m_pRight) temp = temp->m_pRight;
		}
		if (temp->m_pUp) temp = temp->m_pUp;
		while (temp->m_pLeft)
			temp = temp->m_pLeft;
	}

	if (b + w == 64) { // ���� ���� �� ���
		if (b == w) return 3;
		else if (b > w) return 1;
		else return 2;
	}
	else { // �� ���� ������ ���ϵ� ���
		if ((b == 0) || (w == 0))
			return (b > w) ? 1 : 2;
		else if (end) { //������ �����ϴ� ���
			if (b == w) return 3;
			return (b > w) ? 1 : 2;
		}
	}
	//���ᰡ �ƴ� ���
	return 0;
}

// ���ʸ� �ǳ� �ٴ��� Ȯ��(���� �ڸ� ����)
// [return: �ǳ� ��(true), �ǳʶ��� ����(false}]
bool OthelloBoard::IsSkip(int player) {
	for (int y = 1; y < 9; y++) {
		for (int x = 1; x < 9; x++) {
			if (IsPossible(player, x, y)) return false;
		}
	}
	return true;
}

// ������ ������ �� ����Ʈ ����
void OthelloBoard::DeleteBoard(void) {
	OthelloBoard* del = m_pHead;
	del->gotoxy(8, 8);
	OthelloBoard* temp = del;

	// �������� (8,8) -> (1,8) -> (8,7) -> (1,7) ->
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			temp = (del->m_pLeft) ? del->m_pLeft : del->m_pDown;
			if (del == m_pHead) break;
			delete del;
			del = temp;
		}
		if (temp == nullptr) break;
		while (temp->m_pRight) temp = temp->m_pRight;
		del = temp;
	}
}


// ���⿡ ���� �Ǵ� �Լ�
bool OthelloBoard::IsPossible_R(int player, OthelloBoard * add) {
	OthelloBoard* temp = add;
	char color = (player == 1) ? 'b' : 'w'; // �������� ���� ��

	// �̿��� ĭ�� ��ĭ
	temp = temp->m_pRight;
	if (!temp)return false;
	if (!temp->m_pStone) return false;

	// �̿��� ĭ�� �ڽ��� ��
	if (temp->m_pStone->GetColor() == color) return false;

	//�̿��� ĭ�� ����� ��
	temp = add;
	while (temp->m_pRight->m_pStone) { // ���� ���� ������
		temp = temp->m_pRight;
		if (temp->m_pStone->GetColor() == color )
			return true; // �ڽ��� ���� ã��
		if (!temp->m_pRight) break; // �����ʿ� ĭ�� ����
	}
	return false;
}
bool OthelloBoard::IsPossible_L(int player, OthelloBoard* add) {
	OthelloBoard* temp = add;
	char color = (player == 1) ? 'b' : 'w'; // �������� ���� ��

	// �̿��� ĭ�� ��ĭ
	temp = temp->m_pLeft;
	if (!temp)return false;
	if (!temp->m_pStone) return false;

	// �̿��� ĭ�� �ڽ��� ��
	
	if (temp->m_pStone->GetColor() == color) return false;

	//�̿��� ĭ�� ����� ��
	temp = add;
	while (temp->m_pLeft->m_pStone) { // ���� ���� ������
		temp = temp->m_pLeft;
		if (temp->m_pStone->GetColor() == color)
			return true; // �ڽ��� ���� ã��
		if (!temp->m_pLeft) break; // ���ʿ� ĭ�� ����
	}
	return false;
}
bool OthelloBoard::IsPossible_U(int player, OthelloBoard* add) {
	OthelloBoard* temp = add;
	char color = (player == 1) ? 'b' : 'w'; // �������� ���� ��

	// �̿��� ĭ�� ��ĭ
	temp = temp->m_pUp;
	if (!temp)return false;
	if (!temp->m_pStone) return false;

	// �̿��� ĭ�� �ڽ��� ��
	if (temp->m_pStone->GetColor() == color) return false;

	//�̿��� ĭ�� ����� ��
	temp = add;
	while (temp->m_pUp->m_pStone) { // ���� ���� ������
		temp = temp->m_pUp;
		if (temp->m_pStone->GetColor() == color)
			return true; // �ڽ��� ���� ã��
		if (!temp->m_pUp) break; // ���� ĭ�� ����
	}
	return false;
}
bool OthelloBoard::IsPossible_D(int player, OthelloBoard* add) {
	OthelloBoard* temp = add;
	char color = (player == 1) ? 'b' : 'w'; // �������� ���� ��

	// �̿��� ĭ�� ��ĭ
	temp = temp->m_pDown;
	if (!temp)return false;
	if (!temp->m_pStone) return false;

	// �̿��� ĭ�� �ڽ��� ��
	if (temp->m_pStone->GetColor() == color) return false;

	//�̿��� ĭ�� ����� ��
	temp = add;
	while (temp->m_pDown->m_pStone) { // ���� ���� ������
		temp = temp->m_pDown;
		if (temp->m_pStone->GetColor() == color)
			return true; // �ڽ��� ���� ã��
		if (!temp->m_pDown) break; // �Ʒ��� ĭ�� ����
	}
	return false;
}
bool OthelloBoard::IsPossible_UR(int player, OthelloBoard* add) {
	OthelloBoard* temp = add;
	char color = (player == 1) ? 'b' : 'w'; // �������� ���� ��

	// �̿��� ĭ�� ��ĭ
	if (!temp->m_pUp) return false;
	temp = temp->m_pUp->m_pRight;
	if (!temp)return false;
	if (!temp->m_pStone) return false;

	// �̿��� ĭ�� �ڽ��� ��
	if (temp->m_pStone->GetColor() == color) return false;

	//�̿��� ĭ�� ����� ��
	temp = add;
	while (temp->m_pUp->m_pRight->m_pStone) { // ���� ���� ������
		temp = temp->m_pUp->m_pRight;
		if (temp->m_pStone->GetColor() == color)
			return true; // �ڽ��� ���� ã��
		if (!temp->m_pUp) break; // ���� ĭ�� ����
		if (!temp->m_pUp->m_pRight) break; // �������ʿ� ĭ�� ����
	}
	return false;
}
bool OthelloBoard::IsPossible_UL(int player, OthelloBoard* add) {
	OthelloBoard* temp = add;
	char color = (player == 1) ? 'b' : 'w'; // �������� ���� ��

	// �̿��� ĭ�� ��ĭ
	if (!temp->m_pUp) return false;
	temp = temp->m_pUp->m_pLeft;
	if (!temp)return false;
	if (!temp->m_pStone) return false;

	// �̿��� ĭ�� �ڽ��� ��
	if (temp->m_pStone->GetColor() == color) return false;

	//�̿��� ĭ�� ����� ��
	temp = add;
	while (temp->m_pUp->m_pLeft->m_pStone) { // ���� ���� ������
		temp = temp->m_pUp->m_pLeft;
		if (temp->m_pStone->GetColor() == color)
			return true; // �ڽ��� ���� ã��
		if (!temp->m_pUp) break; // ���� ĭ�� ����
		if (!temp->m_pUp->m_pLeft) break; // �����ʿ� ĭ�� ����
	}
	return false;
}
bool OthelloBoard::IsPossible_DR(int player, OthelloBoard* add) {
	OthelloBoard* temp = add;
	char color = (player == 1) ? 'b' : 'w'; // �������� ���� ��

	// �̿��� ĭ�� ��ĭ
	if (!temp->m_pDown) return false;
	temp = temp->m_pDown->m_pRight;
	if (!temp)return false;
	if (!temp->m_pStone) return false;

	// �̿��� ĭ�� �ڽ��� ��
	if (temp->m_pStone->GetColor() == color) return false;

	//�̿��� ĭ�� ����� ��
	temp = add;
	while (temp->m_pDown->m_pRight->m_pStone) { // ���� ���� ������
		temp = temp->m_pDown->m_pRight;
		if (temp->m_pStone->GetColor() == color)
			return true; // �ڽ��� ���� ã��
		if (!temp->m_pDown) break; // �Ʒ��� ĭ�� ����
		if (!temp->m_pDown->m_pRight) break; // �Ʒ������ʿ� ĭ�� ����
	}
	return false;
}
bool OthelloBoard::IsPossible_DL(int player, OthelloBoard* add) {
	OthelloBoard* temp = add;
	char color = (player == 1) ? 'b' : 'w'; // �������� ���� ��

	// �̿��� ĭ�� ��ĭ
	if (!temp->m_pDown) return false;
	temp = temp->m_pDown->m_pLeft;
	if (!temp)return false;
	if (!temp->m_pStone) return false;

	// �̿��� ĭ�� �ڽ��� ��
	if (temp->m_pStone->GetColor() == color) return false;

	//�̿��� ĭ�� ����� ��
	temp = add;
	while (temp->m_pDown->m_pLeft->m_pStone) { // ���� ���� ������
		temp = temp->m_pDown->m_pLeft;
		if (temp->m_pStone->GetColor() == color)
			return true; // �ڽ��� ���� ã��
		if (!temp->m_pDown) break; // �Ʒ��� ĭ�� ����
		if (!temp->m_pDown->m_pLeft) break; // �Ʒ����ʿ� ĭ�� ����
	}
	return false;
}

// ���⿡ ���� ������ �Լ�
void OthelloBoard::Turn_R(OthelloBoard* temp) {
	char color = temp->m_pStone->GetColor();

	while (temp->m_pRight->m_pStone) { //���� ���� ������
		temp = temp->m_pRight;
		if (temp->m_pStone->GetColor() == color) return;
		else
			temp->m_pStone->SetColor(color);
	}
}
void OthelloBoard::Turn_L(OthelloBoard* temp) {
	char color = temp->m_pStone->GetColor();

	while (temp->m_pLeft->m_pStone) {
		temp = temp->m_pLeft;
		if (temp->m_pStone->GetColor() == color) return;
		else
			temp->m_pStone->SetColor(color);
	}
}
void OthelloBoard::Turn_U(OthelloBoard* temp) {
	char color = temp->m_pStone->GetColor();

	while (temp->m_pUp->m_pStone) {
		temp = temp->m_pUp;
		if (temp->m_pStone->GetColor() == color) return;
		else
			temp->m_pStone->SetColor(color);
	}
}
void OthelloBoard::Turn_D(OthelloBoard* temp) {
	char color = temp->m_pStone->GetColor();

	while (temp->m_pDown->m_pStone) {
		temp = temp->m_pDown;
		if (temp->m_pStone->GetColor() == color) return;
		else
			temp->m_pStone->SetColor(color);
	}
}
void OthelloBoard::Turn_UR(OthelloBoard* temp) {
	char color = temp->m_pStone->GetColor();

	while (temp->m_pUp->m_pRight->m_pStone) {
		temp = temp->m_pUp->m_pRight;
		if (temp->m_pStone->GetColor() == color) return;
		else
			temp->m_pStone->SetColor(color);
	}
}
void OthelloBoard::Turn_UL(OthelloBoard* temp) {
	char color = temp->m_pStone->GetColor();

	while (temp->m_pUp->m_pLeft->m_pStone) {
		temp = temp->m_pUp->m_pLeft;
		if (temp->m_pStone->GetColor() == color) return;
		else
			temp->m_pStone->SetColor(color);
	}
}
void OthelloBoard::Turn_DR(OthelloBoard* temp) {
	char color = temp->m_pStone->GetColor();

	while (temp->m_pDown->m_pRight->m_pStone) {
		temp = temp->m_pDown->m_pRight;
		if (temp->m_pStone->GetColor() == color) return;
		else
			temp->m_pStone->SetColor(color);
	}
}
void OthelloBoard::Turn_DL(OthelloBoard* temp) {
	char color = temp->m_pStone->GetColor();

	while (temp->m_pDown->m_pLeft->m_pStone) {
		temp = temp->m_pDown->m_pLeft;
		if (temp->m_pStone->GetColor() == color) return;
		else
			temp->m_pStone->SetColor(color);
	}
}
