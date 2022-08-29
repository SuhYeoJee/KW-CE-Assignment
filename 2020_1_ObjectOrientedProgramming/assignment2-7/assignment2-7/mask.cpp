#include "mask.h"
#include <iostream>
using namespace std;

Pharmacist::Pharmacist(int _stock, int _price)
	: stock(_stock), price(_price) {};

void Pharmacist::say_stock(void) { //마스크 재고를 말함
	cout << " 남은 마스크 갯수: " << stock << "개" << endl;
	return;
}

void Pharmacist::say_price(void) { //마스크 가격을 말함
	cout << " 마스크 가격: " << price << "원" << endl;
	return;
}

void Pharmacist::sell(Buyer* buyer) { //마스크를 판매함
	int amount, change;
	cout << "몇 개를 구매하시겠습니까?" << endl;
	amount = buyer->how_many();

	int money = buyer->give_money();

	int buy;
	if (stock >= amount)
		buy = 1; // 요구량보다 재고가 많은 경우 (구매 가능)
	else
		buy = 2; // 재고가 부족한경우 (구매 불가)

	if (money > amount * price)
		buy *= -1; // 잔액이 총액보다 많은 경우 (구매가능)

	switch (buy) {
	case (-1)://구매성공
		change = money - amount * price;
		stock -= amount;
		buyer->recive(amount, change);
		cout << amount << "개를 구매 완료." << endl;
		break;
	case (1)://잔액부족
		cout << "잔액이 부족합니다." << endl;
		break;
	case(-2)://재고부족
		cout << "마스크 재고가 부족합니다." << endl;
		break;
	case(2)://재고, 금액부족
		cout << "마스크 재고와 잔액이 모두 부족합니다." << endl;
		break;
	}
	return;
}


Buyer::Buyer(int _hold, int _wallet)
	: hold(_hold), wallet(_wallet) {};

void Buyer::func1(Pharmacist pharm) { //재고를 물어봄
	pharm.say_stock();
	return;
}

void Buyer::func2(Pharmacist pharm) { //가격을 물어봄
	pharm.say_price();
	return;
}

void Buyer::say_hold(void) { //보유량을 말함
	cout << "내 마스크 갯수: " << hold << "개" << endl;
	return;
}

void Buyer::say_wallet(void) { // 잔액을 말함
	cout << "내 잔액: " << wallet << "원" << endl;
	return;
}

int Buyer::how_many(void) { // 구입할 수량을 전달함
	int amount;
	cin >> amount;
	return amount;
}

int Buyer::give_money(void) { // 잔액을 모두 건넴
	return wallet;
}

void Buyer::recive(int amount, int change) { // 구입한 마스크와 잔돈을 받음
	this->hold += amount;
	this->wallet = change;
	return;
}
