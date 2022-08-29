#pragma once
class Buyer;

class Pharmacist {
private:
	int stock; // 재고
	int price; // 가격

public:
	Pharmacist(int _stock, int _price);
	void say_stock(void); // 재고를 말함(cout)
	void say_price(void); // 가격을 말함
	void sell(Buyer* buyer); //구매자에게 마스크 판매
};

class Buyer {
private:
	int hold;
	int wallet;

public:
	Buyer(int _hold, int _wallet);
	void func1(Pharmacist pharm); // 약사에게 재고를 물어봄
	void func2(Pharmacist pharm); // 약사에게 가격을 물어봄
	void say_hold(void); // 보유량을 말함
	void say_wallet(void); // 잔액을 말함
	int how_many(void); // 구입할 수량을 전달함
	int give_money(void); // 잔액을 모두 건넴
	void recive(int amount, int change); // 구입한 마스크와 잔돈을 받음
};