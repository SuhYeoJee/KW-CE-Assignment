#include <iostream>
#include "List.h"
using namespace std;

List::List() {
	head = nullptr;
	count = 0;
}

List::~List() {
	Node* temp = head;
	while (count > 0) {
		temp = head;
		head = temp->next;
		delete temp;
		count--;
	}
}

int List::GetCount(void) { return count; }

// �� ��带 ������ �� ������ ��ġ�� �Է¹޾Ҵ��� Ȯ��
// [return: �������� ��ġ(-1), ������ ��ġ(0)]
int List::isPosi(int position) {
	if ((position > 0) && (position <= count + 1)) {
		return 0;
	}
	return -1;
}

// �� ��� ����
void List::Insert(int position) {
	
	char _name[40], _prof[20], _grade;
	Node* add = new Node;

	// ���� �Է�
	do {
	cout << "->Enter the lecture name: ";
	cin.getline(_name, 40, '\n');
	} while (SearchLecture(_name)!=-1);
	strcpy(add->name, _name);

	cout << "->Enter the lecture professor: ";
	cin >> _prof; cin.ignore(50, '\n');
	strcpy(add->professor, _prof);

	cout << "->Enter the lecture grade: ";
	cin >> _grade; cin.ignore(50, '\n');
	add->grade = _grade;

	// ��� ����
	if (head == nullptr) { // ù ��� �߰�
		add->next = add;
		add->prev = add;
		head = add;
	}
	else if ((position == 0) || (position == -1) ){ // ����Ʈ�� �Ǿ� Ȥ�� �ǳ�
		add->next = head;
		add->prev = head->prev;
		add->next->prev = add;
		add->prev->next = add;
		if (position == 0)
			head = add;
	}
	else { // ����Ʈ �߰��� �߰�
		Node* pre = head;
		for (int i = 0; i < position - 1; i++)
			pre = pre->next;
		add->prev = pre;
		add->next = pre->next;
		add->next->prev = add;
		add->prev->next = add;
	}
	count++; // ����� ���� +1;
	return;
}

// ������� ��ġ�ϴ� ��� ����
void List::Delete(void) {
	char _name[40];
	int position=0;

	if (count == 0) { //[����] ����Ʈ�� ��尡 ���� ���
		cout << "No Data" << endl;
		return;
	}

	do { // ������ ����� �Է�, ����Ʈ�� ���� ��� �ٽ� �Է¹���
		cout << "Enter the lecture of lecture Delete: ";
		cin.getline(_name, 40, '\n');
	} while ((position=SearchLecture(_name)) == -1);
	
	// ��� ����
	Node* del = head;
	for (int i = 0; i < position; i++)
		del = del->next;
	Node* temp = del->prev;
	temp->next = del->next;
	temp = del->next;
	temp->prev = del->prev;

	delete del;
	count--; // ����� �� -1;
	cout << "**" << _name << " has been deleted from position" << position+1 << "**" << endl<<endl;

	return;
}

// ������� ��ġ�ϴ� ����� ���� ����
// [return: �����Ϸ��� ������ ���� ���(false), �������� (true)]
bool List::Update(void) {
	char _name[40];
	int position;
	
	if (count == 0) { // [����] ����Ʈ�� �� ���
		cout << "No data" << endl;
		return false;
	}

	// ���� �Է�
	cout << "->Enter the lecture name: ";
	cin.getline(_name, 40, '\n');
	if ((position = SearchLecture(_name)) == -1) { // [����] �ش� ��尡 ���� ���
		return false;
	}
	else {
		char _prof[20], _grade;
		Node * temp = head;
		for (int i = 0; i < position; i++)
			temp = temp->next;
		// �� ���� �Է�, ����
		do {
			cout << "->Enter the new lecture name: ";
			cin.getline(_name, 40, '\n');
			if (strcmp(temp->name, _name) == 0)break; // ���� ���� �̸��� ���� ���
		} while (SearchLecture(_name) != -1); // ����Ʈ�� �ٸ� ����� ��ġ�ϴ� ��� �ٽ� �Է¹���
		strcpy(temp->name, _name);

		cout << "->Enter the new lecture professor: ";
		cin >> _prof; cin.ignore(50, '\n');
		strcpy(temp->professor, _prof);

		cout << "->Enter the new lecture grade: ";
		cin >> _grade; cin.ignore(50, '\n');
		temp->grade = _grade;
	}

	return true;
}

// ������� ��ġ�ϴ� ����� ���� ��ȯ
// [return: �ش� ��� ����(-1), ��������( �ش� ����� ����)]
int List::SearchLecture(char * _name) {
	if (count == 0) { // [����] ����Ʈ�� �� ���
		return -1;
	}
	Node* temp = head;
	for (int i = 0; i < count; i++) {
		if (stricmp(temp->name, _name) == 0) {
			return i;
		}
		temp = temp->next;
	}
	return -1;
}

// �������� ��ġ�ϴ� ����� ���� ���
// [return: �ش��� ����(false), ��������(true)]
bool List::SearchProfessor(void) {
	int err = false;
	char _prof[20];

	if (count == 0) { // [����] ����Ʈ�� �� ���
		cout << "No data" << endl;
		return false;
	}

	cout << "->Enter the professor name you want to search: ";
	cin >> _prof; cin.ignore(50, '\n');

	Node* temp = head;
	for (int i = 0; i < count; i++) {
		if (stricmp(temp->professor, _prof) == 0) {
			Display(i);
			err = true;
		}
		temp = temp->next;
	}
	return err;
}

// �г��� ��ġ�ϴ� ����� ���� ���
// [return: �ش��� ����(false), ��������(true)]
bool List::SearchGrade(void) {
	int err = false;
	char _grade;

	if (count == 0) { // [����] ����Ʈ�� �� ���
		cout << "No data" << endl;
		return false;
	}
	cout << "Enter the grade you want to search: ";
	cin >> _grade; cin.ignore(50, '\n');

	Node* temp = head;
	for (int i = 0; i < count; i++) {
		if (temp->grade== _grade) {
			Display(i);
			err = true;
		}
		temp = temp->next;
	}
	return err;
}

// �г� ������������ ����, �г��� ������� ����� ����
// [return: ��� ����(false), ��������(true)]
bool List::Sort(void) {
	if (count == 0) { // [����] ����Ʈ�� �� ���
		cout << "No data" << endl;
		return false;
	}
	while(1){
		Node* sort=head;
		// ���������� �ƴ� ��� ã��
		for (int i = 0; i < count; i++) {
			if (sort->grade < sort->next->grade) { // sort�� sort�� ���� ��尡 �г� ��������
				sort = sort->next;
			}
			else if (sort->grade == sort->next->grade) { // sort�� sort�� ���� ��尡 �г��� ��ġ
				//���ڿ���
				if (stricmp(sort->name, sort->next->name) < 0) { 
					sort = sort->next; // sort�� sort�� ���� ��尡 ���Ǹ� ��������
				}
				else {
					if (sort->next == head) // ���������� ��� ���� �� ���
						return true;
					break;
				}
			}
			else { // sort�� sort�� ���� ��尡 �г� ���������� �ƴ�
				if (sort->next == head) // ���������� ��� ���� �� ���
					return true;
				break;
			}
		}

		Node* temp = head;
		// ���������� �ƴ� ��� sort�� �̵���Ŵ
		for (int j = 0; j < count; j++) {
			if (sort == temp) { // ���� ��带 ���ϴ� ���
				temp = temp->next;
			}
			if (sort->grade < temp->grade) { // sort�� temp�� ������������ ���� �� ���
				temp = temp->next;
				// sort�� ������ ����Ʈ ��ü�� ���������� ��� sort�� ����Ʈ�� ���� ������ �̵�
				if (temp == head) {
					Node* temp2  = sort->prev;
					temp2->next = sort->next;
					sort->next->prev = temp2;

					temp->prev->next = sort;
					sort->prev = temp->prev;
					sort->next = temp;
					temp->prev = sort;

					temp = head;
					break;
				}
			}
			else if (sort->grade == temp->grade) { // �г��� ���� ���
				for (int k = 0; k < count; k++) {
					if (sort == temp) { // ���� ��带 ���ϴ� ���
						temp = temp->next;
					}
					if (stricmp(sort->name, temp->name) < 0) { // sort�� temp�� ������������ ���ĵ� ���
						temp = temp->next;
						if (temp == head) { // sort�� ������ ��ü�� ��������, sort�� ����Ʈ�� �� ��
							Node* temp2 = sort->prev;
							temp2->next = sort->next;
							sort->next->prev = temp2;

							temp->prev->next = sort;
							sort->prev = temp->prev;
							sort->next = temp;
							temp->prev = sort;

							break;
						}
					}
					else { // sort�� temp�� ���������� �ƴ� ��� sort�̵�
						if (sort == head)
							head = head->next;

						Node* temp2 = sort->prev;
						temp2->next = sort->next;
						temp2 = temp2->next;
						temp2->prev = sort->prev;

						temp->prev->next = sort;
						sort->prev = temp->prev;
						temp->prev = sort;
						sort->next = temp;

						break;

					}
				}
			}
			else { // sort�� temp�� ���������� �ƴ� ��� sort�̵�

				if (sort == head)
					head = head->next;

				Node* temp2 = sort->prev;
				temp2->next = sort->next;
				temp2 = temp2->next;
				temp2->prev = sort->prev;

				temp->prev->next = sort;
				sort->prev = temp->prev;
				temp->prev = sort;
				sort->next = temp;

				break;
			}
		}
	}
	return true;
}

// ����Ʈ ��ü ���
void List::Display(void) {
	Node* temp = head;
	if (count == 0) {
		cout << "No data" << endl;
		return;
	}
	for(int i=0;i<count;i++) {
		cout << "lecture name: " <<temp->name<< endl;
		cout << "lecture professor: " <<temp->professor<< endl;
		cout << "lecture grade: " <<temp->grade<< endl;
		temp = temp->next;
	}
	return;
}
// �� ���� ���
void List::Display(int position) {
	Node* temp = head;

	if (position == -1) // [����] ����Ϸ��� ��� ����
		return;

	for (int i = 0; i < position; i++)
		temp = temp->next;

	cout << "* At position " << position+1 << "*" << endl;
	cout << "lecture name: " << temp->name << endl;
	cout << "lecture professor: " << temp->professor << endl;
	cout << "lecture grade: " << temp->grade << endl;

	return;
}
// ����Ʈ ���� ������
// [return: ��� ����(false), ��������(true)]
bool List::Reverse(void) {
	Node* rev = head, * temp;
	if (count == 0) { // [����] ����Ʈ�� �� ���
		cout << "No data" << endl;
		return false;
	}
	for (int i = 0; i < count; i++) {
		temp=rev->prev;
		rev->prev = rev->next;
		rev->next = temp;

		rev = rev->prev;
	}
	head = head->next;
	return true;
}

