#include <iostream>
#include "List.h"
using namespace std;

int main(void) {

	cout << "**************************" << endl;
	cout << "S T A R T" << endl;
	cout << "**************************" << endl;
	List Lecture;
	char str[40];

	while (1) {
		int select = 0,err = 0, position = 0;

		cout << "1. Insert lecture at beginning" << endl;
		cout << "2. Insert lecture at last" << endl;
		cout << "3. Insert lecture at position" << endl;
		cout << "4. Delete lecture" << endl;
		cout << "5. Update lecture" << endl;
		cout << "6. Search lecture" << endl;
		cout << "7. Search professor" << endl;
		cout << "8. Search grade" << endl;
		cout << "9. Sort by grade In ascennding order" << endl;
		cout << "10. Display lecture list" << endl;
		cout << "11. Reverse lecture list" << endl;
		cout << "12.Exit" << endl;
		cout << "input number: ";
		cin >> select; cin.ignore();

		switch (select)
		{
		case(1):
			cout << "<Insert lecture at beginnig>" << endl;
			Lecture.Insert(0);
			break;
		case(2):
			cout << "<insert lecture at last>" << endl;
			Lecture.Insert(-1);
			break;
		case(3):
			cout << "<insert lecture at position>" << endl;
			do{ // [오류] 1~count+1 사이 값이 아니면 다시 입력받음
				position = 0;
				cout << "Enter the position of lecture insert: ";
				cin >> position; cin.ignore();
			} while (Lecture.isPosi(position));
			Lecture.Insert(position-1);
			break;
		case(4):
			cout << "<Delete lecture>" << endl;
			Lecture.Delete();
			break;
		case(5):
			cout << "<Update lecture>" << endl;
			err = Lecture.Update();
			if(!err) //[오류] 해당 과목이 없음
				cout << "No information to update" << endl;
			break;
		case(6):
			cout << "<Search lecture>" << endl;
			if (Lecture.GetCount() == 0) { // [오류] 리스트가 비어있음
				cout << "No Data" << endl;
				break;
			}
			cout << "->Enter the lecture name you want to search:";
			cin >> str; cin.ignore(50, '\n');
			Lecture.Display(Lecture.SearchLecture(str));
			break;
		case(7):
			cout << "<Search professor>" << endl;
			if(!Lecture.SearchProfessor())  
				cout << "No Data" << endl; // [오류] 해당 교수명 없음
			break;
		case(8):
			cout << "<Search grade>" << endl;
			if(!Lecture.SearchGrade())
				cout << "No Data" << endl; // [오류] 해당 학년 없음
			break;
		case(9):
			cout << "<Sort by grade In ascennding order>" << endl;
			err = Lecture.Sort();
			break;
		case(10):
			cout << "<Display lecture list>" << endl;
			Lecture.Display();
			break;
		case(11):
			cout << "<Reverse lecture list>" << endl;
			err = Lecture.Reverse();
			if (err)
				cout << "**The product list has been reversed**" << endl;
			break;
		case(12):
			cout << "<Exit>" << endl;
			return 0;
		default: // [오류] 1~12가 입력되지 않은 경우
			cout << "Invalid input" << endl;
			break;
		}
		cout << "----------------------------" << endl;
	}
	return 0;
}