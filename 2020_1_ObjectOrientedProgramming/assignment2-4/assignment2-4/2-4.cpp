#include <iostream>
using namespace std;

char* my_strstr(char* str, char* strSearch, char* strChange)
{
	int strsize, Searchsize, Changesize;
	for (int i = 0; i < 100; i++) {
		if (!str[i]) strsize = i;
	} //str�� ����

	for (int i = 0; i < 100; i++) {
		if (!strSearch[i]) Searchsize = i;
	} //strSerch�� ����

	for (int i = 0; i < 100; i++) {
		if (!strChange[i]) Changesize = i;
	} //strChange�� ����

	int p;
	for (int i = 0; i < strsize; i++) {
		if (str[i] == strSearch[0]) { // �˻����� ù���ڿ� ��ġ
			for (p = 0; p < Searchsize; p++) {
				if (str[i + p] != strSearch[p]) break; // �˻���� ����ġ
			}
			if (p == Searchsize) {
				p = i; break; //�˻���� ��ġ
			}// p�� ��ȯ�� ������ �ε���
		}
		if (i == strsize - 1) return NULL; // �˻�� ����
	}

	// ����� ������ ���ڿ� �����Ҵ�
	int length = strsize + Changesize - Searchsize;
	char* result = new char[length];
	for (int i = 0; i < strsize; i++) result[i] = str[i]; //str ���뺹��
	result[length] = NULL; // ���ڿ� ������ NULL����

	int k = (Changesize > Searchsize) ? Searchsize : Changesize;

	// �������� �ڷ� �з����� ���� �̵�
	for (int i = length - 1; i >= p + k; i--)
		result[i] = str[i - Changesize + Searchsize];

	// strChange ����
	for (int i = 0; i < Changesize; i++)
		result[p + i] = strChange[i];

	return result;
}

int main(void)
{
	char str[100], strSearch[100], strChange[100];
	char* result;

	// ���ڿ� �Է�
	cout << "���� ���ڿ��� �Է��ϼ���." << endl;
	cin.getline(str, 100);
	cout << endl << "���� �� ���ڿ��� �Է��ϼ���." << endl;
	cin.getline(strSearch, 100);
	cout << endl << "���� �� ���ڿ��� �Է��ϼ���." << endl;
	cin.getline(strChange, 100);

	// my_strstr �Լ� ȣ��
	result = my_strstr(str, strSearch, strChange);

	// ��� ���
	cout << endl << "����� ����� ������ �����ϴ�." << endl << endl;
	if (result)
		cout << "����� ���ڿ�:" << endl << result << endl;
	else
		cout << "��ġ�ϴ� ���ڿ��� �����ϴ�." << endl;
	return 0;
}
