#include <iostream>
using namespace std;
int main(void)
{
	int two_d_array[2][3] = { 1,2,3,4,5,6 };
	int* a, * b, * c, * d, * e, * f, (*g)[3], ** h, ** i, ** j;

	// 포인터변수 초기화
	a = &two_d_array[0][0];
	b = &two_d_array[1][0];
	c = &two_d_array[0][1];
	d = &two_d_array[0][2];
	h = &a; i = &a; j = &c;

	e = two_d_array[0];
	f = two_d_array[1];
	g = two_d_array;

	// 포인터가 가르키는 정수 출력
	cout << "First Condition" << endl;
	cout << "a: " << *a << endl;
	cout << "b: " << *b << endl;
	cout << "c: " << *c << endl;
	cout << "d: " << *d << endl;
	cout << "h: " << **h << endl;
	cout << "i: " << **i << endl;
	cout << "j: " << **j << endl;

	// 포인터를 이용하여 1~6의 주소 값 출력
	cout << endl << "Second Condition" << endl;
	cout << "1-a: " << a << endl;
	cout << "1-h: " << *h << endl;
	cout << "1-i: " << *i << endl;
	cout << "2-c: " << c << endl;
	cout << "2-j: " << *j << endl;
	cout << "3-d: " << d << endl;
	cout << "4-b: " << b << endl;
	cout << "5-b: " << b + 1 << endl;
	cout << "6-b: " << b + 2 << endl;

	// e,f,g에 저장된 주소 값 출력
	cout << endl << "Third Condition" << endl;
	cout << "e: " << e << endl;
	cout << "f: " << f << endl;
	cout << "g: " << g << endl;

	return 0;
}