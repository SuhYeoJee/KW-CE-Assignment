#pragma once

class PatientInfo {
private:
	char* name;
	char* address;
	int registration_number;
	int phone_number;

public:
	PatientInfo(char* _name, char* _address, int r_num, int p_num);
	~PatientInfo();

	// Ŭ���� ������ ���� ��ȯ
	char* getName() { return name; }
	char* getAddress() { return address; }
	int get_R_Number() { return registration_number; }
	int get_P_Number() { return phone_number; }
};
