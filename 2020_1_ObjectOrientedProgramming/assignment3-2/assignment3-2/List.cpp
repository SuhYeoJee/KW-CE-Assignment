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

// 새 노드를 삽입할 때 적절한 위치를 입력받았는지 확인
// [return: 부적절한 위치(-1), 적절한 위치(0)]
int List::isPosi(int position) {
	if ((position > 0) && (position <= count + 1)) {
		return 0;
	}
	return -1;
}

// 새 노드 삽입
void List::Insert(int position) {
	
	char _name[40], _prof[20], _grade;
	Node* add = new Node;

	// 정보 입력
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

	// 노드 연결
	if (head == nullptr) { // 첫 노드 추가
		add->next = add;
		add->prev = add;
		head = add;
	}
	else if ((position == 0) || (position == -1) ){ // 리스트의 맨앞 혹은 맨끝
		add->next = head;
		add->prev = head->prev;
		add->next->prev = add;
		add->prev->next = add;
		if (position == 0)
			head = add;
	}
	else { // 리스트 중간에 추가
		Node* pre = head;
		for (int i = 0; i < position - 1; i++)
			pre = pre->next;
		add->prev = pre;
		add->next = pre->next;
		add->next->prev = add;
		add->prev->next = add;
	}
	count++; // 노드의 개수 +1;
	return;
}

// 과목명이 일치하는 노드 삭제
void List::Delete(void) {
	char _name[40];
	int position=0;

	if (count == 0) { //[오류] 리스트에 노드가 없는 경우
		cout << "No Data" << endl;
		return;
	}

	do { // 삭제할 과목명 입력, 리스트에 없는 경우 다시 입력받음
		cout << "Enter the lecture of lecture Delete: ";
		cin.getline(_name, 40, '\n');
	} while ((position=SearchLecture(_name)) == -1);
	
	// 노드 삭제
	Node* del = head;
	for (int i = 0; i < position; i++)
		del = del->next;
	Node* temp = del->prev;
	temp->next = del->next;
	temp = del->next;
	temp->prev = del->prev;

	delete del;
	count--; // 노드의 수 -1;
	cout << "**" << _name << " has been deleted from position" << position+1 << "**" << endl<<endl;

	return;
}

// 과목명이 일치하는 노드의 내용 수정
// [return: 수정하려는 과목이 없는 경우(false), 정상종료 (true)]
bool List::Update(void) {
	char _name[40];
	int position;
	
	if (count == 0) { // [오류] 리스트가 빈 경우
		cout << "No data" << endl;
		return false;
	}

	// 정보 입력
	cout << "->Enter the lecture name: ";
	cin.getline(_name, 40, '\n');
	if ((position = SearchLecture(_name)) == -1) { // [오류] 해당 노드가 없는 경우
		return false;
	}
	else {
		char _prof[20], _grade;
		Node * temp = head;
		for (int i = 0; i < position; i++)
			temp = temp->next;
		// 새 정보 입력, 저장
		do {
			cout << "->Enter the new lecture name: ";
			cin.getline(_name, 40, '\n');
			if (strcmp(temp->name, _name) == 0)break; // 수정 전의 이름과 같은 경우
		} while (SearchLecture(_name) != -1); // 리스트의 다른 과목과 일치하는 경우 다시 입력받음
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

// 과목명이 일치하는 노드의 순서 반환
// [return: 해당 노드 없음(-1), 정상종료( 해당 노드의 순서)]
int List::SearchLecture(char * _name) {
	if (count == 0) { // [오류] 리스트가 빈 경우
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

// 교수명이 일치하는 노드의 정보 출력
// [return: 해당노드 없음(false), 정상종료(true)]
bool List::SearchProfessor(void) {
	int err = false;
	char _prof[20];

	if (count == 0) { // [오류] 리스트가 빈 경우
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

// 학년이 일치하는 노드의 정보 출력
// [return: 해당노드 없음(false), 정상종료(true)]
bool List::SearchGrade(void) {
	int err = false;
	char _grade;

	if (count == 0) { // [오류] 리스트가 빈 경우
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

// 학년 오름차순으로 정렬, 학년이 같은경우 과목명 순서
// [return: 노드 없음(false), 정상종료(true)]
bool List::Sort(void) {
	if (count == 0) { // [오류] 리스트가 빈 경우
		cout << "No data" << endl;
		return false;
	}
	while(1){
		Node* sort=head;
		// 오름차순이 아닌 노드 찾기
		for (int i = 0; i < count; i++) {
			if (sort->grade < sort->next->grade) { // sort와 sort의 다음 노드가 학년 오름차순
				sort = sort->next;
			}
			else if (sort->grade == sort->next->grade) { // sort와 sort의 다음 노드가 학년이 일치
				//문자열비교
				if (stricmp(sort->name, sort->next->name) < 0) { 
					sort = sort->next; // sort와 sort의 다음 노드가 강의명 오름차순
				}
				else {
					if (sort->next == head) // 마지막까지 모두 정렬 된 경우
						return true;
					break;
				}
			}
			else { // sort와 sort의 다음 노드가 학년 오름차순이 아님
				if (sort->next == head) // 마지막까지 모두 정렬 된 경우
					return true;
				break;
			}
		}

		Node* temp = head;
		// 오름차순이 아닌 노드 sort를 이동시킴
		for (int j = 0; j < count; j++) {
			if (sort == temp) { // 같은 노드를 비교하는 경우
				temp = temp->next;
			}
			if (sort->grade < temp->grade) { // sort와 temp가 오름차순으로 정렬 된 경우
				temp = temp->next;
				// sort를 제외한 리스트 전체가 오름차순인 경우 sort는 리스트의 가장 끝으로 이동
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
			else if (sort->grade == temp->grade) { // 학년이 같은 경우
				for (int k = 0; k < count; k++) {
					if (sort == temp) { // 같은 노드를 비교하는 경우
						temp = temp->next;
					}
					if (stricmp(sort->name, temp->name) < 0) { // sort와 temp가 오름차순으로 정렬된 경우
						temp = temp->next;
						if (temp == head) { // sort를 제외한 전체가 오름차순, sort는 리스트의 맨 끝
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
					else { // sort와 temp가 오름차순이 아닌 경우 sort이동
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
			else { // sort와 temp가 오름차순이 아닌 경우 sort이동

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

// 리스트 전체 출력
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
// 한 과목 출력
void List::Display(int position) {
	Node* temp = head;

	if (position == -1) // [오류] 출력하려는 노드 없음
		return;

	for (int i = 0; i < position; i++)
		temp = temp->next;

	cout << "* At position " << position+1 << "*" << endl;
	cout << "lecture name: " << temp->name << endl;
	cout << "lecture professor: " << temp->professor << endl;
	cout << "lecture grade: " << temp->grade << endl;

	return;
}
// 리스트 순서 뒤집기
// [return: 노드 없음(false), 정상종료(true)]
bool List::Reverse(void) {
	Node* rev = head, * temp;
	if (count == 0) { // [오류] 리스트가 빈 경우
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

