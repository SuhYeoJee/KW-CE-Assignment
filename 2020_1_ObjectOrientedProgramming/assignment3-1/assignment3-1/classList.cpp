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

// �и��� ���ڷ� ����Ʈ �߰� 
//[return: �ߺ��� �޴� (-2),  �������� (0)]
int List::add(char* cate, char * menu, int price){

	// ī�װ��� �޴��� ������ ã��
	int c_index = find(cate);
	int m_index = find(c_index, menu);

	if (c_index == -1) { // ī�װ��� ������ ���� ���
		CategoryNode* c_add = new CategoryNode;
		strcpy(c_add->c_name, cate);
		
		if (c_size() == 0) {// ù ��° ī�װ��� ���
			delete head;
			head = c_add;
		}
		else {
			CategoryNode* temp = head;
			for (int i = 0; i < c_size() -1; i++)
				temp = temp->nextCNode;
			temp->nextCNode = c_add;
		}
		setc_size(1); // ī�װ� ���� 1 ������
		c_add->nextCNode = nullptr;
		
		//�� �޴���� ���� (ī�װ��� ù ��° �޴�)
		MenuNode* m_add = new MenuNode;
		strcpy(m_add->m_name, menu);
		m_add->nextMNode = nullptr;
		m_add->price = price;

		c_add->Menu = m_add;
		c_add->m_count++;
	}
	else  { // ī�װ��� �ִ� ���
		if (m_index != -1) {//[����] �̹� �����ϴ� �޴�
			cout << menu << " already exists!" << endl;
			return -2;
		}
		else {
			// �� �޴���� ����
			MenuNode* add = new MenuNode;
			strcpy(add->m_name, menu);
			add->price = price;
			add->nextMNode = nullptr;

			// �޴��� ���� m_index ã��
			CategoryNode* category = getCNode(c_index);
			MenuNode* temp = category->Menu;
			
			for (int i = 0; i < category->m_count; i++) {
				if (temp->price > price) {
					m_index = i;
					break;
				}
				else if (temp->price == price) {
					m_index = i; // ������ ���� �޴� �� ���� ���� m_index
					int k = 0; // ���� ����� �޴� �� ������ ���� �޴��� ����
					MenuNode* sameprice = temp;
					while (temp->price != price) { 
						k++; 
						temp = temp->nextMNode;
					}
					for (k; k > 0; k--) {// �̸��� ��
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

				if (temp == nullptr) { // �߰��ϴ� �޴��� ���� ������ �޴��� ���
					m_index = i+1;
					break;
				}
			}
			
			// new�� �ε��� = m_index
			// temp�� new�� �������

			if (m_index == 0) { // �޴��� ���� ��
				MenuNode* next = category->Menu;
				add->nextMNode = next;
				category->Menu = add;
			}
			else { 
				MenuNode* pre = getMNode(c_index, m_index-1);
				if (m_index == category->m_count) // �޴��� ���� ��
					add->nextMNode = nullptr;
				else //�߰�
					add->nextMNode = temp;
				pre->nextMNode = add;
			}
			category->m_count++;
		}
	}
	return 0;
}

// input.txt������ ���뿡�� �߰� 
//[return: ���� ����(-1), �������� (0)]
int List::add(void) {
	// .cpp���ϰ� input.txt�� ���� ��ο� �־�� �Ѵ�.
	ifstream fin("input.txt");
	if (!fin.is_open()) // [����] ������ ���� ���
		return -1;

	while (!fin.eof()) {
		char str[60], m_name[30], c_name[20], c_price[10];
		int price, err = 0;

		fin.getline(str, 60, '\n'); // ���Ͽ��� �� �� ����

		int i = 0, j;
		while (str[i] != NULL) {
			j = 0; // ī�װ� �̸� �и�
			while (str[i] != '\t')
				c_name[j++] = str[i++];
			c_name[j] = NULL;

			j = 0; i++; // �޴��̸� �и�
			while (str[i] != '\t') {
				m_name[j] = str[i++];
				if (m_name[j++] == NULL) { // [����] ���� ��Ұ� ���� ���
					cout << m_name << " Invalid input!" << endl;
					err = -1;
					break;
				}
			}
			m_name[j] = NULL;
			if (err == -1) break;

			j = 0; i++; // ���� �и�
			while (str[i] != NULL)
				c_price[j++] = str[i++];
			c_price[j] = NULL;
		}

		if (err == -1) continue; // [����] ����Ʈ�� �߰����� �ʰ� �Ѿ

		price = atoi(c_price);
		if (price == 0) { // [����] c_price�� ������ ��� �Ѿ
			if (c_price[0]!='0') continue; 
		}
		add(c_name, m_name, price);
	}
	return 0;
}

// �ϳ��� ���ڷ� ����Ʈ �߰� 
//[return: �ߺ��� �޴� (-2),�Է¿���(-1), �������� (0)]
int List::add(char* str) {

	char m_name[30], c_name[20], c_price[10];
	int price;
	int i = 0, j;

	j = 0; // ī�װ� �и�
	while (str[i] != ' ') {
		c_name[j] = str[i++];
		if (c_name[j++] == NULL) { //[����] �޴��� ���� ��Ұ� ���� ���
			return -1;
		}
	}
		
	c_name[j] = NULL;

	j = 0; i++; // �޴� �и�
	while (str[i] != ' ') {
		m_name[j] = str[i++];
		if (m_name[j++] == NULL) { //[����] ���� ��Ұ� ���� ���
			return -1;
		}
	}
	m_name[j] = NULL;

	j = 0; i++; // ���ݺи�
	while (str[i] != NULL)
		c_price[j++] = str[i++];
	c_price[j] = NULL;

	price = atoi(c_price);
	if (price == 0) { // [����] c_price�� ������ ���
		if (c_price[0] != '0') return -1;
	}
	//[return:�ߺ��� �޴�(-2), ��������(0)]
	return add(c_name, m_name, price); 
}
 
//[return: �ش� ī�װ� ��� �ּ�]
CategoryNode* List::getCNode(int c_index) {
	CategoryNode* temp = head;
	for (int i = 0; i < c_index; i++)
		temp = temp->nextCNode;
	return temp;
}

//[return: �ش� �޴� ��� �ּ�]
MenuNode* List::getMNode(int c_index, int m_index) {
	CategoryNode* cate = head;
	for (int i = 0; i < c_index; i++)
		cate = cate->nextCNode;

	MenuNode* temp = cate->Menu;
	for (int i = 0; i < m_index; i++)
		temp = temp->nextMNode;
	return temp;
}

// ī�װ� �̸����� ī�װ� ����� ���� ã�� 
//[return: ī�װ� ����(-1), ��������(ī�װ��� ����)]
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
	return -1; // �ش� ī�װ� ����
}

// ī�װ� ������ �޴� �̸����� �޴� ����� ���� ã�� 
//[return: �޴� ����(-1), ��������(�޴��� ����)]
int List::find(int c_index, char* menu) {
	if (c_index == -1)
		return -1; //[����] ī�װ��� ���� ���

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
	return -1; //�ش� �޴� ����
}

// ī�װ� ������ �ش� ī�װ� ����
void List::remove(int c_index) {
	CategoryNode* remove = getCNode(c_index - 1);
	MenuNode* temp = remove->Menu;
	MenuNode* menu = remove->Menu;

	// ī�װ��� ��� �޴� ����
	for (int i = 0; i < remove->m_count; i++) {
		temp = temp->nextMNode;
		delete menu;
		menu = temp;
	}
	delete remove;
	setc_size(-1); // ī�װ��� ����  -1
}

// �޴� ������ �ش� �޴� ����
void List::remove(int c_index, int m_index) {
	CategoryNode* cate = getCNode(c_index);
	MenuNode* temp = getMNode(c_index, m_index-1);
	MenuNode* remove = getMNode(c_index, m_index);

	if (m_index == 0) //ù ��° ��带 �����ϴ� ���
		cate->Menu = remove->nextMNode;
	else
		temp->nextMNode = remove->nextMNode;
	delete remove;
	cate->m_count--; // �޴��� ���� -1

	if (cate->m_count == 0) { //ī�װ��� ��� �޴��� ���� ���
		if (c_index != 0) {
			CategoryNode* pre = getCNode(c_index - 1);
			pre->nextCNode = cate->nextCNode;
		}
		else { // ����Ʈ�� ù ��° ī�װ��� ���
			head = cate->nextCNode;
		}
		delete cate;
		setc_size(-1); // ī�װ��� ���� -1
	}

	return;
}

// �޴� �̸����� �ش� �޴� ����
//[return: �޴� ����(-1), �������� (0)]
int List::deleteMenu(char* menu) {
	for (int c_index = 0; c_index < c_size(); c_index++) {
		int m_index = find(c_index, menu);
		if (m_index != -1) {
			remove(c_index, m_index);
			return 0;
		}
	}
	return -1; //[����] �ش� �޴��� ���� ���
}

// ����Ʈ ��ü ���
void List::printList(void) {

	if (c_size() == 0) { // ����Ʈ�� ����ִ� ���
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

// c_index��° ī�װ� ���
//[return: ī�װ� ����(-1), �������� (0)]
int List::printList(int c_index) {

	if (c_index == -1) // [����] ī�װ��� ���� ���
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

// �޴� �̸����� �޴��� ���� ���
//[return: �޴� ����(-1), �������� (0)]
int List::printMenu(char* menu) {
	for (int c_index = 0; c_index< c_size();c_index++) {
		int m_index = find(c_index, menu);
		if (m_index != -1){
			MenuNode* Menu = getMNode(c_index, m_index);
			cout << Menu->m_name << ' ' << Menu->price << endl;
			return 0;
		}
	}
	return -1; //[����] �޴� ����
}
