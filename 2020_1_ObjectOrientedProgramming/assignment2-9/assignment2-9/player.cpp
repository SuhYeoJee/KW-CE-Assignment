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
{ // � ���ϸ��� j,i�� �ִ� ��� ���ϸ��� �̸� ���

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
	//���ϸ� ü�� ���
	char z = 'X';
	cout << " C: ";

	if (getC() == NULL) { //������
		cout << z;
	}
	else {
		int i = getC()->get_hp();
		cout << i;
	}

	cout << " S: ";
	if (getS() == NULL) { //������
		cout << z;
	}
	else {
		int i = getS()->get_hp();
		cout << i;
	}

	cout << " B: ";
	if (getB() == NULL) { //������
		cout << z;
	}
	else {
		int i = getB()->get_hp();
		cout << i;
	}
	cout << " P: ";
	if (getP() == NULL) { //������
		cout << z;
	}
	else {
		int i = getP()->get_hp();
		cout << i;
	}

	cout << endl;
}

void player::battle(int(*field)[9], player* plr, int select, char direction)
{	//�ʵ�(y,x), ���ݹ޴� �����, �����ϴ� ���ϸ�, ����	
	bool att = false;
	int s = 0;

	switch (select)
	{
	case(1):
		if (getC() == NULL) {
			cout << "���̸��� �̹� ���������ϴ�." << endl;
			return;
		}
		cout << getName() << "�� ���̸��� �Ҳɼ���!" << endl;

		if (plr->getC() != NULL)
		{
			att = getC()->Attack(field, direction, plr->getC()->get_x(), plr->getC()->get_y());
			if (att) {//���̸� - ���̸� ���ݼ���
				getC()->damage(plr->getC());
				if (plr->getC()->get_hp() <= 0) { //������
					cout << "���̸��� ��������!" << endl;
					field[plr->getC()->get_y()][plr->getC()->get_x()] = 0; // field���� ����
					delete plr->getC();
					plr->setC();
				}
				s++;
			}
		}

		if (plr->getS() != NULL)
		{
			att = getC()->Attack(field, direction, plr->getS()->get_x(), plr->getS()->get_y());
			if (att) {//���̸� - ���α���ݼ���
				getC()->damage(plr->getS());
				if (plr->getS()->get_hp() <= 0) { //������
					cout << "���α�� ��������!" << endl;
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
			if (att) {//���̸� - �̻��ؾ� ���ݼ���
				getC()->damage(plr->getB());
				if (plr->getB()->get_hp() <= 0) { //������
					cout << "�̻��ؾ��� ��������!" << endl;
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
			if (att) {//���̸� - ��ī�� ���ݼ���
				//�������޼ҵ� ȣ��
				getC()->damage(plr->getP());
				if (plr->getP()->get_hp() <= 0) { //������
					cout << "��ī��� ��������!" << endl;
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
			cout << "���α�� �̹� ���������ϴ�." << endl;
			return;
		}
		cout << getName() << "�� ���α��� ������!" << endl;

		if (plr->getC() != NULL)
		{
			att = getS()->Attack(field, direction, plr->getC()->get_x(), plr->getC()->get_y());
			if (att) {//���α� -> ���̸� ���ݼ���
				getS()->damage(plr->getC());
				if (plr->getC()->get_hp() <= 0) { //������
					cout << "���̸��� ��������!" << endl;
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
			if (att) {//���α� -> ���α���ݼ���
				getS()->damage(plr->getS());
				if (plr->getS()->get_hp() <= 0) { //������
					cout << "���α�� ��������!" << endl;
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
			if (att) {//���α� -> �̻��ؾ� ���ݼ���
				getS()->damage(plr->getB());
				if (plr->getB()->get_hp() <= 0) { //������
					cout << "�̻��ؾ��� ��������!" << endl;
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
			if (att) {//���α� - ��ī�� ���ݼ���
				getS()->damage(plr->getP());
				if (plr->getP()->get_hp() <= 0) { //������
					cout << "��ī��� ��������!" << endl;
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
			cout << "�̻��ؾ��� �̹� ���������ϴ�." << endl;
			return;
		}
		cout << getName() << "�� �̻��ؾ��� �ٳ�������!" << endl;

		if (plr->getC() != NULL)
		{
			att = getB()->Attack(field, direction, plr->getC()->get_x(), plr->getC()->get_y());
			if (att) {//�̻��ؾ� -> ���̸� ���ݼ���
				getB()->damage(plr->getC());
				if (plr->getC()->get_hp() <= 0) { //������
					cout << "���̸��� ��������!" << endl;
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
			if (att) {//�̻��ؾ� -> ���α���ݼ���
				getB()->damage(plr->getS());
				if (plr->getS()->get_hp() <= 0) { //������
					cout << "���α�� ��������!" << endl;
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
			if (att) {//�̻��ؾ� -> �̻��ؾ� ���ݼ���
				getB()->damage(plr->getB());
				if (plr->getB()->get_hp() <= 0) { //������
					cout << "�̻��ؾ��� ��������!" << endl;
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
			if (att) {//�̻��ؾ� - ��ī�� ���ݼ���
				getB()->damage(plr->getP());
				if (plr->getP()->get_hp() <= 0) { //������
					cout << "��ī��� ��������!" << endl;
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
			cout << "��ī��� �̹� ���������ϴ�." << endl;
			return;
		}
		cout << getName() << "�� ��ī���� ����ũ!" << endl;

		if (plr->getC() != NULL)
		{
			att = getP()->Attack(field, direction, plr->getC()->get_x(), plr->getC()->get_y());
			if (att) {//��ī�� -> ���̸� ���ݼ���
				getP()->damage(plr->getC());
				if (plr->getC()->get_hp() <= 0) { //������
					cout << "���̸��� ��������!" << endl;
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
			if (att) {//��ī�� -> ���α���ݼ���
				getP()->damage(plr->getS());
				if (plr->getS()->get_hp() <= 0) { //������
					cout << "���α�� ��������!" << endl;
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
			if (att) {//��ī�� -> �̻��ؾ� ���ݼ���
				getP()->damage(plr->getB());
				if (plr->getB()->get_hp() <= 0) { //������
					cout << "�̻��ؾ��� ��������!" << endl;
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
			if (att) {//��ī�� - ��ī�� ���ݼ���
				getP()->damage(plr->getP());
				if (plr->getP()->get_hp() <= 0) { //������
					cout << "��ī��� ��������!" << endl;
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
		cout << "������ ��������.." << endl;

	return;
}
