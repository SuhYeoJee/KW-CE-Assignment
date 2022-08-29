#pragma once

// �޴��� ����(�̸�, ����)�� �����ϴ� ���
class MenuNode{
public:
	char m_name[30];
	int price;
	MenuNode* nextMNode;
};

// ī�װ��� ����(�̸�, �޴��� ����)�� �����ϴ� ���
class CategoryNode{
public:
	char c_name[20];
	int m_count = 0;
	CategoryNode* nextCNode;
	MenuNode* Menu;
};

// ���� ���� ����Ʈ
class List {
private:
	int c_count; // ī�װ��� ����
	CategoryNode* head = new CategoryNode;

public:
	List();
	~List();

	// �޴��� �߰��ϴ� �Լ�
	int add(char* cate, char* menu, int price);
	int add(void);
	int add(char* str);

	// c_index��° ī�װ� ����� �ּҸ� ��ȯ
	CategoryNode* getCNode(int c_index);
	// (c_index��° ī�װ� �����) m_index��° �޴� ����� �ּҸ� ��ȯ
	MenuNode* getMNode(int c_index, int m_index);

	// ī�װ��� ���� ��ȯ
	int c_size(void) { return c_count; }
	// ī�װ��� ������ i��ŭ ����
	void setc_size(int i) { c_count += i; }

	// ī�װ� �̸����� ī�װ� ����� ������ ã�� ��ȯ
	int find(char* cate);
	// �޴� �̸����� (c_index��° ī�װ� �����) �޴� ����� ������ ã�� ��ȯ
	int find(int c_index, char* menu);

	// c_index��° ī�װ� ����
	void remove(int c_index);
	// (c_index��° ī�װ� �����) m_index��° �޴� ����
	void remove(int c_index, int m_index);
	// �޴� �̸����� �ش� �޴� ����
	int deleteMenu(char* menu);

	// ����Ʈ ��ü ���
	void printList(void);
	// c_index��° ī�װ� ���
	int printList(int c_index);
	// �޴� �̸����� �޴��� ���� ���
	int printMenu(char* menu);
};
