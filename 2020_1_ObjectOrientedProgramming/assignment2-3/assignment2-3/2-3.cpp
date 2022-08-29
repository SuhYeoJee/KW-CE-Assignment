#include <iostream>
using namespace std;

int main(void)
{
	int row, column;
	cout << "Please input 2D array size: ";
	cin >> row >> column;

	//[오류] 입력이 1~10 이 아닌 경우
	if ((row < 1) || (row > 10)) {
		cout << "unsuitable row" << endl;
		return -1;
	}
	else if ((column < 1) || (column > 10)) {
		cout << "unsuitable column" << endl;
		return -1;
	}

	// 2차원 배열 동적 할당
	int** arr = new int* [row];
	for (int i = 0; i < row; i++)
		arr[i] = new int[column];

	// 숫자 채우기
	int num = 1;
	int x = 0, y = -1, direction = 1;
	int r = row, c = column + 1;
	while (1) {
		if (--c == 0) break; // 반복횟수 1씩 감소
		for (int i = 0; i < c; i++) // 가로 이동
			arr[x][y += direction] = num++;

		if (--r == 0) break; // 반복횟수 1씩 감소
		for (int i = 0; i < r; i++) // 세로 이동
			arr[x += direction][y] = num++;

		direction *= -1; //방향 전환
	}

	// arr 출력
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			cout.width(4);
			cout << arr[i][j] << ' ';
		}
		cout << endl;
	}


	//동적할당 해제
	for (int i = 0; i < row; i++)
		delete[] arr[i];
	delete[] arr;

	return 0;
}