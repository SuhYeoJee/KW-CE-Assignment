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
	//c 방향으로 움직일 수 있는가?
	//U, D, R, L

	if ((c == 'u') || (c == 'U')) {
		//위가 막혀있지 않은 경우 간다.
		if (y != 0) {
			// 위에 다른 포켓몬이 없는 경우 간다.
			if (field[y - 1][x] == 0) {
				field[y][x] = 0;
				field[--y][x] = 1;
				return true;
			}
		}
	}
	else if ((c == 'd') || (c == 'D')) {
		//아래가 막혀있지 않은 경우 간다.
		if (y != 8) {
			// 아래에 다른 포켓몬이 없는 경우 간다.
			if (field[y + 1][x] == 0) {
				field[y][x] = 0;
				field[++y][x] = 1;
				return true;
			}
		}
	}
	else if ((c == 'r') || (c == 'R')) {
		//오른쪽이 막혀있지 않은 경우 간다.
		if (x != 8) {
			// 오른쪽에 다른 포켓몬이 없는 경우 간다.
			if (field[y][x + 1] == 0) {
				field[y][x] = 0;
				field[y][++x] = 1;
				return true;
			}
		}
	}
	else if ((c == 'l') || (c == 'L')) {
		//왼쪽이 막혀있지 않은 경우 간다.
		if (x != 0) {
			// 왼쪽에 다른 포켓몬이 없는 경우 간다.
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
	// n:공격 받는 포켓몬
	pokemon* p = this;
	if ((p->get_type() == n->get_type()) || (p->get_type() == 'E') || (n->get_type() == 'E')) // 2데미지
	{
		n->set_hp(2);
	}
	else if (((p->get_type() == 'F') && (n->get_type() == 'G')) || ((p->get_type() == 'W') && (n->get_type() == 'F')) || ((p->get_type() == 'G') && (n->get_type() == 'W'))) //3데미지
		n->set_hp(3);
	else
		n->set_hp(1);
	return;
}

bool Charmander::Attack(int(*field)[9], char direction, int x, int y) {
	//필드[y][x], 방향, 공격 받는 포켓몬 위치
	bool att = false;
	int t = 1;

	//방향전환
	if ((direction == 'r') || (direction == 'R')) t = 1;
	else if ((direction == 'l') || (direction == 'L')) t = -1;

	if ((get_x() + t < 9) && ((get_x() + t >= 0))) { //공격하는 칸
		if (((get_x() + t) == x) && ((get_y()) == y)) { //상대 포켓몬이 있음
			att = true; return att;
		} //공격자위치 (0,0)일때 (1,0) 혹은 (-1,0)
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
	//필드[y][x], 방향, 공격 받는 포켓몬 위치
	bool att = false;
	int t = 1;

	//방향전환
	if ((direction == 'r') || (direction == 'R')) t = 1;
	else if ((direction == 'l') || (direction == 'L')) t = -1;

	if ((get_x() + t < 9) && ((get_x() + t >= 0))) { //공격하는 칸
		if (((get_x() + t) == x) && ((get_y()) == y)) { //상대 포켓몬이 있음
			att = true; return att;
		} //공격자위치(x,y)가 (0,0)일때 (1,0) 혹은 (-1,0)
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
	//필드[y][x], 방향, 공격 받는 포켓몬 위치
	bool att = false;
	int t = 1;

	//방향전환
	if ((direction == 'r') || (direction == 'R')) t = 1;
	else if ((direction == 'l') || (direction == 'L')) t = -1;

	if ((get_x() + t < 9) && ((get_x() + t >= 0))) { //공격하는 칸
		if (((get_x() + t) == x) && ((get_y()) == y)) { //상대 포켓몬이 있음
			att = true; return att;
		} //공격자위치 (0,0)일때 (1,0) 혹은 (-1,0)
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
	//필드[y][x], 방향, 공격 받는 포켓몬 위치
	bool att = false;
	int t = 1;

	//방향전환
	if ((direction == 'r') || (direction == 'R')) t = 1;
	else if ((direction == 'l') || (direction == 'L')) t = -1;

	if ((get_x() + t < 9) && ((get_x() + t >= 0))) { //공격하는 칸
		if (((get_x() + t) == x) && ((get_y()) == y)) { //상대 포켓몬이 있음
			att = true; return att;
		} //공격자위치(x,y)가 (0,0)일때 (1,0) 혹은 (-1,0)
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