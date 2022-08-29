#include <iostream>

struct dot {
	int x;
	int y;
};

int main(void) {
	struct dot p1, p2, p3;
	struct dot* ptr;

	ptr = &p1;
	std::cout << "P1: ";
	std::cin >> p1.x >> p1.y;

	ptr = &p2;
	std::cout << "P2: ";
	std::cin >> p2.x >> p2.y;

	ptr = &p3;
	std::cout << "P3: ";
	std::cin >> p3.x >> p3.y;

	//p1->p2, p1->p3 벡터 구하기
	struct dot v12, v13;
	v12.x = p2.x - p1.x; v12.y = p2.y - p1.y;
	v13.x = p3.x - p1.x; v13.y = p3.y - p1.y;

	//벡터의 외적 계산
	int z;
	z = (v12.x * v13.y) - (v13.x * v12.y);


	if (!z)
		std::cout << "Straight";
	else
		std::cout << ((z > 0) ? "Counter-Clockwise" : "Clockwise");

	return 0;
}