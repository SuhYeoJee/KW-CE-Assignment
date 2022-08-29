#include <iostream>
#include "Patient.h"
using namespace std;

int main(void)
{
	const int t = 4; // test case�� ��
	PatientInfo* info_arr[t]; //Ŭ���� ������ �迭 ����

	char* name = new char[30]; // �̸��� �Է¹��� ���ڿ� �����Ҵ�
	char* address = new char[30]; // �ּҸ� �Է¹��� ���ڿ� �����Ҵ�

	for (int i = 0; i < t; i++) {
		int r_num, p_num;

		cout << "Name: ";
		cin >> name;
		cout << "Address: ";
		cin >> address;
		cout << "Registration Number: ";
		cin >> r_num;
		cout << "Phone Number: ";
		cin >> p_num;

		// �Է¹��� ������ �ν��Ͻ� ���� 
		info_arr[i] = new PatientInfo(name, address, r_num, p_num);
		cout << endl;
	}
	delete[] name; //�����Ҵ��� �޸� ����
	delete[] address;

	// ����� ���� ���
	for (int i = 0; i < t; i++) {
		cout << info_arr[i]->getName() << endl;
		cout << info_arr[i]->getAddress() << endl;
		cout << info_arr[i]->get_R_Number() << endl;
		cout << info_arr[i]->get_P_Number() << endl << endl;
	}

	// �����Ҵ��� �޸� ���� (�Ҹ��� ȣ��)
	for (int i = 0; i < t; i++)
		delete info_arr[i];

	return 0;
}
