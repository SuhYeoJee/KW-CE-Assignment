#pragma once
class Buyer;

class Pharmacist {
private:
	int stock; // ���
	int price; // ����

public:
	Pharmacist(int _stock, int _price);
	void say_stock(void); // ��� ����(cout)
	void say_price(void); // ������ ����
	void sell(Buyer* buyer); //�����ڿ��� ����ũ �Ǹ�
};

class Buyer {
private:
	int hold;
	int wallet;

public:
	Buyer(int _hold, int _wallet);
	void func1(Pharmacist pharm); // ��翡�� ��� ���
	void func2(Pharmacist pharm); // ��翡�� ������ ���
	void say_hold(void); // �������� ����
	void say_wallet(void); // �ܾ��� ����
	int how_many(void); // ������ ������ ������
	int give_money(void); // �ܾ��� ��� �ǳ�
	void recive(int amount, int change); // ������ ����ũ�� �ܵ��� ����
};