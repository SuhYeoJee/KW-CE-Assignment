#include <iostream>
#include "Stone.h"
using namespace std;

OthelloStone::OthelloStone() {
	m_pColor = NULL;
}
OthelloStone::OthelloStone(int player) {
	m_pColor = (player == 1) ? 'b' : 'w';
}
OthelloStone::~OthelloStone() {}

void OthelloStone::SetColor(int player) {
	if ((player == 1)||(player == 'b')) m_pColor = 'b';
	else if ((player == 2) || (player == 'w')) m_pColor = 'w';
	return;
}
char OthelloStone::GetColor(void) { return m_pColor; }