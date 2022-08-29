#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h> 


void Menu1(void);
void BaseQ(char *score);

void Menu2(void);
void BaseA(int * score); //실행함수
int Try(int trc, int bast[10][5]); //시행, 결과저장, BS합 반환
void ReAr(int arr[3][3], int bast[10][5]); // 수열재배치
void SetP(int trc, int BS, int arr[3][3], int bast[10][5]); //다음 시행할 수를 bast[trc][0,1,2]에 저장
void FinP(int trc, int bast[10][5]); // 순서를 정하는 함수
void SetC(int s, int trc, int bast[10][5]);

void Menu3(void);