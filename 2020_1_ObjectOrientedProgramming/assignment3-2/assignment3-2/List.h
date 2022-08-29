#pragma once

class Node {
public:
	char name[40];
	char professor[20];
	char grade; // �� ���� ����
	Node* prev;
	Node* next;
};

class List {
private:
	int count; // ����� ��
	Node* head;
public:
	List();
	~List();

	int GetCount(void); // ��� �� ��ȯ

	int isPosi(int position); // ��� ���� ��ġ Ȯ��
	void Insert(int position); // �� ��� ����

	void Delete(void); // ������
	bool Update(void); // ��� ���� ����

	int SearchLecture(char * _name); // ���Ǹ����� ��� ���� ã��
	bool SearchProfessor(void); // ���������� �������
	bool SearchGrade(void); // �г����� �������

	bool Sort(void); // �������� ����
	void Display(void); // ��ü ���
	void Display(int position); // �� ���� ���
	bool Reverse(void); // ���� ������
};
