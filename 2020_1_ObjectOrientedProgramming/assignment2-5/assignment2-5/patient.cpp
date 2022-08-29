#include <string>
#include "Patient.h"


PatientInfo::PatientInfo(char* _name, char* _address, int r_num, int p_num) {
	name = new char[30]; //�޸� �Ҵ�
	strcpy_s(name, 5, _name); //���ڿ� ����
	address = new char[30];
	strcpy_s(address, 10, _address);
	registration_number = r_num; //�� ����
	phone_number = p_num;
}

PatientInfo::~PatientInfo() {
	//�Ҵ�� �޸� ����
	if (name != NULL) {
		delete name;
	}
	if (address != NULL) {
		delete address;
	}
}
