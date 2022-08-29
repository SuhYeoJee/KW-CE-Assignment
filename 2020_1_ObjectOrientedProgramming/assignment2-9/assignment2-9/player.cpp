#include "player.h"

player::player(int pNum)
{
	int x;
	if (pNum == 1) { name = "player1"; x = 0; }
	else { name = "player2"; x = 8; }
	playerNumber = pNum;
	C = new Charmander(pNum, x, 1, 'F');
	S = new Squirtle(pNum, x, 3, 'W');
	B = new Bulbasaur(pNum, x, 7, 'G');
	P = new Pikachu(pNum, x, 5, 'E');
}

player::player(char* N, int pNum)
{
	int x;
	name = N;
	playerNumber = pNum;
	if (pNum == 1) { x = 0; }
	else { x = 8; }
	C = new Charmander(pNum, x, 1, 'F');
	S = new Squirtle(pNum, x, 3, 'W');
	B = new Bulbasaur(pNum, x, 7, 'G');
	P = new Pikachu(pNum, x, 5, 'E');
}

player::~player()
{
	if ((C == NULL) && (S == NULL) && (B == NULL) && (P == NULL))
		cout << getName() << " lose." << endl;
	else {
		cout << getName() << " win!" << endl;
		if (C != NULL)
			delete C;
		if (S != NULL)
			delete S;
		if (B != NULL)
			delete B;
		if (P != NULL)
			delete P;
	}
}

void player::print(int j, int i)
{ // 어떤 포켓몬이 j,i에 있는 경우 포켓몬의 이름 출력

	if (getC() != NULL)
	{
		if ((getC()->get_x() == j) && (getC()->get_y() == i))
			cout << 'C' << playerNumber;
	}
	if (getS() != NULL)
	{
		if ((getS()->get_x() == j) && (getS()->get_y() == i))
			cout << 'S' << playerNumber;
	}
	if (getB() != NULL)
	{
		if ((getB()->get_x() == j) && (getB()->get_y() == i))
			cout << 'B' << playerNumber;
	}
	if (getP() != NULL)
	{
		if ((getP()->get_x() == j) && (getP()->get_y() == i))
			cout << 'P' << playerNumber;
	}
	return;
}

void player::HPprint(void)
{
	//포켓몬 체력 출력
	char z = 'X';
	cout << " C: ";

	if (getC() == NULL) { //쓰러짐
		cout << z;
	}
	else {
		int i = getC()->get_hp();
		cout << i;
	}

	cout << " S: ";
	if (getS() == NULL) { //쓰러짐
		cout << z;
	}
	else {
		int i = getS()->get_hp();
		cout << i;
	}

	cout << " B: ";
	if (getB() == NULL) { //쓰러짐
		cout << z;
	}
	else {
		int i = getB()->get_hp();
		cout << i;
	}
	cout << " P: ";
	if (getP() == NULL) { //쓰러짐
		cout << z;
	}
	else {
		int i = getP()->get_hp();
		cout << i;
	}

	cout << endl;
}

void player::battle(int(*field)[9], player* plr, int select, char direction)
{	//필드(y,x), 공격받는 사용자, 공격하는 포켓몬, 방향	
	bool att = false;
	int s = 0;

	switch (select)
	{
	case(1):
		if (getC() == NULL) {
			cout << "파이리는 이미 쓰러졌습니다." << endl;
			return;
		}
		cout << getName() << "의 파이리의 불꽃세례!" << endl;

		if (plr->getC() != NULL)
		{
			att = getC()->Attack(field, direction, plr->getC()->get_x(), plr->getC()->get_y());
			if (att) {//파이리 - 파이리 공격성공
				getC()->damage(plr->getC());
				if (plr->getC()->get_hp() <= 0) { //쓰러짐
					cout << "파이리는 쓰러졌다!" << endl;
					field[plr->getC()->get_y()][plr->getC()->get_x()] = 0; // field에서 지움
					delete plr->getC();
					plr->setC();
				}
				s++;
			}
		}

		if (plr->getS() != NULL)
		{
			att = getC()->Attack(field, direction, plr->getS()->get_x(), plr->getS()->get_y());
			if (att) {//파이리 - 꼬부기공격성공
				getC()->damage(plr->getS());
				if (plr->getS()->get_hp() <= 0) { //쓰러짐
					cout << "꼬부기는 쓰러졌다!" << endl;
					field[plr->getS()->get_y()][plr->getS()->get_x()] = 0;
					delete plr->getS();
					plr->setS();
				}
				s++;
			}
		}

		if (plr->getC() != NULL)
		{
			att = getC()->Attack(field, direction, plr->getB()->get_x(), plr->getB()->get_y());
			if (att) {//파이리 - 이상해씨 공격성공
				getC()->damage(plr->getB());
				if (plr->getB()->get_hp() <= 0) { //쓰러짐
					cout << "이상해씨는 쓰러졌다!" << endl;
					field[plr->getB()->get_y()][plr->getB()->get_x()] = 0;
					delete plr->getB();
					plr->setB();
				}
				s++;
			}

		}

		if (plr->getP() != NULL)
		{
			att = getC()->Attack(field, direction, plr->getP()->get_x(), plr->getP()->get_y());
			if (att) {//파이리 - 피카츄 공격성공
				//데미지메소드 호출
				getC()->damage(plr->getP());
				if (plr->getP()->get_hp() <= 0) { //쓰러짐
					cout << "피카츄는 쓰러졌다!" << endl;
					field[plr->getP()->get_y()][plr->getP()->get_x()] = 0;
					delete plr->getP();
					plr->setP();
				}
				s++;
			}
		}

		break;

	case(2):
		if (getS() == NULL) {
			cout << "꼬부기는 이미 쓰러졌습니다." << endl;
			return;
		}
		cout << getName() << "의 꼬부기의 물대포!" << endl;

		if (plr->getC() != NULL)
		{
			att = getS()->Attack(field, direction, plr->getC()->get_x(), plr->getC()->get_y());
			if (att) {//꼬부기 -> 파이리 공격성공
				getS()->damage(plr->getC());
				if (plr->getC()->get_hp() <= 0) { //쓰러짐
					cout << "파이리는 쓰러졌다!" << endl;
					field[plr->getC()->get_y()][plr->getC()->get_x()] = 0;
					delete plr->getC();
					plr->setC();
				}
				s++;
			}
		}

		if (plr->getS() != NULL)
		{
			att = getS()->Attack(field, direction, plr->getS()->get_x(), plr->getS()->get_y());
			if (att) {//꼬부기 -> 꼬부기공격성공
				getS()->damage(plr->getS());
				if (plr->getS()->get_hp() <= 0) { //쓰러짐
					cout << "꼬부기는 쓰러졌다!" << endl;
					field[plr->getS()->get_y()][plr->getS()->get_x()] = 0;
					delete plr->getS();
					plr->setS();
				}
				s++;
			}

		}

		if (plr->getB() != NULL)
		{
			att = getS()->Attack(field, direction, plr->getB()->get_x(), plr->getB()->get_y());
			if (att) {//꼬부기 -> 이상해씨 공격성공
				getS()->damage(plr->getB());
				if (plr->getB()->get_hp() <= 0) { //쓰러짐
					cout << "이상해씨는 쓰러졌다!" << endl;
					field[plr->getB()->get_y()][plr->getB()->get_x()] = 0;
					delete plr->getB();
					plr->setB();
				}
				s++;
			}
		}

		if (plr->getP() != NULL)
		{
			att = getS()->Attack(field, direction, plr->getP()->get_x(), plr->getP()->get_y());
			if (att) {//꼬부기 - 피카츄 공격성공
				getS()->damage(plr->getP());
				if (plr->getP()->get_hp() <= 0) { //쓰러짐
					cout << "피카츄는 쓰러졌다!" << endl;
					field[plr->getP()->get_y()][plr->getP()->get_x()] = 0;
					delete plr->getP();
					plr->setP();
				}
				s++;
			}
		}

		break;

	case(3):
		if (getB() == NULL) {
			cout << "이상해씨는 이미 쓰러졌습니다." << endl;
			return;
		}
		cout << getName() << "의 이상해씨의 잎날가르기!" << endl;

		if (plr->getC() != NULL)
		{
			att = getB()->Attack(field, direction, plr->getC()->get_x(), plr->getC()->get_y());
			if (att) {//이상해씨 -> 파이리 공격성공
				getB()->damage(plr->getC());
				if (plr->getC()->get_hp() <= 0) { //쓰러짐
					cout << "파이리는 쓰러졌다!" << endl;
					field[plr->getC()->get_y()][plr->getC()->get_x()] = 0;
					delete plr->getC();
					plr->setC();
				}
				s++;
			}
		}

		if (plr->getS() != NULL)
		{
			att = getB()->Attack(field, direction, plr->getS()->get_x(), plr->getS()->get_y());
			if (att) {//이상해씨 -> 꼬부기공격성공
				getB()->damage(plr->getS());
				if (plr->getS()->get_hp() <= 0) { //쓰러짐
					cout << "꼬부기는 쓰러졌다!" << endl;
					field[plr->getS()->get_y()][plr->getS()->get_x()] = 0;
					delete plr->getS();
					plr->setS();
				}
				s++;
			}

		}

		if (plr->getB() != NULL)
		{
			att = getB()->Attack(field, direction, plr->getB()->get_x(), plr->getB()->get_y());
			if (att) {//이상해씨 -> 이상해씨 공격성공
				getB()->damage(plr->getB());
				if (plr->getB()->get_hp() <= 0) { //쓰러짐
					cout << "이상해씨는 쓰러졌다!" << endl;
					field[plr->getB()->get_y()][plr->getB()->get_x()] = 0;
					delete plr->getB();
					plr->setB();
				}
				s++;
			}
		}

		if (plr->getP() != NULL)
		{
			att = getB()->Attack(field, direction, plr->getP()->get_x(), plr->getP()->get_y());
			if (att) {//이상해씨 - 피카츄 공격성공
				getB()->damage(plr->getP());
				if (plr->getP()->get_hp() <= 0) { //쓰러짐
					cout << "피카츄는 쓰러졌다!" << endl;
					field[plr->getP()->get_y()][plr->getP()->get_x()] = 0;
					delete plr->getP();
					plr->setP();
				}
				s++;
			}
		}

		break;


	case(4):
		if (getP() == NULL) {
			cout << "피카츄는 이미 쓰러졌습니다." << endl;
			return;
		}
		cout << getName() << "의 피카츄의 스파크!" << endl;

		if (plr->getC() != NULL)
		{
			att = getP()->Attack(field, direction, plr->getC()->get_x(), plr->getC()->get_y());
			if (att) {//피카츄 -> 파이리 공격성공
				getP()->damage(plr->getC());
				if (plr->getC()->get_hp() <= 0) { //쓰러짐
					cout << "파이리는 쓰러졌다!" << endl;
					field[plr->getC()->get_y()][plr->getC()->get_x()] = 0;
					delete plr->getC();
					plr->setC();
				}
				s++;
			}
		}

		if (plr->getS() != NULL)
		{
			att = getP()->Attack(field, direction, plr->getS()->get_x(), plr->getS()->get_y());
			if (att) {//피카츄 -> 꼬부기공격성공
				getP()->damage(plr->getS());
				if (plr->getS()->get_hp() <= 0) { //쓰러짐
					cout << "꼬부기는 쓰러졌다!" << endl;
					field[plr->getS()->get_y()][plr->getS()->get_x()] = 0;
					delete plr->getS();
					plr->setS();
				}
				s++;
			}

		}

		if (plr->getB() != NULL)
		{
			att = getP()->Attack(field, direction, plr->getB()->get_x(), plr->getB()->get_y());
			if (att) {//피카츄 -> 이상해씨 공격성공
				getP()->damage(plr->getB());
				if (plr->getB()->get_hp() <= 0) { //쓰러짐
					cout << "이상해씨는 쓰러졌다!" << endl;
					field[plr->getB()->get_y()][plr->getB()->get_x()] = 0;
					delete plr->getB();
					plr->setB();
				}
				s++;
			}
		}

		if (plr->getP() != NULL)
		{
			att = getP()->Attack(field, direction, plr->getP()->get_x(), plr->getP()->get_y());
			if (att) {//피카츄 - 피카츄 공격성공
				getP()->damage(plr->getP());
				if (plr->getP()->get_hp() <= 0) { //쓰러짐
					cout << "피카츄는 쓰러졌다!" << endl;
					field[plr->getP()->get_y()][plr->getP()->get_x()] = 0;
					delete plr->getP();
					plr->setP();
				}
				s++;
			}
		}

		break;
	}

	if (s == 0)
		cout << "공격은 빗나갔다.." << endl;

	return;
}
