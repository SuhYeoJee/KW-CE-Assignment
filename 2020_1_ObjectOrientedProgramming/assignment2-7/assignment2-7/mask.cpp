#include "mask.h"
#include <iostream>
using namespace std;

Pharmacist::Pharmacist(int _stock, int _price)
	: stock(_stock), price(_price) {};

void Pharmacist::say_stock(void) { //����ũ ��� ����
	cout << " ���� ����ũ ����: " << stock << "��" << endl;
	return;
}

void Pharmacist::say_price(void) { //����ũ ������ ����
	cout << " ����ũ ����: " << price << "��" << endl;
	return;
}

void Pharmacist::sell(Buyer* buyer) { //����ũ�� �Ǹ���
	int amount, change;
	cout << "�� ���� �����Ͻðڽ��ϱ�?" << endl;
	amount = buyer->how_many();

	int money = buyer->give_money();

	int buy;
	if (stock >= amount)
		buy = 1; // �䱸������ ��� ���� ��� (���� ����)
	else
		buy = 2; // ��� �����Ѱ�� (���� �Ұ�)

	if (money > amount * price)
		buy *= -1; // �ܾ��� �Ѿ׺��� ���� ��� (���Ű���)

	switch (buy) {
	case (-1)://���ż���
		change = money - amount * price;
		stock -= amount;
		buyer->recive(amount, change);
		cout << amount << "���� ���� �Ϸ�." << endl;
		break;
	case (1)://�ܾ׺���
		cout << "�ܾ��� �����մϴ�." << endl;
		break;
	case(-2)://������
		cout << "����ũ ��� �����մϴ�." << endl;
		break;
	case(2)://���, �ݾ׺���
		cout << "����ũ ���� �ܾ��� ��� �����մϴ�." << endl;
		break;
	}
	return;
}


Buyer::Buyer(int _hold, int _wallet)
	: hold(_hold), wallet(_wallet) {};

void Buyer::func1(Pharmacist pharm) { //��� ���
	pharm.say_stock();
	return;
}

void Buyer::func2(Pharmacist pharm) { //������ ���
	pharm.say_price();
	return;
}

void Buyer::say_hold(void) { //�������� ����
	cout << "�� ����ũ ����: " << hold << "��" << endl;
	return;
}

void Buyer::say_wallet(void) { // �ܾ��� ����
	cout << "�� �ܾ�: " << wallet << "��" << endl;
	return;
}

int Buyer::how_many(void) { // ������ ������ ������
	int amount;
	cin >> amount;
	return amount;
}

int Buyer::give_money(void) { // �ܾ��� ��� �ǳ�
	return wallet;
}

void Buyer::recive(int amount, int change) { // ������ ����ũ�� �ܵ��� ����
	this->hold += amount;
	this->wallet = change;
	return;
}
