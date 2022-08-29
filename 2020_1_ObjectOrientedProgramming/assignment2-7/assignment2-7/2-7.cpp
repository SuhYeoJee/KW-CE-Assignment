#include <iostream>
#include "mask.h"
using namespace std;

int main(void)
{
	//재고:7, 가격:1500
	Pharmacist pharm(7, 1500);
	//보유량:1, 지갑:5000
	Buyer buyer(1, 5000);

	int num;
	while (1) {
		cout << "0. 프로그램 종료" << endl;
		cout << "1. 마스크 재고 물어보기" << endl;
		cout << "2. 마스크 가격 물어보기" << endl;
		cout << "3. 마스크 구매하기" << endl;
		cout << "4. 내 마스크 갯수 확인하기" << endl;
		cout << "5. 내 지갑 확인하기" << endl;
		cin >> num;

		switch (num) { //사용자 입력에 따라 실행
		case(0):
			cout << "프로그램 종료";
			break;
		case(1):
			buyer.func1(pharm); //재고확인
			break;
		case(2):
			buyer.func2(pharm); //가격확인
			break;
		case(3):
			pharm.sell(&buyer); //구매
			break;
		case(4):
			buyer.say_hold(); //보유량확인
			break;
		case(5):
			buyer.say_wallet(); //지갑확인
			break;
		default: // [예외] 메뉴에 없는 숫자인 경우
			cout << "다시 입력하세요." << endl;
			break;
		}
		if (!num) // 0이 입력된 경우 while문 종료
			break;
		cout << endl;
	}
	return 0;
}

