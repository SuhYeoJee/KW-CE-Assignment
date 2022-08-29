#include <string>
#include "Patient.h"


PatientInfo::PatientInfo(char* _name, char* _address, int r_num, int p_num) {
	name = new char[30]; //메모리 할당
	strcpy_s(name, 5, _name); //문자열 복사
	address = new char[30];
	strcpy_s(address, 10, _address);
	registration_number = r_num; //값 복사
	phone_number = p_num;
}

PatientInfo::~PatientInfo() {
	//할당된 메모리 해제
	if (name != NULL) {
		delete name;
	}
	if (address != NULL) {
		delete address;
	}
}
