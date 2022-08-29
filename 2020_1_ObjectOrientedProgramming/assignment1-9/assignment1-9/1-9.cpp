#include <iostream>

int main(void) {
	char type;
	std::cout << "Which type: ";
	std::cin >> type;

	int text;
	std::cout << "Text: ";
	std::cin >> text;

	int call;
	std::cout << "CALL: ";
	std::cin >> call;

	//요금제 별 수치 대입
	int monthly_fee, free_text, free_call;
	int extra_text_charges, extra_call_charges;
	switch (type) {
	case('A'):
		monthly_fee = 10000;
		free_text = 100;
		free_call = 60;
		extra_text_charges = 20;
		extra_call_charges = 180;
		break;
	case('B'):
		monthly_fee = 15000;
		free_text = 150;
		free_call = 90;
		extra_text_charges = 15;
		extra_call_charges = 150;
		break;
	case('C'):
		monthly_fee = 20000;
		free_text = 200;
		free_call = 120;
		extra_text_charges = 10;
		extra_call_charges = 60;
		break;
	case('D'):
		monthly_fee = 25000;
		free_text = 250;
		free_call = 150;
		extra_text_charges = 5;
		extra_call_charges = 30;
		break;
	default:
		std::cout << "unsuitable input";
		return -1;
	}

	//요금 계산
	text -= free_text;
	call -= free_call;

	if (text < 0) text = 0;
	if (call < 0) call = 0;

	int result_text = text * extra_text_charges;
	int result_call = call * extra_call_charges;
	int result_total = monthly_fee + result_text + result_call;

	//결과출력
	std::cout << "=========" << std::endl << "Result" << std::endl;
	std::cout << "Extra text: " << result_text << std::endl;
	std::cout << "Extra call: " << result_call << std::endl;
	std::cout << "Total: " << result_total << std::endl;

	return 0;
}