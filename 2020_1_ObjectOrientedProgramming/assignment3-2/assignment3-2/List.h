#pragma once

class Node {
public:
	char name[40];
	char professor[20];
	char grade; // 한 글자 문자
	Node* prev;
	Node* next;
};

class List {
private:
	int count; // 노드의 수
	Node* head;
public:
	List();
	~List();

	int GetCount(void); // 노드 수 반환

	int isPosi(int position); // 노드 삽입 위치 확인
	void Insert(int position); // 새 노드 삽입

	void Delete(void); // 노드삭제
	bool Update(void); // 노드 정보 수정

	int SearchLecture(char * _name); // 강의명으로 노드 순서 찾기
	bool SearchProfessor(void); // 교수명으로 정보출력
	bool SearchGrade(void); // 학년으로 정보출력

	bool Sort(void); // 오름차순 정렬
	void Display(void); // 전체 출력
	void Display(int position); // 한 과목 출력
	bool Reverse(void); // 순서 뒤집기
};
