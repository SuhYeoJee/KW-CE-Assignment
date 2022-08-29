#include <iostream>
using namespace std;

class ThreeSixNine
{
public:
	int find369(int i);
	void print_i(int i, int exmark);
	void print369(int _num);
};


int ThreeSixNine::find369(int i) // i의 ! 개수를 찾음
{
	int find = 0; //비교할 자리
	int exmark = 0; //느낌표의 개수

	// 일의자리, 십의자리, 백의자리 순서로 비교
	for (int n = i; n > 0; n /= 10) {
		find = (n) % 10;
		if ((find == 3) || (find == 6) || (find == 9))
			exmark++; //369가 있는 경우 느낌표의 개수 +1
	}
	return exmark;
}

void ThreeSixNine::print_i(int i, int exmark) // i의 결과 출력
{
	//i의 결과 출력
	if (exmark) { //느낌표의 개수만큼 실행
		for (int j = 0; j < exmark; j++)
			cout << '!';
	}
	else { cout << i; } //느낌표가 하나도 없는 경우 숫자 출력
}

void ThreeSixNine::print369(const int num)
{
	//369결과를 출력함
	for (int i = 1; i <= num; i++) {
		int exmark = find369(i);
		print_i(i, exmark);

		cout << '\t';
		if (!(i % 10)) cout << endl; //줄바꿈
	}
}

int main(void)
{
	int num;
	ThreeSixNine game;

	cout << "input your number" << endl;
	cin >> num;

	if ((num < 1) || (num > 300)) {
		cout << "1~300 범위 밖의 수 입니다." << endl;
		return -1;
	} //[예외] num의 값이 범위밖인 경우

	game.print369(num);
	cout << endl;

	return 0;
}