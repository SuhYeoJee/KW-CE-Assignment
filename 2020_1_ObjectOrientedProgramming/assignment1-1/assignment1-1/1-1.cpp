#include <iostream>

void hole(int N, int i, char** arr) {
	//빈칸의 크기를 구함
	int hole_size = N, a = i;
	while (a--) hole_size /= 3;

	//빈칸 삽입을 반복할 횟수를 구함
	int repeat = 1; a = i;
	while (--a) repeat *= 9;

	//빈칸 삽입
	int x = hole_size, y = hole_size;
	do {
		for (int j = 0; j < hole_size; j++) {
			for (int k = 0; k < hole_size; k++)
				arr[y + j][x + k] = ' ';
		}
		//다음 빈칸을 삽입할 위치로 이동
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

	//지수 찾기, 예외처리
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

	//2차원 배열 동적할당
	char** arr = new char* [N];
	for (int i = 0; i < N; i++) arr[i] = new char[N];

	//모든 칸에 기호 채우기
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			arr[i][j] = '$';
	}

	//빈칸 삽입
	for (int i = 1; i <= power; i++) hole(N, i, arr);

	//배열 출력
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			std::cout << arr[i][j];
		std::cout << std::endl;
	}

	//배열 해제
	for (int i = 0; i < N; i++) delete[] arr[i];
	delete[] arr;

	return 0;
}