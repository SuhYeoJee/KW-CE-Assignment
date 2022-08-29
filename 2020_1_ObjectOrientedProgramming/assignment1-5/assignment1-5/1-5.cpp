#include <iostream>
#include <cstdlib>
#include <ctime>

int repetition_check(int rand_num, int** origin_matrix, int row, int column) {
	
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			if (origin_matrix[i][j] == rand_num) {
				if ((i == row - 1) && (j == column - 1))
					return 0;
				return 1;
			}
		}
	}
	return 0;
}

int main(void) {

	int row, column;
	std::cout << "Enter the row: ";
	std::cin >> row;
	std::cout << "Enter the column: ";
	std::cin >> column;

	if ((row < 1) || (row > 100) || (column < 1) || (column > 100)) {
		std::cout << "unsuitable input" << std::endl;
		return -1;
	}

	//2차원 배열 동적할당
	int** origin_matrix = new int* [row];
	for (int i = 0; i < row; i++) origin_matrix[i] = new int[column];

	srand((unsigned int)time(NULL));
	int rand_num;

	//난수생성
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			rand_num = rand() % (row * column);
			if (repetition_check(rand_num, origin_matrix, row, column)) j--;
			else origin_matrix[i][j] = rand_num;
		}
	}

	//행렬 출력
	std::cout << std::endl << "Origin Matrix >>>" << std::endl;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			std::cout.width(5);
			std::cout << std::left << origin_matrix[i][j] << ' ';
		}
		std::cout << std::endl;
	}

	//전치행렬 출력
	std::cout << std::endl << "Transpose Matrix >>>" << std::endl;
	for (int i = 0; i < column; i++) {
		for (int j = 0; j < row; j++) {
			std::cout.width(5);
			std::cout << std::left << origin_matrix[j][i] << ' ';
		}
		std::cout << std::endl;
	}

	for (int i = 0; i < row; i++) delete[] origin_matrix[i];
	delete[] origin_matrix;

	return 0;
}