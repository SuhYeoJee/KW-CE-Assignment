#include <iostream>
#include "Block.h"

MyBlock::MyBlock() {
	m_number = 0;
	m_x = 0; m_y = 0;
	m_pUp = nullptr;
	m_pDown = nullptr;
	m_pLeft = nullptr;
	m_pRight = nullptr;
}

MyBlock::~MyBlock() {
}

// private 영역 반환
int MyBlock::GetNum(void) { return m_number; }
MyBlock* MyBlock::GetUp(void) { return m_pUp; }
MyBlock* MyBlock::GetDown(void) { return m_pDown; }
MyBlock* MyBlock::GetLeft(void) { return m_pLeft; }
MyBlock* MyBlock::GetRight(void) { return m_pRight; }

// private 영역 수정
void MyBlock::SetNum(int num) { m_number = num; return; }
void MyBlock::SetX(int x) { m_x = x; return; }
void MyBlock::SetY(int y) { m_y = y; return; }
void MyBlock::SetUp(MyBlock* temp) { m_pUp = temp; return; }
void MyBlock::SetDown(MyBlock* temp) { m_pDown = temp; return; }
void MyBlock::SetLeft(MyBlock* temp) { m_pLeft = temp; return; }
void MyBlock::SetRight(MyBlock* temp) { m_pRight = temp; return; }