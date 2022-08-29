#include <iostream>
#include "Stone.h"
#include "Board.h"

using namespace std;

OthelloBoard::OthelloBoard() {
	OthelloStone* m_pStone = nullptr;
	OthelloBoard* m_pHead = nullptr;
	OthelloBoard* m_pUp = nullptr;
	OthelloBoard* m_pDown = nullptr;
	OthelloBoard* m_pLeft = nullptr;
	OthelloBoard* m_pRight = nullptr;
}

OthelloBoard::~OthelloBoard() {
	// 칸에 돌이 있다면 메모리 해제
	if (this->m_pStone)
		delete this->m_pStone;
}

// x,y 칸으로 포인터 이동
OthelloBoard* OthelloBoard::gotoxy(int x, int y) {
	OthelloBoard* temp = m_pHead;
	for (int i = 1; i < x; i++) temp = temp->m_pRight;
	for (int i = 1; i < y; i++) temp = temp->m_pUp;
	return temp;
}

//보드 생성, 초기 돌 놓기
void OthelloBoard::SetBoard(void) {
	// 보드 생성
	m_pHead = this;
	OthelloBoard* rl_temp = m_pHead;
	OthelloBoard* ud_temp = m_pHead;
	OthelloBoard* add = nullptr;

	for (int i = 1; i < 9; i++) {
		for (int j = 2; j < 9; j++) {
			// 오른쪽 칸 생성
			add = new OthelloBoard;
			add->m_pHead = this; // 헤드 저장
			rl_temp->m_pRight = add; //좌우 연결
			add->m_pLeft = rl_temp;
			if (i > 1) {
				ud_temp->m_pUp = add;// 위아래 연결
				add->m_pDown = ud_temp;
				if (ud_temp->m_pRight) ud_temp = ud_temp->m_pRight;
			}
			rl_temp = add;
		}
		if (i == 8) break; // 전체 리스트 생성 종료

		// rl_temp 위치 초기화
		while (rl_temp->m_pLeft)
			rl_temp = rl_temp->m_pLeft;

		// ud_temp 위치 초기화
		while (ud_temp->m_pLeft)
			ud_temp = ud_temp->m_pLeft;
		if (ud_temp->m_pUp) { ud_temp = ud_temp->m_pUp; }

		// 윗줄 생성
		add = new OthelloBoard;
		add->m_pHead = this;
		ud_temp->m_pUp = add; add->m_pDown = ud_temp;
		rl_temp = add;
		ud_temp = ud_temp->m_pRight;
	}

	// 초기 돌 놓기
	SetStone(1, 4, 4);
	SetStone(1, 5, 5);
	SetStone(2, 4, 5);
	SetStone(2, 5, 4);

	return;
}

// 보드 출력
void OthelloBoard::PrintBoard(void) {
	OthelloBoard* temp = gotoxy(1, 8);
	wchar_t ch; // 특수문자 출력 wcout, wchar_t
	// 출력 순서 (1,8) -> (8,8) -> (1,7) -> (8,7) ->
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++) {
			if (temp->m_pStone) // 돌이 놓인 경우
				ch = (temp->m_pStone->GetColor() == 'b') ? L'●' : L'○';
			else
				ch = L'□'; // 칸이 빈 경우
			wcout << ch;
			if (temp->m_pRight) temp = temp->m_pRight;
		}
		cout << endl;
		while (temp->m_pLeft) temp = temp->m_pLeft;
		if (temp->m_pDown) temp = temp->m_pDown;
	}
	return;
}


//새 돌 놓기
//[return: 조건 불만족(false), 정상종료(true)]
bool OthelloBoard::NewStone(int player, int x, int y) {

	// 조건성립 여부
	if (!IsPossible(player, x, y)) { //[오류] 조건 불만족
		cout << "Wrong position!" << endl;
		return false; 
	}
	OthelloBoard* add = gotoxy(x, y);// 새 돌을 놓을 자리로 이동
	SetStone(player, x, y);// 새 돌 놓기
	Turn(player, add);// 상대 돌 뒤집기
	return true;
}
// 돌을 놓을 수 있는지 판단
// [return: 불가능(false), 가능(true)]
bool OthelloBoard::IsPossible(int player, int x, int y) {

	// [오류] 게임판의 범위 밖의 좌표
	if ((x < 1) || (x > 8)) return false;
	if ((y < 1) || (y > 8)) return false;

	OthelloBoard* add = gotoxy(x, y);// 새 돌을 놓을 자리로 이동

	if (add->m_pStone) return false;// [오류] 이미 돌이 있는 경우

	// 각 방향으로 뒤집을 수 있는지 확인
	if (IsPossible_R(player, add)) return true;
	if (IsPossible_L(player, add)) return true;
	if (IsPossible_U(player, add)) return true;
	if (IsPossible_D(player, add)) return true;
	if (IsPossible_UR(player, add)) return true;
	if (IsPossible_UL(player, add)) return true;
	if (IsPossible_DR(player, add)) return true;
	if (IsPossible_DL(player, add)) return true;
	return false;
}
// OthelloStone 생성
void OthelloBoard::SetStone(int player, int x, int y) {
	// 새 돌을 놓을 자리
	OthelloBoard* add = gotoxy(x, y);

	// (x,y)에 새 돌 생성
	OthelloStone* n_stone = new OthelloStone;
	n_stone->SetColor(player);
	add->m_pStone = n_stone;
}
// 상대의 돌을 뒤집어놓음
void OthelloBoard::Turn(int player, OthelloBoard* temp) {
	// 각 방향으로 상대 돌 뒤집기
	if (IsPossible_R(player, temp)) { Turn_R(temp); }
	if (IsPossible_L(player, temp)) { Turn_L(temp); }
	if (IsPossible_U(player, temp)) { Turn_U(temp); }
	if (IsPossible_D(player, temp)) { Turn_D(temp); }
	if (IsPossible_UR(player, temp)) { Turn_UR(temp); }
	if (IsPossible_UL(player, temp)) { Turn_UL(temp); }
	if (IsPossible_DR(player, temp)) { Turn_DR(temp); }
	if (IsPossible_DL(player, temp)) { Turn_DL(temp); }
	return;
}


// 종료조건 확인
// [return: 종료되지 않음(0), p1승리(1), p2승리(2), 비김(3)]
int OthelloBoard::IsEnd(int end) {
	// end ==1 무조건 종료
	OthelloBoard* temp = m_pHead;
	int b = 0, w = 0;
	char color;
	// 흑돌과 백돌의 수 계산
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (!temp->m_pStone) {
				if (temp->m_pRight) temp = temp->m_pRight;
				continue; // 칸에 돌이 없는 경우
			}
			color = temp->m_pStone->GetColor();
			if (color == 'b') b++;
			else if (color == 'w') w++;
			if (temp->m_pRight) temp = temp->m_pRight;
		}
		if (temp->m_pUp) temp = temp->m_pUp;
		while (temp->m_pLeft)
			temp = temp->m_pLeft;
	}

	if (b + w == 64) { // 판이 가득 찬 경우
		if (b == w) return 3;
		else if (b > w) return 1;
		else return 2;
	}
	else { // 한 가지 색으로 통일된 경우
		if ((b == 0) || (w == 0))
			return (b > w) ? 1 : 2;
		else if (end) { //무조건 종료하는 경우
			if (b == w) return 3;
			return (b > w) ? 1 : 2;
		}
	}
	//종료가 아닌 경우
	return 0;
}

// 차례를 건너 뛰는지 확인(놓을 자리 없음)
// [return: 건너 뜀(true), 건너뛰지 않음(false}]
bool OthelloBoard::IsSkip(int player) {
	for (int y = 1; y < 9; y++) {
		for (int x = 1; x < 9; x++) {
			if (IsPossible(player, x, y)) return false;
		}
	}
	return true;
}

// 게임이 끝났을 때 리스트 해제
void OthelloBoard::DeleteBoard(void) {
	OthelloBoard* del = m_pHead;
	del->gotoxy(8, 8);
	OthelloBoard* temp = del;

	// 삭제방향 (8,8) -> (1,8) -> (8,7) -> (1,7) ->
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			temp = (del->m_pLeft) ? del->m_pLeft : del->m_pDown;
			if (del == m_pHead) break;
			delete del;
			del = temp;
		}
		if (temp == nullptr) break;
		while (temp->m_pRight) temp = temp->m_pRight;
		del = temp;
	}
}


// 방향에 따른 판단 함수
bool OthelloBoard::IsPossible_R(int player, OthelloBoard * add) {
	OthelloBoard* temp = add;
	char color = (player == 1) ? 'b' : 'w'; // 놓으려는 돌의 색

	// 이웃한 칸이 빈칸
	temp = temp->m_pRight;
	if (!temp)return false;
	if (!temp->m_pStone) return false;

	// 이웃한 칸에 자신의 돌
	if (temp->m_pStone->GetColor() == color) return false;

	//이웃한 칸에 상대의 돌
	temp = add;
	while (temp->m_pRight->m_pStone) { // 돌이 없을 때까지
		temp = temp->m_pRight;
		if (temp->m_pStone->GetColor() == color )
			return true; // 자신의 돌을 찾음
		if (!temp->m_pRight) break; // 오른쪽에 칸이 없음
	}
	return false;
}
bool OthelloBoard::IsPossible_L(int player, OthelloBoard* add) {
	OthelloBoard* temp = add;
	char color = (player == 1) ? 'b' : 'w'; // 놓으려는 돌의 색

	// 이웃한 칸이 빈칸
	temp = temp->m_pLeft;
	if (!temp)return false;
	if (!temp->m_pStone) return false;

	// 이웃한 칸에 자신의 돌
	
	if (temp->m_pStone->GetColor() == color) return false;

	//이웃한 칸에 상대의 돌
	temp = add;
	while (temp->m_pLeft->m_pStone) { // 돌이 없을 때까지
		temp = temp->m_pLeft;
		if (temp->m_pStone->GetColor() == color)
			return true; // 자신의 돌을 찾음
		if (!temp->m_pLeft) break; // 왼쪽에 칸이 없음
	}
	return false;
}
bool OthelloBoard::IsPossible_U(int player, OthelloBoard* add) {
	OthelloBoard* temp = add;
	char color = (player == 1) ? 'b' : 'w'; // 놓으려는 돌의 색

	// 이웃한 칸이 빈칸
	temp = temp->m_pUp;
	if (!temp)return false;
	if (!temp->m_pStone) return false;

	// 이웃한 칸에 자신의 돌
	if (temp->m_pStone->GetColor() == color) return false;

	//이웃한 칸에 상대의 돌
	temp = add;
	while (temp->m_pUp->m_pStone) { // 돌이 없을 때까지
		temp = temp->m_pUp;
		if (temp->m_pStone->GetColor() == color)
			return true; // 자신의 돌을 찾음
		if (!temp->m_pUp) break; // 위에 칸이 없음
	}
	return false;
}
bool OthelloBoard::IsPossible_D(int player, OthelloBoard* add) {
	OthelloBoard* temp = add;
	char color = (player == 1) ? 'b' : 'w'; // 놓으려는 돌의 색

	// 이웃한 칸이 빈칸
	temp = temp->m_pDown;
	if (!temp)return false;
	if (!temp->m_pStone) return false;

	// 이웃한 칸에 자신의 돌
	if (temp->m_pStone->GetColor() == color) return false;

	//이웃한 칸에 상대의 돌
	temp = add;
	while (temp->m_pDown->m_pStone) { // 돌이 없을 때까지
		temp = temp->m_pDown;
		if (temp->m_pStone->GetColor() == color)
			return true; // 자신의 돌을 찾음
		if (!temp->m_pDown) break; // 아래에 칸이 없음
	}
	return false;
}
bool OthelloBoard::IsPossible_UR(int player, OthelloBoard* add) {
	OthelloBoard* temp = add;
	char color = (player == 1) ? 'b' : 'w'; // 놓으려는 돌의 색

	// 이웃한 칸이 빈칸
	if (!temp->m_pUp) return false;
	temp = temp->m_pUp->m_pRight;
	if (!temp)return false;
	if (!temp->m_pStone) return false;

	// 이웃한 칸에 자신의 돌
	if (temp->m_pStone->GetColor() == color) return false;

	//이웃한 칸에 상대의 돌
	temp = add;
	while (temp->m_pUp->m_pRight->m_pStone) { // 돌이 없을 때까지
		temp = temp->m_pUp->m_pRight;
		if (temp->m_pStone->GetColor() == color)
			return true; // 자신의 돌을 찾음
		if (!temp->m_pUp) break; // 위에 칸이 없음
		if (!temp->m_pUp->m_pRight) break; // 위오른쪽에 칸이 없음
	}
	return false;
}
bool OthelloBoard::IsPossible_UL(int player, OthelloBoard* add) {
	OthelloBoard* temp = add;
	char color = (player == 1) ? 'b' : 'w'; // 놓으려는 돌의 색

	// 이웃한 칸이 빈칸
	if (!temp->m_pUp) return false;
	temp = temp->m_pUp->m_pLeft;
	if (!temp)return false;
	if (!temp->m_pStone) return false;

	// 이웃한 칸에 자신의 돌
	if (temp->m_pStone->GetColor() == color) return false;

	//이웃한 칸에 상대의 돌
	temp = add;
	while (temp->m_pUp->m_pLeft->m_pStone) { // 돌이 없을 때까지
		temp = temp->m_pUp->m_pLeft;
		if (temp->m_pStone->GetColor() == color)
			return true; // 자신의 돌을 찾음
		if (!temp->m_pUp) break; // 위에 칸이 없음
		if (!temp->m_pUp->m_pLeft) break; // 위왼쪽에 칸이 없음
	}
	return false;
}
bool OthelloBoard::IsPossible_DR(int player, OthelloBoard* add) {
	OthelloBoard* temp = add;
	char color = (player == 1) ? 'b' : 'w'; // 놓으려는 돌의 색

	// 이웃한 칸이 빈칸
	if (!temp->m_pDown) return false;
	temp = temp->m_pDown->m_pRight;
	if (!temp)return false;
	if (!temp->m_pStone) return false;

	// 이웃한 칸에 자신의 돌
	if (temp->m_pStone->GetColor() == color) return false;

	//이웃한 칸에 상대의 돌
	temp = add;
	while (temp->m_pDown->m_pRight->m_pStone) { // 돌이 없을 때까지
		temp = temp->m_pDown->m_pRight;
		if (temp->m_pStone->GetColor() == color)
			return true; // 자신의 돌을 찾음
		if (!temp->m_pDown) break; // 아래에 칸이 없음
		if (!temp->m_pDown->m_pRight) break; // 아래오른쪽에 칸이 없음
	}
	return false;
}
bool OthelloBoard::IsPossible_DL(int player, OthelloBoard* add) {
	OthelloBoard* temp = add;
	char color = (player == 1) ? 'b' : 'w'; // 놓으려는 돌의 색

	// 이웃한 칸이 빈칸
	if (!temp->m_pDown) return false;
	temp = temp->m_pDown->m_pLeft;
	if (!temp)return false;
	if (!temp->m_pStone) return false;

	// 이웃한 칸에 자신의 돌
	if (temp->m_pStone->GetColor() == color) return false;

	//이웃한 칸에 상대의 돌
	temp = add;
	while (temp->m_pDown->m_pLeft->m_pStone) { // 돌이 없을 때까지
		temp = temp->m_pDown->m_pLeft;
		if (temp->m_pStone->GetColor() == color)
			return true; // 자신의 돌을 찾음
		if (!temp->m_pDown) break; // 아래에 칸이 없음
		if (!temp->m_pDown->m_pLeft) break; // 아래왼쪽에 칸이 없음
	}
	return false;
}

// 방향에 따른 뒤집기 함수
void OthelloBoard::Turn_R(OthelloBoard* temp) {
	char color = temp->m_pStone->GetColor();

	while (temp->m_pRight->m_pStone) { //돌이 없을 때까지
		temp = temp->m_pRight;
		if (temp->m_pStone->GetColor() == color) return;
		else
			temp->m_pStone->SetColor(color);
	}
}
void OthelloBoard::Turn_L(OthelloBoard* temp) {
	char color = temp->m_pStone->GetColor();

	while (temp->m_pLeft->m_pStone) {
		temp = temp->m_pLeft;
		if (temp->m_pStone->GetColor() == color) return;
		else
			temp->m_pStone->SetColor(color);
	}
}
void OthelloBoard::Turn_U(OthelloBoard* temp) {
	char color = temp->m_pStone->GetColor();

	while (temp->m_pUp->m_pStone) {
		temp = temp->m_pUp;
		if (temp->m_pStone->GetColor() == color) return;
		else
			temp->m_pStone->SetColor(color);
	}
}
void OthelloBoard::Turn_D(OthelloBoard* temp) {
	char color = temp->m_pStone->GetColor();

	while (temp->m_pDown->m_pStone) {
		temp = temp->m_pDown;
		if (temp->m_pStone->GetColor() == color) return;
		else
			temp->m_pStone->SetColor(color);
	}
}
void OthelloBoard::Turn_UR(OthelloBoard* temp) {
	char color = temp->m_pStone->GetColor();

	while (temp->m_pUp->m_pRight->m_pStone) {
		temp = temp->m_pUp->m_pRight;
		if (temp->m_pStone->GetColor() == color) return;
		else
			temp->m_pStone->SetColor(color);
	}
}
void OthelloBoard::Turn_UL(OthelloBoard* temp) {
	char color = temp->m_pStone->GetColor();

	while (temp->m_pUp->m_pLeft->m_pStone) {
		temp = temp->m_pUp->m_pLeft;
		if (temp->m_pStone->GetColor() == color) return;
		else
			temp->m_pStone->SetColor(color);
	}
}
void OthelloBoard::Turn_DR(OthelloBoard* temp) {
	char color = temp->m_pStone->GetColor();

	while (temp->m_pDown->m_pRight->m_pStone) {
		temp = temp->m_pDown->m_pRight;
		if (temp->m_pStone->GetColor() == color) return;
		else
			temp->m_pStone->SetColor(color);
	}
}
void OthelloBoard::Turn_DL(OthelloBoard* temp) {
	char color = temp->m_pStone->GetColor();

	while (temp->m_pDown->m_pLeft->m_pStone) {
		temp = temp->m_pDown->m_pLeft;
		if (temp->m_pStone->GetColor() == color) return;
		else
			temp->m_pStone->SetColor(color);
	}
}
