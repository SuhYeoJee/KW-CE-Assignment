#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
using namespace std;

int main(void)
{
	float accuracy = 0, speed = 0;
	ifstream fin("source.txt"); // cpp�� ���� ��ο� �־����
	ofstream fout("result.txt"); //���ٸ� ���� ��ο� ���� ����
	time_t start, end;
	string str, ustr;

	// [����] source.txt�� ���� ���
	if (!fin.is_open()) {
		cout << "NO FILE" << endl;
		return -1;
	}

	// �ܼ�â�� result.txt���Ͽ� ���
	cout << "KW Typing Werification Program" << endl;
	fout << "KW Typing Werification Program" << endl;
	cout << "��Ȯ�� :" << accuracy << "\t\t" << "�ӵ�(Ÿ��/s) : " << speed << endl << endl;
	fout << "��Ȯ�� :" << accuracy << "\t\t" << "�ӵ�(Ÿ��/s) : " << speed << endl << endl;

	// source.txt������ ��� ���� �� ���� �ݺ�
	while (!fin.eof()) {
		getline(fin, str); // source.txt �� �� �б�
		cout << "���� : " << str << endl << "�Է� : ";
		start = time(NULL); //�ð����� ����
		getline(cin, ustr);
		end = time(NULL); //�ð����� ����

		int ulength = ustr.length(); //�Է¹��� ������ ����

		// ���õ� ����� �Է¹��� ������ �� ���ھ� ���ؼ� ��Ÿ�� ���� ����
		int typo = 0;
		for (int i = 0; i < ulength; i++) {
			if (!(ustr.at(i) == str.at(i)))
				typo++;
		}

		// ��Ȯ���� �ӵ� ���
		speed = (float)ulength / (end - start);
		accuracy = ((ulength - typo) / (float)ulength) * 100;

		system("cls");// ȭ�� �����

		// �ܼ�â�� result.txt���Ͽ� ���
		cout << "KW Typing Werification Program" << endl;
		fout << str << endl;
		cout << fixed; cout.precision(2); //�ݿø�
		cout << "��Ȯ�� :" << accuracy << '\t' << "�ӵ�(Ÿ��/s) : " << speed << endl << endl;
		fout << fixed; fout.precision(2);
		fout << "��Ȯ�� :" << accuracy << '\t' << "�ӵ�(Ÿ��/s) : " << speed << endl << endl;
	}

	// ���� �ݱ�
	fin.close();
	fout.close();

}