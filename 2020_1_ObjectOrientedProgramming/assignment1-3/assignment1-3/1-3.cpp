#include <iostream>

int main(void) {
	int N;
	std::cout << "Input N: ";
	std::cin >> N;

	char* bitstream = new char[50];
	std::cout << "Input Bitstream: ";
	std::cin >> bitstream;
	
	int n = 0;
	while (n++ < N) {
		int length = 0;
		while (bitstream[++length]);

		//bitstream ���� ����
		char* p = new char[length + 2];
		for (int i = 0; i < length; i++) {
			p[i] = bitstream[length - 1 - i];
			//����ó��
			if ((p[i] != '0') && (p[i] != '1')) {
				std::cout << "bitstream is unsuitable" << std::endl;
				return -1;
			}
		}

		delete[] bitstream;

		//��Ʈ ������
		for (int i = 0; i < length; i++) {
			if (p[i] == '0') p[i] = '1';
			else p[i] = '0';
		}
		//������ ��Ʈ ���ϱ�
		if (n % 2) p[length] = '1';
		else p[length] = '0';
		p[length + 1] = 0; //���ڿ��� ��

		bitstream = new char[length + 2];
		for (int i = 0; i < length + 2; i++)
			bitstream[i] = p[i];

		//10���� ǥ��
		unsigned int deci = 0; int t = 1;
		int check_overflow = length;
		if (length > 32) check_overflow = 31;
		for (int i = 0; i <= check_overflow; i++) {
			if (p[length - i] == '1')
				deci += t;
			t *= 2;
		}

		delete[] p;
		std::cout << n << ": " << bitstream << std::endl;
		std::cout << deci << std::endl;
	}
	return 0;
}