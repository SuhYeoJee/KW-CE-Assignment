#pragma once

class OthelloStone {
private:
	char m_pColor;
public:
	OthelloStone();
	OthelloStone(int player);
	~OthelloStone();

	void SetColor(int player); // ���� ���� ����
	char GetColor(void); // ���� ���� ��ȯ
};
