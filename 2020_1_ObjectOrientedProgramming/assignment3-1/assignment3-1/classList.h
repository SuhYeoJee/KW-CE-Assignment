#pragma once

// 메뉴의 정보(이름, 가격)를 저장하는 노드
class MenuNode{
public:
	char m_name[30];
	int price;
	MenuNode* nextMNode;
};

// 카테고리의 정보(이름, 메뉴의 개수)를 저장하는 노드
class CategoryNode{
public:
	char c_name[20];
	int m_count = 0;
	CategoryNode* nextCNode;
	MenuNode* Menu;
};

// 단일 연결 리스트
class List {
private:
	int c_count; // 카테고리의 개수
	CategoryNode* head = new CategoryNode;

public:
	List();
	~List();

	// 메뉴를 추가하는 함수
	int add(char* cate, char* menu, int price);
	int add(void);
	int add(char* str);

	// c_index번째 카테고리 노드의 주소를 반환
	CategoryNode* getCNode(int c_index);
	// (c_index번째 카테고리 노드의) m_index번째 메뉴 노드의 주소를 반환
	MenuNode* getMNode(int c_index, int m_index);

	// 카테고리의 개수 반환
	int c_size(void) { return c_count; }
	// 카테고리의 개수를 i만큼 증가
	void setc_size(int i) { c_count += i; }

	// 카테고리 이름으로 카테고리 노드의 순서를 찾아 반환
	int find(char* cate);
	// 메뉴 이름으로 (c_index번째 카테고리 노드의) 메뉴 노드의 순서를 찾아 반환
	int find(int c_index, char* menu);

	// c_index번째 카테고리 삭제
	void remove(int c_index);
	// (c_index번째 카테고리 노드의) m_index번째 메뉴 삭제
	void remove(int c_index, int m_index);
	// 메뉴 이름으로 해당 메뉴 삭제
	int deleteMenu(char* menu);

	// 리스트 전체 출력
	void printList(void);
	// c_index번째 카테고리 출력
	int printList(int c_index);
	// 메뉴 이름으로 메뉴와 가격 출력
	int printMenu(char* menu);
};
