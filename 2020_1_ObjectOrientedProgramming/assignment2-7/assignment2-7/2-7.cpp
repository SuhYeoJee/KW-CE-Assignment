#include <iostream>
#include "mask.h"
using namespace std;

int main(void)
{
	//���:7, ����:1500
	Pharmacist pharm(7, 1500);
	//������:1, ����:5000
	Buyer buyer(1, 5000);

	int num;
	while (1) {
		cout << "0. ���α׷� ����" << endl;
		cout << "1. ����ũ ��� �����" << endl;
		cout << "2. ����ũ ���� �����" << endl;
		cout << "3. ����ũ �����ϱ�" << endl;
		cout << "4. �� ����ũ ���� Ȯ���ϱ�" << endl;
		cout << "5. �� ���� Ȯ���ϱ�" << endl;
		cin >> num;

		switch (num) { //����� �Է¿� ���� ����
		case(0):
			cout << "���α׷� ����";
			break;
		case(1):
			buyer.func1(pharm); //���Ȯ��
			break;
		case(2):
			buyer.func2(pharm); //����Ȯ��
			break;
		case(3):
			pharm.sell(&buyer); //����
			break;
		case(4):
			buyer.say_hold(); //������Ȯ��
			break;
		case(5):
			buyer.say_wallet(); //����Ȯ��
			break;
		default: // [����] �޴��� ���� ������ ���
			cout << "�ٽ� �Է��ϼ���." << endl;
			break;
		}
		if (!num) // 0�� �Էµ� ��� while�� ����
			break;
		cout << endl;
	}
	return 0;
}

