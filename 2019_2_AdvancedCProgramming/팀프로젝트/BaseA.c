#include "BaseBall.h"

int T = 0; //Try함수 호출 횟수 저장

void Menu2(void)
{
	int score = 0; //게임 횟수 저장
	int rep ; //다시하기 메뉴 선택
	int at[20] = { 0 }; //각 게임의 T를 저장하는 배열
	int Ma=0, mi=10, si; //T의 최대, 최소 저장
	double av = 0; //T의 평균값

	BaseA(&score);
	at[score - 1] = T; //at배열에 T값 저장
	T = 0;

	while (1)
	{
		rep = 0;
		printf("┌────────────────────────────────────────┐ \n");
		printf("│           야구게임 문제내기            │ \n");
		printf("│                                        │ \n");
		printf("│              (1)계속하기               │ \n");
		printf("│              (2)그만하기               │ \n");
		printf("└────────────────────────────────────────┘ \n  >>>  ");

		scanf("%d", &rep); //메뉴 입력받음
		while (getchar() != '\n'); //입력버퍼 비움

		if (rep == 1)
		{
			BaseA(&score);
			at[score - 1] = T;
			T = 0;
		}
			
		else if (rep == 2)
			break;
		else
		{
			system("cls");
			printf("┌────────────────────────────────────────┐ \n");
			printf("│           잘못 입력하셨습니다.         │ \n");
			printf("│            다시 입력해주세요.          │ \n");
		}
	}
	system("cls");
	//at[20]에 저장된 요소들의 평균, 최대 최소 구해서 출력
	for (si = 0; at[si]!=0; si++)
	{
		av += at[si];
		mi = (at[si] < mi) ? at[si] : mi;
		Ma = (at[si] > Ma) ? at[si] : Ma;
	}
	av = av / score;

	printf("┌────────────────────────────────────────┐ \n");
	printf("│              총시행 %2d 회              │ \n", score);
	if (si != 1)
	{
		printf("│             최대시행 %2d 회             │\n", Ma);
		printf("│             최소시행 %2d 회             │   \n", mi);
		printf("│            평균시행 %1.2lf 회            │   \n", av);
	}
	else //score==1일때만 출력
		printf("│              시행수 %2d 회              │\n", Ma);
	printf("└────────────────────────────────────────┘ \n");
	printf("│  - Enter를 누르면 메뉴로 돌아갑니다. - │ \n");
	printf("└────────────────────────────────────────┘ \n");
	while (getchar() != '\n');//엔터 입력받음
	system("cls");
	printf("┌────────────────────────────────────────┐ \n");
	return;
}

void BaseA(int * score)
{
	char i,j,k=0; // for문에 사용
	char trc=0; // BAST의 행번호

	int arr[3][3] = { {7,8,9},{4,5,6},{1,2,3} }; //전체 수의 배열 {{a1,a2,a3},{b1,b2,b3},{c1,c2,c3}}
	int bast[10][5] = { {7,8,9},{4,5,6} }; //시행 결과를 저장할 배열, 최초 2회 시행할 값 저장
	int BS = 0; //판정 시행 후 스트라이크와 볼의 합

	system("cls");

	for (i = 0; i < 2; i++) //최초 2회 시행
	{
		trc++;
		BS = Try(trc - 1, bast);
		if (BS == 0)
		{
			if (trc == 1) // a1,a2,a3 의 BS값이 0일 때 arr에서 a1,a2,a3제거
			{
				for (j = 0; j < 3; j++) 
					arr[0][j] = 0;
			}
			else if (trc == 2) // b1,b2,b3 의 BS값이 0일때 arr에서 b1,b2,b3제거
			{
				for (j = 0; j < 3; j++)
					arr[1][j] = 0;
			}
		}
		else if (BS == 3)//(a,a,a), (b,b,b)인 경우
		{
			for (j = 0; j < 3; j++) // c1,c2,c3 제거
				arr[2][j] = 0;
			if (trc == 1) //(a,a,a)일때 b1,b2,b3 제거
			{
				for (j = 0; j < 3; j++)
					arr[1][j] = 0;
				break;
			}
		}
		else if (bast[0][3] + bast[0][4] + bast[1][3] + bast[1][4] == 3) //a,b행에 3개의 숫자가 모두 나타남
		{// 1,2 회 실행을 통해 c1,c2,c3 제거 가능한 상황
			for (j = 0; j < 3; j++)
				arr[2][j] = 0;
		}
	}

	if (arr[0][0] == arr[1][0]) // (c,c,c)인 경우
		BS = 3;

	ReAr(arr,bast); //수열 재배치

	while (BS != 3) //숫자 3개를 찾는 과정
	{

		SetP(trc, BS,arr,bast);//다음 시행할 수를 저장하는 함수
		if ((bast[trc][3] + bast[trc][4] == 6)) //직전 시행을 통해 시행 없이 수를 알아낸 경우
		{
			trc++;
			break;
		}
		BS = Try(trc, bast);//bast[trc][3,4]에 볼,슽 저장, BS합 반환
		trc++;
	}

	if ((bast[trc-1][3] == 3)&&(bast[trc-1][4]!=3)) 
	{//bast에 3s가 저장되어 이미 시행한 경우
		for (i = 0; i < 3; i++)
			bast[9][i] = bast[trc - 1][i];
	}
	else
		FinP(trc-1,bast); //추가 시행 후 3s인 경우 종료

	printf("┌────────────────────────────────────────┐ \n");
	printf("│              시행수 %2d 회              │ \n", T);
	printf("└────────────────────────────────────────┘ \n");

	*score += 1; //게임실행횟수 증가
	return;
}

int Try(int trc,int bast[10][5])  //시행, 결과저장, BS합 반환
{
	int a=3; //bast배열에 저장
	char str[30]; // 문자열 입력받음
	int s, i;
	char k; //문자열의 문자저장

	T++;//Try함수 호출 회수


	printf("┌────────────────────────────────────────┐ \n");
	printf("│    %d.          %d %d %d                   │ \n", T, bast[trc][0], bast[trc][1], bast[trc][2]);
	printf("└────────────────────────────────────────┘ \n  >>>  ");

	fgets(str, sizeof(str), stdin);
	s = strlen(str); //문자열 길이

	for (i = 0; i < s; i++)
	{
		k = str[i];
		if (((atoi(&str[i]) != 0) && (k != ' ')) || (k == '0'))
		{
			if (a == 3)
			{
				bast[trc][a] = atoi(&str[i]);
				a++;
			}
			else
				bast[trc][4] = atoi(&str[i]);
		}
	}
	return bast[trc][3]+bast[trc][4]; //BS값 반환
}

void ReAr(int arr[3][3], int bast[10][5]) //수열재배치
{
	char i, j;
	int sum;
	int v[3] = { 0,0,0 }; //현재 수가 들어있는 행을 찾음
	int t[3] = { 1,2,3 }; //arr[0]행에 저장할 값
	int r[3] = { 1,2,3 }; //(a,c,c)인 경우 예외 처리하기 위한 초기화값

	for (i = 0; i < 3; i++) //v에 각행의 합 저장 // 빈배열:0
	{
		for (j = 0; j < 3; j++)
			v[i] += arr[i][j];
	}
	j = 0;
	for (i = 0; i < 3; i++) //수가 들어있는 행 개수 구함
	{
		if (v[i] != 0)
			j++;
	}
	switch (j)
	{
	case 1: //하나의 행에만 수가 있는 경우
		for (i = 1; i < 3; i++)
		{
			for (j = 0; j < 3; j++) // 수를 arr[0]에 복사
			{
				if (v[i] != 0)
					arr[0][j] = arr[i][j];
			}
		}
		for (i = 0; i < 3; i++) //arr[0]을 제외하고 0 저장
		{
			arr[1][i] = 0;
			arr[2][i] = 0;
		}
		break;
	case 2: //2개의 행에 수가 있는 경우
		for (i = 0; i < 2; i++)
		{
			sum = bast[i][3] + bast[i][4]; //sum = 각 행의 BS값

			switch (sum)
			{
			case 1: //BS값이 1인 경우
				for (j = 0; j < 3; j++) 
					t[j] = arr[i][j];//arr[1]에 저장하기 위함
				break;
			case 2: //BS값이 2인 경우
				for (j = 0; j < 3; j++)
					r[j] = arr[i][j]; //arr[0]에 저장하기 위함
				break;
			case 3: //BS값이 3인 경우 ({{0,0,0},{4,5,6},{7,8,9}})
				for (j = 0; j < 3; j++)
					t[j] = j + 1; //arr[1]에 4,5,6 저장
				break;
			}
		}
		for (i = 0; i < 3; i++)
		{
			arr[0][i] = r[i]; //arr[0]에 BS가 2인 행의 값 저장
			arr[1][i] = t[i]; //arr[1]에 BS가 1인 행의 값 저장
			arr[2][i] = 0; //arr[2]에 {0,0,0}저장
			if (arr[0][i] == arr[1][i]) // (a,a,c)인 경우 예외처리
				arr[1][i] = 7 + i;
		}
		break;
	case 3: //3개의 행에 수가 있는 경우 재정렬하지 않음
		break;
	}
	return;
}

void SetP(int trc, int BS, int arr[3][3], int bast[10][5]) // BAST에 다음 시행 값 복사
{
	int i;
	int *p;

	//각 경우 뒤에 붙는 숫자는 이전 시행의 BS값

	//A~ (a,b,c) 인 경우
	int A[3] = { arr[2][2],arr[0][0],arr[0][1] }, A0[3] = { arr[1][2],arr[1][0],arr[2][1] },
		A00[3] = { arr[0][2],arr[2][0],arr[1][1] }, A01[3] = { arr[2][0],arr[0][2],arr[1][0] },
		A011[3] = { arr[2][1],arr[1][1],arr[0][2] }, A012[3] = { arr[1][2],arr[2][0],arr[0][2] },
		A02[3] = { arr[2][1],arr[0][2],arr[1][0] }, A022[3] = { arr[1][2],arr[2][1],arr[0][2] },

		A1[3] = { arr[0][2],arr[2][2],arr[1][0] }, A10[3] = { arr[2][0],arr[0][0],arr[1][1] },
		A100[3] = { arr[0][1],arr[1][2],arr[2][1] }, A101[3] = { arr[1][2],arr[2][1],arr[0][0] },
		A1011[3] = { arr[1][1],arr[2][1],arr[0][1] }, A10111[3] = { arr[0][1],arr[1][2],arr[2][0] },
		A102[3] = { arr[1][1],arr[0][0],arr[2][1] }, A1021[3] = { arr[2][0],arr[1][2],arr[0][0] },
		A10211[3] = { arr[0][1],arr[1][1],arr[2][0] },

		A11[3] = { arr[2][0],arr[1][0],arr[0][0] }, A111[3] = { arr[0][1],arr[2][1],arr[1][0] },
		A112[3] = { arr[0][0],arr[2][1],arr[1][0] }, A1121[3] = { arr[0][1],arr[2][0],arr[1][0] },
		A12[3] = { arr[1][1],arr[0][2],arr[2][2] },A122[3] = { arr[1][2],arr[0][2],arr[2][2] },

		A2[3] = { arr[0][1],arr[1][2],arr[1][0] },A20[3] = { arr[1][1],arr[0][0],arr[2][2] },
		A21[3] = { arr[2][2],arr[1][0],arr[0][0] },A211[3] = { arr[0][1],arr[1][1],arr[2][2] },
		A212[3] = { arr[1][2],arr[0][0],arr[2][2] },A22[3] = { arr[0][1],arr[1][0],arr[2][2] },
		A222[3] = { arr[1][2],arr[0][1],arr[2][2] };

	//B~ (a,a,b) 인 경우
	int B[3] = { arr[1][2],arr[0][0],arr[0][1] },B1[3] = { arr[0][2],arr[1][0],arr[0][0] },
		B11[3] = { arr[0][1],arr[1][1],arr[0][2] },B12[3] = { arr[0][0],arr[0][2],arr[1][1] },
		B121[3] = { arr[0][1],arr[1][0],arr[0][2] },

		B2[3] = { arr[0][2],arr[1][2],arr[0][0] },B21[3] = { arr[0][1],arr[1][0],arr[0][0] },
		B22[3] = { arr[0][1],arr[0][2],arr[1][2] },B212[3] = { arr[1][1],arr[0][0],arr[0][1] };
		
	//C~ (a,a,a) 인 경우
	int C[3] = { arr[0][0],arr[0][1],arr[0][2] };


	if (arr[1][0] == 0) //(aaa)(bbb)(ccc), C인 경우
			p = C;

	////////////////////////////////////////

	else if (((trc + 1) == 3) && (arr[2][0] != 0)) // A 실행조건
		p = A;

	else if (((trc + 1) == 4) && (bast[trc - 1][0] == A[0]) && (bast[trc - 1][1] == A[1])) // A 실행 후 결과처리
	{
		if (BS == 0)
			p = A0;
		else if (BS == 1)
			p = A1;
		else // (BS == 2)
			p = A2;
	}

	///////////////////////////////////// A0

	else if (((trc + 1) == 5) && (bast[trc - 1][0] == A0[0]) && (bast[trc - 1][1] == A0[1])) // A0 실행 후 결과처리
	{
		if (BS == 0) //3bs 저장
		{
			p = A00;
			bast[trc][3] = 3;
			bast[trc][4] = 3;
		}
		else if (BS == 1)
			p = A01;
		else //(BS == 2)
			p = A02;
	}

	else if (((trc + 1) == 6) && (bast[trc - 1][0] == A01[0]) && (bast[trc - 1][1] == A01[1])) // A01 실행 후 결과처리
	{
		if (BS == 1) //3bs 저장
		{
			p = A011;
			bast[trc][3] = 3;
			bast[trc][4] = 3;
		}

		else // (BS == 2)
		{
			p = A012;
			bast[trc][3] = 3;
			bast[trc][4] = 3;
		}
	}

	else if (((trc + 1) == 6) && (bast[trc - 1][0] == A02[0]) && (bast[trc - 1][1] == A02[1])) // A02 실행 후 결과처리
	{
		p = A022;
		bast[trc][3] = 3;
		bast[trc][4] = 3;
	}

	///////////////////////////////////// A1

	else if (((trc + 1) == 5) && (bast[trc - 1][0] == A1[0]) && (bast[trc - 1][1] == A1[1])) // A1 실행 후 결과처리
	{
		if (BS == 0)
			p = A10;
		else if (BS == 1)
			p = A11;
		else //(BS == 2)
			p = A12;
	}

	else if (((trc + 1) == 6) && (bast[trc - 1][0] == A10[0]) && (bast[trc - 1][1] == A10[1])) // A10 실행 후 결과처리
	{
		if (BS == 0) 
		{// 결과처리를 통해 숫자를 모두 알아낸 경우 bast[trc][3]과 bast[trc][4]에 모두 3 저장
			p = A100;
			bast[trc][3] = 3;
			bast[trc][4] = 3;
		}
		else if (BS == 1)
			p = A101;
		else if (BS == 2)
			p = A102;
	}

	else if (((trc + 1) == 7) && (bast[trc - 1][0] == A101[0]) && (bast[trc - 1][1] == A101[1])) // A101 실행 후 결과처리
		p = A1011;

	else if (((trc + 1) == 8) && (bast[trc - 1][0] == A1011[0]) && (bast[trc - 1][1] == A1011[1])) // A1011 실행 후 결과처리
	{
		p = A10111;
		bast[trc][3] = 3;
		bast[trc][4] = 3;
	}

	else if (((trc + 1) == 7) && (bast[trc - 1][0] == A102[0]) && (bast[trc - 1][1] == A102[1])) // A102 실행 후 결과처리
		p = A1021;

	else if (((trc + 1) == 8) && (bast[trc - 1][0] == A1021[0]) && (bast[trc - 1][1] == A1021[01])) // A1021 실행 후 결과처리
	{
		p = A10211;
		bast[trc][3] = 3;
		bast[trc][4] = 3;
	}

	else if (((trc + 1) == 6) && (bast[trc - 1][0] == A11[0]) && (bast[trc - 1][1] == A11[1])) // A11 실행 후 결과처리
	{
		if (BS == 1)
		{
			p = A111;
			bast[trc][3] = 3;
			bast[trc][4] = 3;
		}
		else
			p = A112;
	}

	else if (((trc + 1) == 7) && (bast[trc - 1][0] == A112[0]) && (bast[trc - 1][1] == A112[1])) // A112 실행 후 결과처리
	{
		p = A1121;
		bast[trc][3] = 3;
		bast[trc][4] = 3;
	}

	else if (((trc + 1) == 6) && (bast[trc - 1][0] == A12[0]) && (bast[trc - 1][1] == A12[1])) // A12 실행 후 결과처리
	{
		p = A122;
		bast[trc][3] = 3;
		bast[trc][4] = 3;
	}
	///////////////////////////////////// A2

	else if (((trc + 1) == 5) && (bast[trc - 1][0] == A2[0]) && (bast[trc - 1][1] == A2[1])) // A2 실행 후 결과처리
	{
		if (BS == 0)
		{
			p = A20;
			bast[trc][3] = 3;
			bast[trc][4] = 3;
		}
		else if (BS == 1)
			p = A21;
		else //(BS == 2)
			p = A22;
	}

	else if (((trc + 1) == 6) && (bast[trc - 1][0] == A21[0]) && (bast[trc - 1][1] == A21[1])) // A21 실행 후 결과처리
	{
		if (BS == 1)
		{
			p = A211;
			bast[trc][3] = 3;
			bast[trc][4] = 3;
		}

		else // (BS == 2)
		{
			p = A212;
			bast[trc][3] = 3;
			bast[trc][4] = 3;
		}
	}

	else if (((trc + 1) == 6) && (bast[trc - 1][0] == A22[0]) && (bast[trc - 1][1] == A22[1])&&(bast[trc-1][2]==A22[2])) // A22 실행 후 결과처리
	{
		p = A222;
		bast[trc][3] = 3;
		bast[trc][4] = 3;
	}

	

	else if (((trc+1) == 3) && (arr[2][0] == 0)) // B 실행조건
		p = B;

	else if (((trc + 1) == 4) && (bast[trc - 1][0] == B[0]) && (bast[trc - 1][1] == B[1])) // B 실행 후 결과처리
	{
		if(BS==1)
			p = B1;
		else //(BS==2)
			p = B2;
	}

	///////////////////////////////////// B1

	else if (((trc + 1) == 5) && (bast[trc - 1][0] == B1[0]) && (bast[trc - 1][1] == B1[1])) // B1 실행 후 결과처리
	{
		if (BS == 1)
		{
			p = B11;
			bast[trc][3] = 3;
			bast[trc][4] = 3;
		}
		else // (BS == 2)
			p = B12;
	}

	else if (((trc + 1) == 6) && (bast[trc - 1][0] == B12[0]) && (bast[trc - 1][1] == B12[1])) // B12 실행 후 결과처리
	{
		p = B121;
		bast[trc][3] = 3;
		bast[trc][4] = 3;
	}

	///////////////////////////////////// B2

	else if (((trc + 1) == 5) && (bast[trc - 1][0] == B2[0]) && (bast[trc - 1][1] == B2[1])) // B2 실행 후 결과처리
	{
		if (BS == 1)
			p = B21;
		else // (BS == 2)
		{
			p = B22;
			bast[trc][3] = 3;
			bast[trc][4] = 3;
		}
	}

	else if (((trc + 1) == 6) && (bast[trc - 1][0] == B21[0]) && (bast[trc - 1][1] == B21[1])) // B21 실행 후 결과처리
	{
		p = B212;
		bast[trc][3] = 3;
		bast[trc][4] = 3;
	}

	else
		printf("오류발생");

	for (i = 0; i < 3; i++)  //bast에 다음 시행할 값 복사
		bast[trc][i] = p[i];

	return;
}

void FinP(int trc, int bast[10][5]) //순서를 찾는 함수
{
	int i,j,k=0,t,s,a=0;
	int ball[3][10][3] = { 0 };
	int stri[3][10][3] = { 0 };

	// 볼과 스트라이크의 위치를 배열에 저장하는 반복문
	for (i = 0; i < 3; i++) //i는 페이지
	{
		for (j = 0; j <= trc; j++)//j는 행
		{
			for (k = 0; k < 3; k++)//k는 열
			{
				if ((bast[j][3] != 0) && (bast[j][4] != 0)) //볼과 스트라이크가 모두 있는 경우
					break;
				else if ((bast[j][3] == 0) && (bast[j][4] == 0)) //볼과 스트라이크가 모두 없는 경우
					break;
				else if (bast[trc][i] == bast[j][k]) //볼과 스트라이크중 하나만 남은 경우
					(bast[j][4] == 0) ? (stri[i][j][k] = bast[trc][i]) : (ball[i][j][k] = bast[trc][i]);
			}
		}
	}

	//스트라이크 배열 자리확정
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j <= trc; j++)
		{
			for (k = 0; k < 3; k++)
			{//스트라이크가 있는 경우 bast의 9행, 해당하는 자리에 복사
				if (stri[i][j][k] != 0) 
					bast[9][k] = stri[i][j][k];
			}
		}
	}

	s = 0;//확정된 자리 수의 개수 저장
	for (i = 0; i < 3; i++)
	{
		if (bast[9][i] != 0) //s에 자리가 확정된 수의 개수 저장
			s++;
	}

	//자리조합 후 3s일때 마지막 시행
	for (t = 0; t < 2; t++)
	{
		if (s == 3)//3s이면 마지막 시행 후 리턴
		{
			trc++;
			for (i = 0; i < 3; i++)
				bast[trc][i] = bast[9][i];
			Try(trc, bast);//마지막시행
			return;
		}
		else if (s == 2)
		{//숫자 2개가 확정되면 나머지 하나도 자동 확정
			for (i = 0; i < 3; i++) //a에 빈칸 저장
			{
				if (bast[9][i] == 0)
					a = i;
			}
			k = 0;
			for (i = 0; i < 3; i++)//k에 남은 숫자 저장
			{
				k = 0;
				for (j = 0; j < 3; j++)
				{
					if (bast[trc][i] == bast[9][j])
						break;
					else
						k++;
				}
				if ((k == 3)&&(j==3))
				{
					k = bast[trc][i];
					break;
				}
			}
			bast[9][a] = k; //빈칸에 남은 수 저장
			trc++;
			for (i = 0; i < 3; i++)
				bast[trc][i] = bast[9][i];
			Try(trc, bast); //마지막시행
			return;
		}
		else //s==1or s==0
		{//ball을 이용해서 자리 확정
			for (i = 0; i < 3; i++) 
			{
				for (k = 0; k < 3; k++)
				{
					for (j = 0; j <=trc; j++)
						ball[i][9][k] += ball[i][j][k];
				}//ball의 각 열의 합 ball[i][9][k]에 각각 저장
			}
			for (i = 0; i < 3; i++)
			{
				j = 0;
				for (k = 0; k < 3; k++)
				{
					if (ball[i][9][k] != 0)//j에 볼 자리 수 저장
						j++;
					else
						s = k; //s에 빈 자리 저장
				}
				if (j == 2) //볼이 2자리에서 나타난 경우 위치 확정
					bast[9][s] = bast[trc][i];
			}

			s = 0;//확정된 자리 수의 개수 저장
			for (i = 0; i < 3; i++)
			{
				if (bast[9][i] != 0) //s에 자리가 확정된 수의 개수 저장
					s++;
			}
			if (s < 2) // 확정된 자리가 0또는 1일때 추가시행
			{
				SetC(s, trc, bast);//다음 시행할 수 저장하는 함수
				trc++;
				Try(trc, bast); //순서를 찾기 위한 추가시행
				if (bast[trc][3] == 3)
					return; //추가시행에서 3s인 경우
				else
				{// 추가시행 이후 FinP함수 다시 호출
					FinP( trc,bast); 
					return;
				}
			}
		}
	}
	return;
}

void SetC(int s, int trc, int bast[10][5]) //s = 지금까지 확정된 자리 수 (0 또는 1)
{
	int i,j,k;
	int b[3] = { bast[trc][0],bast[trc][1],bast[trc][2] }; //bast[trc][0,1,2]의 수를 b에 저장
	int x, y; //(1s2b),(0s3b) 시행한 행을 찾음

	//1,2회 시행에서 BS 모두 0인 경우
	if ((bast[0][3] + bast[0][4] == 0) && (bast[1][3] + bast[1][4] == 0)) 
	{//(c,c,c)인 경우 해당하는 수 다음 판정시행
		bast[trc + 1][0] = 1;
		bast[trc + 1][1] = 2;
		bast[trc + 1][2] = 3;
		bast[0][3] = 5;
		bast[0][4] = 5;
		bast[1][3] = 5;
		bast[1][4] = 5;
		return;
	}

	for (x = 0; x <= trc; x++) //x는 1s2b의 시도가 저장된 행 (여러개일 경우 가장 앞의 시도)
	{
		if ((bast[x][3] == 1) && (bast[x][4] == 2))
			break;
	}
	for (y = 0; y <= trc; y++)//y는 0s3b의 시도가 저장된 행 (여러개일 경우에 가장 앞의 시도)
	{
		if ((bast[y][3] == 0) && (bast[y][4] == 3))
			break;
	}

	if (s == 1) //확정된 수가 하나 있는 경우
	{//bast[trc+1][0,1,2]에 다음 시행할 수 저장
		for (i = 0; i < 3; i++)
		{
			if (bast[9][i] != 0) //i는 확정된 한자리의 위치
				break;
		}

		bast[trc + 1][i] = bast[9][i]; //확정된 한자리를 다음에 시도할 행에 저장
		for (j = 0; j < 3; j++)
			b[j] = (b[j] == bast[9][i]) ? (0) : (b[j]); //자리가 확정된 수 b배열에서 제거

		if (y != trc+1) //한 자리가 확정이고, (0s3b)시행이 있는 경우 3s를 확정
		{
			k = (i == 2) ? (0) : (i + 1); //i가 0이면 k는 1, 1이면 2, 2이면 0
			if (bast[trc + 1][i] == bast[y][k])
			{
				bast[trc + 1][0] = bast[y][1];
				bast[trc + 1][1] = bast[y][2];
				bast[trc + 1][2] = bast[y][0];
			}
			else
			{
				bast[trc + 1][0] = bast[y][2];
				bast[trc + 1][1] = bast[y][0];
				bast[trc + 1][2] = bast[y][1];
			}
		}
		else if (x != trc+1) //한 자리가 확정이고, (1s 2b) 시행이 있는 경우 3s를 확정
		{
			if (bast[trc + 1][0] == bast[x][0])
			{
				bast[trc + 1][0] = bast[x][0];
				bast[trc + 1][1] = bast[x][2];
				bast[trc + 1][2] = bast[x][1];
			}
			else if (bast[trc + 1][0] == bast[x][1])
			{
				bast[trc + 1][0] = bast[x][1];
				bast[trc + 1][1] = bast[x][0];
				bast[trc + 1][2] = bast[x][2];
			}
			else // (bast[trc + 1][0] == bast[x][2])
			{
				bast[trc + 1][0] = bast[x][2];
				bast[trc + 1][1] = bast[x][1];
				bast[trc + 1][2] = bast[x][0];
			}
		}
		else //(0,3),(1,2) 둘다 없는 경우 (1s2b)또는 (3s0b) 
		{// (1,2) 가 나오면 남은 한가지 경우의수가 3S
			//다음 시행할 수 저장, 확정된 자리 외 임의 저장
			if (i == 0)
			{
				for (j = 0; j < 3; j++)
				{
					if (b[j] == 0);
					else
					{
						if (bast[trc + 1][1] == 0)
							bast[trc + 1][1] = b[j];
						else
							bast[trc + 1][2] = b[j];
					}
				}
			}
			else if (i == 1)
			{
				for (j = 0; j < 3; j++)
				{
					if (b[j] == 0);
					else
					{
						if (bast[trc + 1][0] == 0)
							bast[trc + 1][0] = b[j];
						else
							bast[trc + 1][2] = b[j];
					}
				}
			}
			else // (i == 2)
			{
				for (j = 0; j < 3; j++)
				{
					if (b[j] == 0);
					else
					{
						if (bast[trc + 1][0] == 0)
							bast[trc + 1][0] = b[j];
						else
							bast[trc + 1][1] = b[j];
					}
				}
			}
		}
	}
	else //s==0 확정된 수가 하나도 없는 경우
	{
		if(y!=trc+1)
		{//3b가 있는 경우 경우의 수는 2가지임 (한 가지 임의 시행)
			bast[trc + 1][0] = bast[y][1];
			bast[trc + 1][1] = bast[y][2];
			bast[trc + 1][2] = bast[y][0];
		}//trc+1의 시행 결과는 (3,0) 또는 (3,0이 아님)
		else if(x!=trc+1)
		{//1s2b이 있는 경우 경우의 수는 3가지임 (한 가지 임의 시행)
			bast[trc + 1][0] = bast[x][0];
			bast[trc + 1][1] = bast[x][2];
			bast[trc + 1][2] = bast[x][1];
		}//trc+1의 시행 결과는 (3,0) 또는 (0,3)
		else
		{//시행 없이 3BS를 알아낸 경우 (시행을 통해 정보를 더 받음)
			bast[trc + 1][0] = bast[trc][0];
			bast[trc + 1][1] = bast[trc][1];
			bast[trc + 1][2] = bast[trc][2];
		}//trc+1의 시행 결과는 (3,0),(1,2),(0,3)
	}
	return;
}
