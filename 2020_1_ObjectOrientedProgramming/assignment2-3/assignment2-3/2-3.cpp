#include <iostream>
using namespace std;

int main(void)
{
	int row, column;
	cout << "Please input 2D array size: ";
	cin >> row >> column;

	//[����] �Է��� 1~10 �� �ƴ� ���
	if ((row < 1) || (row > 10)) {
		cout << "unsuitable row" << endl;
		return -1;
	}
	else if ((column < 1) || (column > 10)) {
		cout << "unsuitable column" << endl;
		return -1;
	}

	// 2���� �迭 ���� �Ҵ�
	int** arr = new int* [row];
	for (int i = 0; i < row; i++)
		arr[i] = new int[column];

	// ���� ä���
	int num = 1;
	int x = 0, y = -1, direction = 1;
	int r = row, c = column + 1;
	while (1) {
		if (--c == 0) break; // �ݺ�Ƚ�� 1�� ����
		for (int i = 0; i < c; i++) // ���� �̵�
			arr[x][y += direction] = num++;

		if (--r == 0) break; // �ݺ�Ƚ�� 1�� ����
		for (int i = 0; i < r; i++) // ���� �̵�
			arr[x += direction][y] = num++;

		direction *= -1; //���� ��ȯ
	}

	// arr ���
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			cout.width(4);
			cout << arr[i][j] << ' ';
		}
		cout << endl;
	}


	//�����Ҵ� ����
	for (int i = 0; i < row; i++)
		delete[] arr[i];
	delete[] arr;

	return 0;
}