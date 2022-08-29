#pragma once
#include <iostream>
using namespace std;
class pokemon
{
private:
	int hp;
	int playerNum;
	int x = NULL;
	int y = NULL;
	char type;
public:
	pokemon(int pNum, char _type);
	~pokemon() {};
	bool move(char c, int(*field)[9]); //�̵������ϸ� �̵��ϰ� ��, �Ұ����ϸ� ����
	virtual bool Attack(int(*field)[9], char direction, int x, int y) = 0; //���������Լ�
	// ���ϸ󸶴� �ٸ� �������� ����, ������ ��, ���н� ����

	void damage(pokemon* n); //�󼺿� ���� ���ط� ���

	int get_hp(void) { return hp; }
	int get_pNum(void) { return playerNum; }
	int get_x(void) { return x; }
	int get_y(void) { return y; }
	char get_type(void) { return type; }

	void set_hp(int _damage) { hp -= _damage; }
	void set_x_y(int _x, int _y);

};

class Charmander : public pokemon
{
public:
	Charmander(int pNum, int _x, int _y, char _type) :pokemon(pNum, _type)
	{
		set_x_y(_x, _y);
	}
	virtual bool Attack(int(*field)[9], char direction, int x, int y);

};



class Squirtle : public pokemon
{
public:
	Squirtle(int pNum, int _x, int _y, char _type) :pokemon(pNum, _type)
	{
		set_x_y(_x, _y);
	}
	virtual bool Attack(int(*field)[9], char direction, int x, int y);
};

class Bulbasaur : public pokemon
{
public:
	Bulbasaur(int pNum, int _x, int _y, char _type) :pokemon(pNum, _type)
	{
		set_x_y(_x, _y);
	}
	virtual bool Attack(int(*field)[9], char direction, int x, int y);
};

class Pikachu : public pokemon
{
public:
	Pikachu(int pNum, int _x, int _y, char _type) :pokemon(pNum, _type)
	{
		set_x_y(_x, _y);
	}
	virtual bool Attack(int(*field)[9], char direction, int x, int y);
};
