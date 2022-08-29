#include <iostream>

int main(void) {
	char* str = new char[50];
	std::cout << "Enter the string: ";
	std::cin.getline(str, 50);

	int length = 0;
	while (str[++length]);

	//역순 저장
	char* p = new char[length + 1];
	for (int i = 0; i < length; i++)
		p[i] = str[length - 1 - i];
	p[length] = 0;

	//대소문자 반전
	for (int i = 0; i < length; i++) {
		if ((p[i] <= 'z') && (p[i] >= 'a'))
			p[i] -= 32;
		else if ((p[i] <= 'Z') && (p[i] >= 'A'))
			p[i] += 32;
	}

	std::cout << "Result: " << p;
	return 0;
}