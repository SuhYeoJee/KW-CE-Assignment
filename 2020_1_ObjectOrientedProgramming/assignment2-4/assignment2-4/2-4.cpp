#include <iostream>
using namespace std;

char* my_strstr(char* str, char* strSearch, char* strChange)
{
	int strsize, Searchsize, Changesize;
	for (int i = 0; i < 100; i++) {
		if (!str[i]) strsize = i;
	} //str의 길이

	for (int i = 0; i < 100; i++) {
		if (!strSearch[i]) Searchsize = i;
	} //strSerch의 길이

	for (int i = 0; i < 100; i++) {
		if (!strChange[i]) Changesize = i;
	} //strChange의 길이

	int p;
	for (int i = 0; i < strsize; i++) {
		if (str[i] == strSearch[0]) { // 검색어의 첫글자와 일치
			for (p = 0; p < Searchsize; p++) {
				if (str[i + p] != strSearch[p]) break; // 검색어와 불일치
			}
			if (p == Searchsize) {
				p = i; break; //검색어와 일치
			}// p는 교환할 문자의 인덱스
		}
		if (i == strsize - 1) return NULL; // 검색어가 없음
	}

	// 결과를 저장할 문자열 동적할당
	int length = strsize + Changesize - Searchsize;
	char* result = new char[length];
	for (int i = 0; i < strsize; i++) result[i] = str[i]; //str 내용복사
	result[length] = NULL; // 문자열 마지막 NULL삽입

	int k = (Changesize > Searchsize) ? Searchsize : Changesize;

	// 변경이후 뒤로 밀려나는 글자 이동
	for (int i = length - 1; i >= p + k; i--)
		result[i] = str[i - Changesize + Searchsize];

	// strChange 삽입
	for (int i = 0; i < Changesize; i++)
		result[p + i] = strChange[i];

	return result;
}

int main(void)
{
	char str[100], strSearch[100], strChange[100];
	char* result;

	// 문자열 입력
	cout << "원본 문자열을 입력하세요." << endl;
	cin.getline(str, 100);
	cout << endl << "변경 전 문자열을 입력하세요." << endl;
	cin.getline(strSearch, 100);
	cout << endl << "변경 후 문자열을 입력하세요." << endl;
	cin.getline(strChange, 100);

	// my_strstr 함수 호출
	result = my_strstr(str, strSearch, strChange);

	// 결과 출력
	cout << endl << "변경된 결과는 다음과 같습니다." << endl << endl;
	if (result)
		cout << "변경된 문자열:" << endl << result << endl;
	else
		cout << "일치하는 문자열이 없습니다." << endl;
	return 0;
}
