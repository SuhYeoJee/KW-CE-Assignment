#include <iostream>

void print_tictactoe(char** arr) { //게임 판 출력
	std::cout << "   x 0   1   2" << std::endl;
	std::cout << " Y  --- --- ---" << std::endl;
	std::cout << " 0 | " << arr[0][0] << " | " << arr[0][1] << " | " << arr[0][2] << " |" << std::endl;
	std::cout << "    --- --- ---" << std::endl;
	std::cout << " 1 | " << arr[1][0] << " | " << arr[1][1] << " | " << arr[1][2] << " |" << std::endl;
	std::cout << "    --- --- ---" << std::endl;
	std::cout << " 2 | " << arr[2][0] << " | " << arr[2][1] << " | " << arr[2][2] << " |" << std::endl;
	std::cout << "    --- --- ---" << std::endl;
	return;
}

int win(char** arr) { //승리조건
	int winner = 0;
	for (int i = 0; i < 3; i++) {
		if ((arr[i][0] == arr[i][1]) && (arr[i][0] == arr[i][2]) && (arr[i][0] != ' '))
			winner = (arr[i][0] == 'O') ? 1 : 2;
	}
	for (int i = 0; i < 3; i++) {
		if ((arr[0][i] == arr[1][i]) && (arr[0][i] == arr[2][i]) && (arr[0][i] != ' '))
			winner = (arr[i][0] == 'O') ? 1 : 2;
	}
	if ((arr[0][0] == arr[1][1]) && (arr[0][0] == arr[2][2]) && (arr[0][0] != ' ')) {
		winner = (arr[1][1] == 'O') ? 1 : 2;
	}
	if ((arr[2][0] == arr[1][1]) && (arr[2][0] == arr[0][2]) && (arr[2][0] != ' ')) {
		winner = (arr[1][1] == 'O') ? 1 : 2;
	}
	return winner;
}

int main(void) {
	char str[29] = " Enter your location [x,y]: ";
	char** arr = new char* [3];
	for (int i = 0; i < 3; i++) arr[i] = new char[3];

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
			arr[i][j] = ' ';
	}

	print_tictactoe(arr);

	//게임 진행
	int attempt = 0, player = 1, x, y, draw, winner;
	while (attempt++ < 9) {
		std::cout << "[Play " << ((player == 1) ? (player++) : (player--)) << ']' << str;
		std::cin >> x >> y;

		if ((x < 0) || (x > 2) || (y < 0) || (y > 2)) {
			std::cout << x << ' ' << y << " is the unsuitable input." << std::endl;
			return -1;
		}
		else if (arr[y][x] != ' ') {
			std::cout << x << ' ' << y << " is already filled." << std::endl;
			return -1;
		}
		arr[y][x] = ((player == 1) ? 'X' : 'O');
		print_tictactoe(arr);

		draw = 0;
		if ((winner = win(arr))) break;
		draw = 1;
	}

	//결과출력
	if (draw) std::cout << "Draw" << std::endl;
	else std::cout << "Winner is [Player " << winner << ']' << std::endl;

	for (int i = 0; i < 3; i++) delete[] arr[i];
	delete[] arr;

	return 0;
}