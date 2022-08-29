#include <iostream>
#include "exchange.h"
using namespace std;

int main(void)
{
	double result = -1, original = 5;
	char from[4], c[3], to[4];
	while (1)
	{
		cout << "★Currency Converter★" << endl;
		cout << "e.g. [Price] KRW to USD" << endl << endl;
		cin >> original >> from >> c >> to; //입력받음

		if (strcmp(c, "to")) {
			cout << "Input error" << endl;
			break;
		} // [오류] 제대로 입력하지 않은 경우

		if (strcmp(from, "KRW")) { // krw이 아닌 화폐를 변환하는 경우 krw로 전환

			if ((strcmp(from, "USD")) && (strcmp(from, "JPY")) && (strcmp(from, "EUR")) && (strcmp(from, "CNY"))) { //[오류] 입력오류
				cout << "Input error" << endl;
				break;
			}
			ToKRW krw(original, from);
			original = krw.GetResult();
			from[0] = 'K'; from[1] = 'R'; from[2] = 'W';
		} // from을 잘못 입력한 경우 음수

		//krw에서 to로 전환
		if (!strcmp(to, "KRW")) //KRW -> KRW
			result = original;
		else if (!strcmp(to, "USD")) { //KRW -> USD
			ToUSD usd(original, from);
			result = usd.GetResult();
		}
		else if (!strcmp(to, "JPY")) {//KRW -> JPY
			ToJPY jpy(original, from);
			result = jpy.GetResult();
		}
		else if (!strcmp(to, "EUR")) {//KRW -> EUR
			ToEUR eur(original, from);
			result = eur.GetResult();
		}
		else if (!strcmp(to, "CNY")) {//KRW -> CNY
			ToCNY cny(original, from);
			result = cny.GetResult();
		}

		//결과 출력
		if (result < 0) { // [오류]
			cout << "Input error" << endl;
			return -1;
		}
		else {
			cout << fixed; cout.precision(0); // 반올림
			cout << result << ' ' << to << endl << endl;
		}

		// 종료 확인
		char s;
		cout << "Would you like to continue? (Y/N)" << endl;
		cin >> s;
		if ((s == 'N') || (s == 'n')) {
			cout << "Bye!" << endl;
			break;
		}
		else if ((s == 'Y') || (s == 'y')) {
			system("cls"); //화면 초기화
			continue;
		}
		else { //[오류]
			cout << "Input error" << endl;
			break;
		}
	}
	return 0;
}