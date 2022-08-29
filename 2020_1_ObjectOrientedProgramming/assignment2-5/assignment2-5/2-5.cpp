#include <iostream>
#include "Patient.h"
using namespace std;

int main(void)
{
	const int t = 4; // test case의 수
	PatientInfo* info_arr[t]; //클래스 포인터 배열 선언

	char* name = new char[30]; // 이름을 입력받을 문자열 동적할당
	char* address = new char[30]; // 주소를 입력받을 문자열 동적할당

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

		// 입력받은 정보로 인스턴스 생성 
		info_arr[i] = new PatientInfo(name, address, r_num, p_num);
		cout << endl;
	}
	delete[] name; //동적할당한 메모리 해제
	delete[] address;

	// 저장된 정보 출력
	for (int i = 0; i < t; i++) {
		cout << info_arr[i]->getName() << endl;
		cout << info_arr[i]->getAddress() << endl;
		cout << info_arr[i]->get_R_Number() << endl;
		cout << info_arr[i]->get_P_Number() << endl << endl;
	}

	// 동적할당한 메모리 해제 (소멸자 호출)
	for (int i = 0; i < t; i++)
		delete info_arr[i];

	return 0;
}
