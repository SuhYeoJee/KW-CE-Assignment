#include <iostream>
#include <fstream>
#include "classList.h"
using namespace std;

List::List() {
	head->nextCNode = nullptr;
	head->Menu = nullptr;
	c_count = 0;
}

List::~List() {
	for (int i = c_size(); i > 0; i--)
		remove(i);
}

// 분리된 인자로 리스트 추가 
//[return: 중복된 메뉴 (-2),  정상종료 (0)]
int List::add(char* cate, char * menu, int price){

	// 카테고리와 메뉴의 순서를 찾음
	int c_index = find(cate);
	int m_index = find(c_index, menu);

	if (c_index == -1) { // 카테고리가 기존에 없는 경우
		CategoryNode* c_add = new CategoryNode;
		strcpy(c_add->c_name, cate);
		
		if (c_size() == 0) {// 첫 번째 카테고리인 경우
			delete head;
			head = c_add;
		}
		else {
			CategoryNode* temp = head;
			for (int i = 0; i < c_size() -1; i++)
				temp = temp->nextCNode;
			temp->nextCNode = c_add;
		}
		setc_size(1); // 카테고리 수를 1 증가함
		c_add->nextCNode = nullptr;
		
		//새 메뉴노드 생성 (카테고리의 첫 번째 메뉴)
		MenuNode* m_add = new MenuNode;
		strcpy(m_add->m_name, menu);
		m_add->nextMNode = nullptr;
		m_add->price = price;

		c_add->Menu = m_add;
		c_add->m_count++;
	}
	else  { // 카테고리가 있는 경우
		if (m_index != -1) {//[오류] 이미 존재하는 메뉴
			cout << menu << " already exists!" << endl;
			return -2;
		}
		else {
			// 새 메뉴노드 생성
			MenuNode* add = new MenuNode;
			strcpy(add->m_name, menu);
			add->price = price;
			add->nextMNode = nullptr;

			// 메뉴의 순서 m_index 찾기
			CategoryNode* category = getCNode(c_index);
			MenuNode* temp = category->Menu;
			
			for (int i = 0; i < category->m_count; i++) {
				if (temp->price > price) {
					m_index = i;
					break;
				}
				else if (temp->price == price) {
					m_index = i; // 가격이 같은 메뉴 중 가장 앞의 m_index
					int k = 0; // 현재 저장된 메뉴 중 가격이 같은 메뉴의 개수
					MenuNode* sameprice = temp;
					while (temp->price != price) { 
						k++; 
						temp = temp->nextMNode;
					}
					for (k; k > 0; k--) {// 이름순 비교
						if (stricmp(sameprice->m_name,menu)<0) {
							m_index++;
							sameprice = sameprice->nextMNode;
						}
						else break;
					}
					temp = sameprice;
					if (k == 0)
						temp = temp->nextMNode;
				}
				else
					temp = temp->nextMNode;

				if (temp == nullptr) { // 추가하는 메뉴가 가장 마지막 메뉴인 경우
					m_index = i+1;
					break;
				}
			}
			
			// new의 인덱스 = m_index
			// temp는 new의 다음노드

			if (m_index == 0) { // 메뉴의 가장 앞
				MenuNode* next = category->Menu;
				add->nextMNode = next;
				category->Menu = add;
			}
			else { 
				MenuNode* pre = getMNode(c_index, m_index-1);
				if (m_index == category->m_count) // 메뉴의 가장 뒤
					add->nextMNode = nullptr;
				else //중간
					add->nextMNode = temp;
				pre->nextMNode = add;
			}
			category->m_count++;
		}
	}
	return 0;
}

// input.txt파일의 내용에서 추가 
//[return: 파일 없음(-1), 정상종료 (0)]
int List::add(void) {
	// .cpp파일과 input.txt가 같은 경로에 있어야 한다.
	ifstream fin("input.txt");
	if (!fin.is_open()) // [오류] 파일이 없는 경우
		return -1;

	while (!fin.eof()) {
		char str[60], m_name[30], c_name[20], c_price[10];
		int price, err = 0;

		fin.getline(str, 60, '\n'); // 파일에서 한 줄 읽음

		int i = 0, j;
		while (str[i] != NULL) {
			j = 0; // 카테고리 이름 분리
			while (str[i] != '\t')
				c_name[j++] = str[i++];
			c_name[j] = NULL;

			j = 0; i++; // 메뉴이름 분리
			while (str[i] != '\t') {
				m_name[j] = str[i++];
				if (m_name[j++] == NULL) { // [오류] 가격 요소가 없는 경우
					cout << m_name << " Invalid input!" << endl;
					err = -1;
					break;
				}
			}
			m_name[j] = NULL;
			if (err == -1) break;

			j = 0; i++; // 가격 분리
			while (str[i] != NULL)
				c_price[j++] = str[i++];
			c_price[j] = NULL;
		}

		if (err == -1) continue; // [오류] 리스트에 추가하지 않고 넘어감

		price = atoi(c_price);
		if (price == 0) { // [오류] c_price가 문자인 경우 넘어감
			if (c_price[0]!='0') continue; 
		}
		add(c_name, m_name, price);
	}
	return 0;
}

// 하나의 인자로 리스트 추가 
//[return: 중복된 메뉴 (-2),입력오류(-1), 정상종료 (0)]
int List::add(char* str) {

	char m_name[30], c_name[20], c_price[10];
	int price;
	int i = 0, j;

	j = 0; // 카테고리 분리
	while (str[i] != ' ') {
		c_name[j] = str[i++];
		if (c_name[j++] == NULL) { //[오류] 메뉴와 가격 요소가 없는 경우
			return -1;
		}
	}
		
	c_name[j] = NULL;

	j = 0; i++; // 메뉴 분리
	while (str[i] != ' ') {
		m_name[j] = str[i++];
		if (m_name[j++] == NULL) { //[오류] 가격 요소가 없는 경우
			return -1;
		}
	}
	m_name[j] = NULL;

	j = 0; i++; // 가격분리
	while (str[i] != NULL)
		c_price[j++] = str[i++];
	c_price[j] = NULL;

	price = atoi(c_price);
	if (price == 0) { // [오류] c_price가 문자인 경우
		if (c_price[0] != '0') return -1;
	}
	//[return:중복된 메뉴(-2), 정상종료(0)]
	return add(c_name, m_name, price); 
}
 
//[return: 해당 카테고리 노드 주소]
CategoryNode* List::getCNode(int c_index) {
	CategoryNode* temp = head;
	for (int i = 0; i < c_index; i++)
		temp = temp->nextCNode;
	return temp;
}

//[return: 해당 메뉴 노드 주소]
MenuNode* List::getMNode(int c_index, int m_index) {
	CategoryNode* cate = head;
	for (int i = 0; i < c_index; i++)
		cate = cate->nextCNode;

	MenuNode* temp = cate->Menu;
	for (int i = 0; i < m_index; i++)
		temp = temp->nextMNode;
	return temp;
}

// 카테고리 이름으로 카테고리 노드의 순서 찾기 
//[return: 카테고리 없음(-1), 정상종료(카테고리의 순서)]
int List::find(char* cate) {
	CategoryNode* find = head;
	int c_index = 0;

	while (find!= nullptr) {
		if (!stricmp(cate, find->c_name))
			return c_index;
		else {
			find = find->nextCNode;
			c_index++;
		}
	}
	return -1; // 해당 카테고리 없음
}

// 카테고리 순서와 메뉴 이름으로 메뉴 노드의 순서 찾기 
//[return: 메뉴 없음(-1), 정상종료(메뉴의 순서)]
int List::find(int c_index, char* menu) {
	if (c_index == -1)
		return -1; //[예외] 카테고리가 없는 경우

	CategoryNode* cate = getCNode(c_index);
	MenuNode* find = cate->Menu;
	int m_index = 0;

	while (find != nullptr) {
		if (!stricmp(menu, find->m_name))
			return m_index;
		else {
			find = find->nextMNode;
			m_index++;
		}
	}
	return -1; //해당 메뉴 없음
}

// 카테고리 순서로 해당 카테고리 삭제
void List::remove(int c_index) {
	CategoryNode* remove = getCNode(c_index - 1);
	MenuNode* temp = remove->Menu;
	MenuNode* menu = remove->Menu;

	// 카테고리의 모든 메뉴 삭제
	for (int i = 0; i < remove->m_count; i++) {
		temp = temp->nextMNode;
		delete menu;
		menu = temp;
	}
	delete remove;
	setc_size(-1); // 카테고리의 개수  -1
}

// 메뉴 순서로 해당 메뉴 삭제
void List::remove(int c_index, int m_index) {
	CategoryNode* cate = getCNode(c_index);
	MenuNode* temp = getMNode(c_index, m_index-1);
	MenuNode* remove = getMNode(c_index, m_index);

	if (m_index == 0) //첫 번째 노드를 삭제하는 경우
		cate->Menu = remove->nextMNode;
	else
		temp->nextMNode = remove->nextMNode;
	delete remove;
	cate->m_count--; // 메뉴의 개수 -1

	if (cate->m_count == 0) { //카테고리의 모든 메뉴를 지운 경우
		if (c_index != 0) {
			CategoryNode* pre = getCNode(c_index - 1);
			pre->nextCNode = cate->nextCNode;
		}
		else { // 리스트의 첫 번째 카테고리인 경우
			head = cate->nextCNode;
		}
		delete cate;
		setc_size(-1); // 카테고리의 개수 -1
	}

	return;
}

// 메뉴 이름으로 해당 메뉴 삭제
//[return: 메뉴 없음(-1), 정상종료 (0)]
int List::deleteMenu(char* menu) {
	for (int c_index = 0; c_index < c_size(); c_index++) {
		int m_index = find(c_index, menu);
		if (m_index != -1) {
			remove(c_index, m_index);
			return 0;
		}
	}
	return -1; //[오류] 해당 메뉴가 없는 경우
}

// 리스트 전체 출력
void List::printList(void) {

	if (c_size() == 0) { // 리스트가 비어있는 경우
		cout << "The data does not exist!" << endl;
		return;
	}
	CategoryNode* cate = head;
	MenuNode* Menu = cate->Menu;

	for (int i = 0; i < c_size(); i++) {
		cout <<endl<<endl<< "========== " << cate->c_name << " ==========" << endl<<endl;
		for (int j = 0; j < cate->m_count; j++)
		{
			cout << Menu->m_name << ' ' << Menu->price << endl;
			Menu = Menu->nextMNode;
		}
		cate = cate->nextCNode;
		if (cate!=nullptr) Menu = cate->Menu;
	}
	return;
}

// c_index번째 카테고리 출력
//[return: 카테고리 없음(-1), 정상종료 (0)]
int List::printList(int c_index) {

	if (c_index == -1) // [오류] 카테고리가 없는 경우
		return -1;

	CategoryNode* cate = head;
	for (int i = 0; i < c_index; i++)
		cate = cate->nextCNode;

	MenuNode* Menu = cate->Menu;
	cout << endl << endl << "========== " << cate->c_name << " ==========" << endl << endl;
	for (int j = 0; j < cate->m_count; j++)
	{
		cout << Menu->m_name << ' ' << Menu->price << endl;
		Menu = Menu->nextMNode;
	}
	return 0;
}

// 메뉴 이름으로 메뉴와 가격 출력
//[return: 메뉴 없음(-1), 정상종료 (0)]
int List::printMenu(char* menu) {
	for (int c_index = 0; c_index< c_size();c_index++) {
		int m_index = find(c_index, menu);
		if (m_index != -1){
			MenuNode* Menu = getMNode(c_index, m_index);
			cout << Menu->m_name << ' ' << Menu->price << endl;
			return 0;
		}
	}
	return -1; //[오류] 메뉴 없음
}
