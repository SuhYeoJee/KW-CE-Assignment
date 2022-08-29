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

		//bitstream 역순 저장
		char* p = new char[length + 2];
		for (int i = 0; i < length; i++) {
			p[i] = bitstream[length - 1 - i];
			//예외처리
			if ((p[i] != '0') && (p[i] != '1')) {
				std::cout << "bitstream is unsuitable" << std::endl;
				return -1;
			}
		}

		delete[] bitstream;

		//비트 뒤집기
		for (int i = 0; i < length; i++) {
			if (p[i] == '0') p[i] = '1';
			else p[i] = '0';
		}
		//마지막 비트 더하기
		if (n % 2) p[length] = '1';
		else p[length] = '0';
		p[length + 1] = 0; //문자열의 끝

		bitstream = new char[length + 2];
		for (int i = 0; i < length + 2; i++)
			bitstream[i] = p[i];

		//10진수 표현
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