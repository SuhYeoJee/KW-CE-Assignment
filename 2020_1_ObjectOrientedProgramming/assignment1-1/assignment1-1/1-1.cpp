#include <iostream>

void hole(int N, int i, char** arr) {
	//��ĭ�� ũ�⸦ ����
	int hole_size = N, a = i;
	while (a--) hole_size /= 3;

	//��ĭ ������ �ݺ��� Ƚ���� ����
	int repeat = 1; a = i;
	while (--a) repeat *= 9;

	//��ĭ ����
	int x = hole_size, y = hole_size;
	do {
		for (int j = 0; j < hole_size; j++) {
			for (int k = 0; k < hole_size; k++)
				arr[y + j][x + k] = ' ';
		}
		//���� ��ĭ�� ������ ��ġ�� �̵�
		if ((x += hole_size * 3) > (N - hole_size)) {
			x = hole_size;
			y += hole_size * 3;
		}
	} while (--repeat);
	return;
}

int main(void) {
	float N;
	std::cout << "Enter the power of 3: ";
	std::cin >> N;

	//���� ã��, ����ó��
	int power = 1;
	float n = N;
	while (!((n /= 3) == 1)) {
		power++;
		int a = n;
		if (!(n - a == 0)||(n==0)) {
			std::cout << N << " is an unsuitable number." << std::endl;
			return -1;
		}
	}

	//2���� �迭 �����Ҵ�
	char** arr = new char* [N];
	for (int i = 0; i < N; i++) arr[i] = new char[N];

	//��� ĭ�� ��ȣ ä���
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			arr[i][j] = '$';
	}

	//��ĭ ����
	for (int i = 1; i <= power; i++) hole(N, i, arr);

	//�迭 ���
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			std::cout << arr[i][j];
		std::cout << std::endl;
	}

	//�迭 ����
	for (int i = 0; i < N; i++) delete[] arr[i];
	delete[] arr;

	return 0;
}