#pragma once

class OthelloStone {
private:
	char m_pColor;
public:
	OthelloStone();
	OthelloStone(int player);
	~OthelloStone();

	void SetColor(int player); // 돌의 색을 지정
	char GetColor(void); // 돌의 색을 반환
};
