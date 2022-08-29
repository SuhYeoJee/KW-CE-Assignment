#include "pokemon.h"

pokemon::pokemon(int pNum, char _type) {
	hp = 3;
	playerNum = pNum;
	type = _type;
}

void pokemon::set_x_y(int _x, int _y)
{
	x = _x; y = _y; return;
}

bool pokemon::move(char c, int(*field)[9])
{
	//c �������� ������ �� �ִ°�?
	//U, D, R, L

	if ((c == 'u') || (c == 'U')) {
		//���� �������� ���� ��� ����.
		if (y != 0) {
			// ���� �ٸ� ���ϸ��� ���� ��� ����.
			if (field[y - 1][x] == 0) {
				field[y][x] = 0;
				field[--y][x] = 1;
				return true;
			}
		}
	}
	else if ((c == 'd') || (c == 'D')) {
		//�Ʒ��� �������� ���� ��� ����.
		if (y != 8) {
			// �Ʒ��� �ٸ� ���ϸ��� ���� ��� ����.
			if (field[y + 1][x] == 0) {
				field[y][x] = 0;
				field[++y][x] = 1;
				return true;
			}
		}
	}
	else if ((c == 'r') || (c == 'R')) {
		//�������� �������� ���� ��� ����.
		if (x != 8) {
			// �����ʿ� �ٸ� ���ϸ��� ���� ��� ����.
			if (field[y][x + 1] == 0) {
				field[y][x] = 0;
				field[y][++x] = 1;
				return true;
			}
		}
	}
	else if ((c == 'l') || (c == 'L')) {
		//������ �������� ���� ��� ����.
		if (x != 0) {
			// ���ʿ� �ٸ� ���ϸ��� ���� ��� ����.
			if (field[y][x - 1] == 0) {
				field[y][x] = 0;
				field[y][--x] = 1;
				return true;
			}
		}
	}
	return false;
}

void pokemon::damage(pokemon* n)
{
	// n:���� �޴� ���ϸ�
	pokemon* p = this;
	if ((p->get_type() == n->get_type()) || (p->get_type() == 'E') || (n->get_type() == 'E')) // 2������
	{
		n->set_hp(2);
	}
	else if (((p->get_type() == 'F') && (n->get_type() == 'G')) || ((p->get_type() == 'W') && (n->get_type() == 'F')) || ((p->get_type() == 'G') && (n->get_type() == 'W'))) //3������
		n->set_hp(3);
	else
		n->set_hp(1);
	return;
}

bool Charmander::Attack(int(*field)[9], char direction, int x, int y) {
	//�ʵ�[y][x], ����, ���� �޴� ���ϸ� ��ġ
	bool att = false;
	int t = 1;

	//������ȯ
	if ((direction == 'r') || (direction == 'R')) t = 1;
	else if ((direction == 'l') || (direction == 'L')) t = -1;

	if ((get_x() + t < 9) && ((get_x() + t >= 0))) { //�����ϴ� ĭ
		if (((get_x() + t) == x) && ((get_y()) == y)) { //��� ���ϸ��� ����
			att = true; return att;
		} //��������ġ (0,0)�϶� (1,0) Ȥ�� (-1,0)
	}
	//else cout<< "Allies cannot attack.";

	if (((get_x() + t) < 9) && ((get_y() - 1) < 9) && ((get_x() + t) >= 0) && ((get_y() - 1) >= 0)) {
		if (((get_x() + t) == x) && ((get_y() - 1) == y)) {
			att = true; return att;
		} // (1,-1) || (-1,-1)
	}
	if (((get_x() + t) < 9) && ((get_y() + 1) < 9) && ((get_x() + t) >= 0) && ((get_y() + 1) >= 0)) {
		if (((get_x() + t) == x) && ((get_y() + 1) == y)) {
			att = true; return att;
		} // (1,1)||(-1,1)
	}
	if (((get_x() + t * 2) < 9) && ((get_y() + 1) < 9) && ((get_x() + t * 2) >= 0) && ((get_y() + 1) >= 0)) {
		if (((get_x() + t * 2) == x) && ((get_y() + 1) == y)) {
			att = true; return att;
		} // (2,1)||(-2,1)
	}
	if (((get_x() + t * 2) < 9) && ((get_y() - 1) < 9) && ((get_x() + t * 2) >= 0) && ((get_y() - 1) >= 0)) {
		if (((get_x() + t * 2) == x) && ((get_y() - 1) == y)) {
			att = true; return att;
		} //(2,-1)||(-2,-1)
	}
	return att;
}

bool Squirtle::Attack(int(*field)[9], char direction, int x, int y) {
	//�ʵ�[y][x], ����, ���� �޴� ���ϸ� ��ġ
	bool att = false;
	int t = 1;

	//������ȯ
	if ((direction == 'r') || (direction == 'R')) t = 1;
	else if ((direction == 'l') || (direction == 'L')) t = -1;

	if ((get_x() + t < 9) && ((get_x() + t >= 0))) { //�����ϴ� ĭ
		if (((get_x() + t) == x) && ((get_y()) == y)) { //��� ���ϸ��� ����
			att = true; return att;
		} //��������ġ(x,y)�� (0,0)�϶� (1,0) Ȥ�� (-1,0)
	}
	if ((get_x() + t * 2 < 9) && ((get_x() + t * 2 >= 0))) {
		if (((get_x() + t * 2) == x) && ((get_y()) == y)) {
			att = true; return att;
		} //(2,0) || (-2,0)
	}
	if ((get_y() + 1 < 9) && ((get_y() + t >= 0))) {
		if (((get_x()) == x) && ((get_y() + 1) == y)) {
			att = true; return att;
		} //(0,1)
	}
	if ((get_y() - 1 < 9) && ((get_y() + t >= 0))) {
		if (((get_x()) == x) && ((get_y() - 1) == y)) {
			att = true; return att;
		} //(0,-1)
	}
	return att;
}

bool Bulbasaur::Attack(int(*field)[9], char direction, int x, int y) {
	//�ʵ�[y][x], ����, ���� �޴� ���ϸ� ��ġ
	bool att = false;
	int t = 1;

	//������ȯ
	if ((direction == 'r') || (direction == 'R')) t = 1;
	else if ((direction == 'l') || (direction == 'L')) t = -1;

	if ((get_x() + t < 9) && ((get_x() + t >= 0))) { //�����ϴ� ĭ
		if (((get_x() + t) == x) && ((get_y()) == y)) { //��� ���ϸ��� ����
			att = true; return att;
		} //��������ġ (0,0)�϶� (1,0) Ȥ�� (-1,0)
	}
	if ((get_y() + 1 < 9) && ((get_y() + t >= 0))) {
		if (((get_x()) == x) && ((get_y() + 1) == y)) {
			att = true; return att;
		} //(0,1)
	}
	if ((get_y() - 1 < 9) && ((get_y() + t >= 0))) {
		if (((get_x()) == x) && ((get_y() - 1) == y)) {
			att = true; return att;
		} //(0,-1)
	}
	if (((get_x() + t) < 9) && ((get_y() - 1) < 9) && ((get_x() + t) >= 0) && ((get_y() - 1) >= 0)) {
		if (((get_x() + t) == x) && ((get_y() - 1) == y)) {
			att = true; return att;
		} // (1,-1) || (-1,-1)
	}
	if (((get_x() + t) < 9) && ((get_y() + 1) < 9) && ((get_x() + t) >= 0) && ((get_y() + 1) >= 0)) {
		if (((get_x() + t) == x) && ((get_y() + 1) == y)) {
			att = true; return att;
		} // (1,1)||(-1,1)
	}
	return att;
}

bool Pikachu::Attack(int(*field)[9], char direction, int x, int y) {
	//�ʵ�[y][x], ����, ���� �޴� ���ϸ� ��ġ
	bool att = false;
	int t = 1;

	//������ȯ
	if ((direction == 'r') || (direction == 'R')) t = 1;
	else if ((direction == 'l') || (direction == 'L')) t = -1;

	if ((get_x() + t < 9) && ((get_x() + t >= 0))) { //�����ϴ� ĭ
		if (((get_x() + t) == x) && ((get_y()) == y)) { //��� ���ϸ��� ����
			att = true; return att;
		} //��������ġ(x,y)�� (0,0)�϶� (1,0) Ȥ�� (-1,0)
	}
	if ((get_x() + t * 2 < 9) && ((get_x() + t * 2 >= 0))) {
		if (((get_x() + t * 2) == x) && ((get_y()) == y)) {
			att = true; return att;
		} //(2,0) || (-2,0)
	}
	if (((get_x() + t * 2) < 9) && ((get_y() + 1) < 9) && ((get_x() + t * 2) >= 0) && ((get_y() + 1) >= 0)) {
		if (((get_x() + t * 2) == x) && ((get_y() + 1) == y)) {
			att = true; return att;
		} // (2,1)||(-2,1)
	}
	if (((get_x() + t * 2) < 9) && ((get_y() - 1) < 9) && ((get_x() + t * 2) >= 0) && ((get_y() - 1) >= 0)) {
		if (((get_x() + t * 2) == x) && ((get_y() - 1) == y)) {
			att = true; return att;
		} //(2,-1)||(-2,-1)
	}


	return att;
}