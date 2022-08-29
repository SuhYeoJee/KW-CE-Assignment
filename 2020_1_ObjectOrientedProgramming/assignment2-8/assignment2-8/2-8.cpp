#include <iostream>
#include "exchange.h"
using namespace std;

int main(void)
{
	double result = -1, original = 5;
	char from[4], c[3], to[4];
	while (1)
	{
		cout << "��Currency Converter��" << endl;
		cout << "e.g. [Price] KRW to USD" << endl << endl;
		cin >> original >> from >> c >> to; //�Է¹���

		if (strcmp(c, "to")) {
			cout << "Input error" << endl;
			break;
		} // [����] ����� �Է����� ���� ���

		if (strcmp(from, "KRW")) { // krw�� �ƴ� ȭ�� ��ȯ�ϴ� ��� krw�� ��ȯ

			if ((strcmp(from, "USD")) && (strcmp(from, "JPY")) && (strcmp(from, "EUR")) && (strcmp(from, "CNY"))) { //[����] �Է¿���
				cout << "Input error" << endl;
				break;
			}
			ToKRW krw(original, from);
			original = krw.GetResult();
			from[0] = 'K'; from[1] = 'R'; from[2] = 'W';
		} // from�� �߸� �Է��� ��� ����

		//krw���� to�� ��ȯ
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

		//��� ���
		if (result < 0) { // [����]
			cout << "Input error" << endl;
			return -1;
		}
		else {
			cout << fixed; cout.precision(0); // �ݿø�
			cout << result << ' ' << to << endl << endl;
		}

		// ���� Ȯ��
		char s;
		cout << "Would you like to continue? (Y/N)" << endl;
		cin >> s;
		if ((s == 'N') || (s == 'n')) {
			cout << "Bye!" << endl;
			break;
		}
		else if ((s == 'Y') || (s == 'y')) {
			system("cls"); //ȭ�� �ʱ�ȭ
			continue;
		}
		else { //[����]
			cout << "Input error" << endl;
			break;
		}
	}
	return 0;
}