#pragma once
#include "pokemon.h"
#include <cstring>
#include <windows.h> 

class player
{
private:
	Charmander* C;
	Squirtle* S;
	Bulbasaur* B;
	Pikachu* P;

	const char* name;
	int playerNumber;
public:
	player(int pNum);
	player(char* N, int pNum);
	~player();
	void battle(int(*field)[9], player* plr, int select, char direction);

	void print(int j, int i);// � ���ϸ��� j,i�� �ִ� ��� ���ϸ��� �̸� ���
	void HPprint(void);//��� ���ϸ��� ü�� ���

	const char* getName(void) { return name; }
	Charmander* getC(void) { return C; }
	Squirtle* getS(void) { return S; }
	Bulbasaur* getB(void) { return B; }
	Pikachu* getP(void) { return P; }

	void setC(void) { C = NULL; }
	void setS(void) { S = NULL; }
	void setB(void) { B = NULL; }
	void setP(void) { P = NULL; }

};

