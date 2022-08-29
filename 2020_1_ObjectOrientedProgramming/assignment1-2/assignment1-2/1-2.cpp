#include <iostream>

int main(void) {
	int n;
	std::cout << "Enter the n: ";
	std::cin >> n;

	if (n < 2) {
		std::cout << "unsuitable input";
		return -1;
	}

	//배열 동적할당
	int* list = new int[n - 1];
	for (int i = 2; i <= n; i++) list[i - 2] = i;

	//소수판별
	int p = 2;
	do {
		for (int i = 2; i <= n; i++) {
			if (list[i - 2] == p) continue;
			if (list[i - 2] % p == 0)
				list[i - 2] = 0;
		}
		for (int i = 2; i <= n; i++) {
			if (list[i - 2] > p) {
				p = list[i - 2];
				break;
			}
		}
	} while (p * p <= n);

	//결과출력
	int count = 0;
	for (int i = 2; i <= n; i++) {
		if (list[i - 2]) {
			std::cout << list[i - 2] << ' ';
			count++;
		}
	}
	std::cout << std::endl << "The number of Prime numbers: " << count << std::endl;
	return 0;
}