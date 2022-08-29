#include <iostream>
using namespace std;

class ThreeSixNine
{
public:
	int find369(int i);
	void print_i(int i, int exmark);
	void print369(int _num);
};


int ThreeSixNine::find369(int i) // i�� ! ������ ã��
{
	int find = 0; //���� �ڸ�
	int exmark = 0; //����ǥ�� ����

	// �����ڸ�, �����ڸ�, �����ڸ� ������ ��
	for (int n = i; n > 0; n /= 10) {
		find = (n) % 10;
		if ((find == 3) || (find == 6) || (find == 9))
			exmark++; //369�� �ִ� ��� ����ǥ�� ���� +1
	}
	return exmark;
}

void ThreeSixNine::print_i(int i, int exmark) // i�� ��� ���
{
	//i�� ��� ���
	if (exmark) { //����ǥ�� ������ŭ ����
		for (int j = 0; j < exmark; j++)
			cout << '!';
	}
	else { cout << i; } //����ǥ�� �ϳ��� ���� ��� ���� ���
}

void ThreeSixNine::print369(const int num)
{
	//369����� �����
	for (int i = 1; i <= num; i++) {
		int exmark = find369(i);
		print_i(i, exmark);

		cout << '\t';
		if (!(i % 10)) cout << endl; //�ٹٲ�
	}
}

int main(void)
{
	int num;
	ThreeSixNine game;

	cout << "input your number" << endl;
	cin >> num;

	if ((num < 1) || (num > 300)) {
		cout << "1~300 ���� ���� �� �Դϴ�." << endl;
		return -1;
	} //[����] num�� ���� �������� ���

	game.print369(num);
	cout << endl;

	return 0;
}