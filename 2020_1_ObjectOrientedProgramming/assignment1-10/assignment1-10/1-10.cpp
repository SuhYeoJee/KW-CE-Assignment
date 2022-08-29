#include <iostream>
#include <cstdlib>
#include <ctime>

int main(void) {
	int num;
	std::cout << "Random numbers : " << std::endl;

	//�����߻�
	srand((unsigned int)time(NULL));
	int random_numbers[4];
	for (int i = 0; i < 4; i++) {
		random_numbers[i] = rand() % 10;
		int j = i;
		while (j--) {
			if (random_numbers[i] == random_numbers[j]) {
				i--; break;
			}
		}
	}

	int hit = 0, blow, t = 0;
	while (hit != 4) {
		hit = 0, blow = 0;

		std::cout << "Your number: ";
		std::cin >> num;
		if (num > 9877) {
			std::cout << "unsuitable input" << std::endl;
			return -1;
		}

		//�Է¹��� ���� �迭�� ����
		int your_numbers[4];
		your_numbers[0] = num / 1000; num %= 1000;
		your_numbers[1] = num / 100; num %= 100;
		your_numbers[2] = num / 10; num %= 10;
		your_numbers[3] = num;

		for (int i = 0; i < 4; i++) {
			int j = i;
			while (j--) {
				if (your_numbers[i] == your_numbers[j]) {
					std::cout << "unsuitable input" << std::endl;
					return -1;
				}
			}
		}

		//������ �Է¹��� �� ��
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (your_numbers[i] == random_numbers[j]) {
					if (i == j) {
						hit++; break;
					}
					else {
						blow++; break;
					}
				}
			}
		}
		//������
		std::cout << ">>HIT: " << hit << ", BLOW: " << blow << std::endl;
		if ((++t) == 10) break;
	}
	//������
	if (hit == 4) std::cout << "Win" << std::endl;
	else std::cout << "Lose" << std::endl;
	return 0;
}