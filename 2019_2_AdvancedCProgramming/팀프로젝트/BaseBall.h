#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h> 


void Menu1(void);
void BaseQ(char *score);

void Menu2(void);
void BaseA(int * score); //�����Լ�
int Try(int trc, int bast[10][5]); //����, �������, BS�� ��ȯ
void ReAr(int arr[3][3], int bast[10][5]); // �������ġ
void SetP(int trc, int BS, int arr[3][3], int bast[10][5]); //���� ������ ���� bast[trc][0,1,2]�� ����
void FinP(int trc, int bast[10][5]); // ������ ���ϴ� �Լ�
void SetC(int s, int trc, int bast[10][5]);

void Menu3(void);