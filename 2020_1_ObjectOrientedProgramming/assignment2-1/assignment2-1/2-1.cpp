#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
using namespace std;

int main(void)
{
	float accuracy = 0, speed = 0;
	ifstream fin("source.txt"); // cpp와 같은 경로에 있어야함
	ofstream fout("result.txt"); //없다면 같은 경로에 새로 생성
	time_t start, end;
	string str, ustr;

	// [오류] source.txt가 없는 경우
	if (!fin.is_open()) {
		cout << "NO FILE" << endl;
		return -1;
	}

	// 콘솔창과 result.txt파일에 출력
	cout << "KW Typing Werification Program" << endl;
	fout << "KW Typing Werification Program" << endl;
	cout << "정확도 :" << accuracy << "\t\t" << "속도(타자/s) : " << speed << endl << endl;
	fout << "정확도 :" << accuracy << "\t\t" << "속도(타자/s) : " << speed << endl << endl;

	// source.txt파일을 모두 읽을 때 까지 반복
	while (!fin.eof()) {
		getline(fin, str); // source.txt 한 줄 읽기
		cout << "문장 : " << str << endl << "입력 : ";
		start = time(NULL); //시간측정 시작
		getline(cin, ustr);
		end = time(NULL); //시간측정 종료

		int ulength = ustr.length(); //입력받은 문장의 길이

		// 제시된 문장과 입력받은 문장을 한 글자씩 비교해서 오타의 수를 구함
		int typo = 0;
		for (int i = 0; i < ulength; i++) {
			if (!(ustr.at(i) == str.at(i)))
				typo++;
		}

		// 정확도와 속도 계산
		speed = (float)ulength / (end - start);
		accuracy = ((ulength - typo) / (float)ulength) * 100;

		system("cls");// 화면 지우기

		// 콘솔창과 result.txt파일에 출력
		cout << "KW Typing Werification Program" << endl;
		fout << str << endl;
		cout << fixed; cout.precision(2); //반올림
		cout << "정확도 :" << accuracy << '\t' << "속도(타자/s) : " << speed << endl << endl;
		fout << fixed; fout.precision(2);
		fout << "정확도 :" << accuracy << '\t' << "속도(타자/s) : " << speed << endl << endl;
	}

	// 파일 닫기
	fin.close();
	fout.close();

}