#pragma once

class MyBlock {
private:
	int m_number, m_x, m_y;
	MyBlock* m_pUp;
	MyBlock* m_pDown;;
	MyBlock* m_pLeft;
	MyBlock* m_pRight;

public:
	MyBlock();
	~MyBlock();

	// private 영역 반환
	int GetNum(void);
	MyBlock* GetUp(void);
	MyBlock* GetDown(void);
	MyBlock* GetLeft(void);
	MyBlock* GetRight(void);

	// private 영역 수정
	void SetNum(int num);
	void SetX(int x);
	void SetY(int y);
	void SetUp(MyBlock* temp);
	void SetDown(MyBlock* temp);
	void SetLeft(MyBlock* temp);
	void SetRight(MyBlock* temp);

};