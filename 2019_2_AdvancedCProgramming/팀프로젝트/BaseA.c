#include "BaseBall.h"

int T = 0; //Try�Լ� ȣ�� Ƚ�� ����

void Menu2(void)
{
	int score = 0; //���� Ƚ�� ����
	int rep ; //�ٽ��ϱ� �޴� ����
	int at[20] = { 0 }; //�� ������ T�� �����ϴ� �迭
	int Ma=0, mi=10, si; //T�� �ִ�, �ּ� ����
	double av = 0; //T�� ��հ�

	BaseA(&score);
	at[score - 1] = T; //at�迭�� T�� ����
	T = 0;

	while (1)
	{
		rep = 0;
		printf("������������������������������������������������������������������������������������ \n");
		printf("��           �߱����� ��������            �� \n");
		printf("��                                        �� \n");
		printf("��              (1)����ϱ�               �� \n");
		printf("��              (2)�׸��ϱ�               �� \n");
		printf("������������������������������������������������������������������������������������ \n  >>>  ");

		scanf("%d", &rep); //�޴� �Է¹���
		while (getchar() != '\n'); //�Է¹��� ���

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
			printf("������������������������������������������������������������������������������������ \n");
			printf("��           �߸� �Է��ϼ̽��ϴ�.         �� \n");
			printf("��            �ٽ� �Է����ּ���.          �� \n");
		}
	}
	system("cls");
	//at[20]�� ����� ��ҵ��� ���, �ִ� �ּ� ���ؼ� ���
	for (si = 0; at[si]!=0; si++)
	{
		av += at[si];
		mi = (at[si] < mi) ? at[si] : mi;
		Ma = (at[si] > Ma) ? at[si] : Ma;
	}
	av = av / score;

	printf("������������������������������������������������������������������������������������ \n");
	printf("��              �ѽ��� %2d ȸ              �� \n", score);
	if (si != 1)
	{
		printf("��             �ִ���� %2d ȸ             ��\n", Ma);
		printf("��             �ּҽ��� %2d ȸ             ��   \n", mi);
		printf("��            ��ս��� %1.2lf ȸ            ��   \n", av);
	}
	else //score==1�϶��� ���
		printf("��              ����� %2d ȸ              ��\n", Ma);
	printf("������������������������������������������������������������������������������������ \n");
	printf("��  - Enter�� ������ �޴��� ���ư��ϴ�. - �� \n");
	printf("������������������������������������������������������������������������������������ \n");
	while (getchar() != '\n');//���� �Է¹���
	system("cls");
	printf("������������������������������������������������������������������������������������ \n");
	return;
}

void BaseA(int * score)
{
	char i,j,k=0; // for���� ���
	char trc=0; // BAST�� ���ȣ

	int arr[3][3] = { {7,8,9},{4,5,6},{1,2,3} }; //��ü ���� �迭 {{a1,a2,a3},{b1,b2,b3},{c1,c2,c3}}
	int bast[10][5] = { {7,8,9},{4,5,6} }; //���� ����� ������ �迭, ���� 2ȸ ������ �� ����
	int BS = 0; //���� ���� �� ��Ʈ����ũ�� ���� ��

	system("cls");

	for (i = 0; i < 2; i++) //���� 2ȸ ����
	{
		trc++;
		BS = Try(trc - 1, bast);
		if (BS == 0)
		{
			if (trc == 1) // a1,a2,a3 �� BS���� 0�� �� arr���� a1,a2,a3����
			{
				for (j = 0; j < 3; j++) 
					arr[0][j] = 0;
			}
			else if (trc == 2) // b1,b2,b3 �� BS���� 0�϶� arr���� b1,b2,b3����
			{
				for (j = 0; j < 3; j++)
					arr[1][j] = 0;
			}
		}
		else if (BS == 3)//(a,a,a), (b,b,b)�� ���
		{
			for (j = 0; j < 3; j++) // c1,c2,c3 ����
				arr[2][j] = 0;
			if (trc == 1) //(a,a,a)�϶� b1,b2,b3 ����
			{
				for (j = 0; j < 3; j++)
					arr[1][j] = 0;
				break;
			}
		}
		else if (bast[0][3] + bast[0][4] + bast[1][3] + bast[1][4] == 3) //a,b�࿡ 3���� ���ڰ� ��� ��Ÿ��
		{// 1,2 ȸ ������ ���� c1,c2,c3 ���� ������ ��Ȳ
			for (j = 0; j < 3; j++)
				arr[2][j] = 0;
		}
	}

	if (arr[0][0] == arr[1][0]) // (c,c,c)�� ���
		BS = 3;

	ReAr(arr,bast); //���� ���ġ

	while (BS != 3) //���� 3���� ã�� ����
	{

		SetP(trc, BS,arr,bast);//���� ������ ���� �����ϴ� �Լ�
		if ((bast[trc][3] + bast[trc][4] == 6)) //���� ������ ���� ���� ���� ���� �˾Ƴ� ���
		{
			trc++;
			break;
		}
		BS = Try(trc, bast);//bast[trc][3,4]�� ��,�� ����, BS�� ��ȯ
		trc++;
	}

	if ((bast[trc-1][3] == 3)&&(bast[trc-1][4]!=3)) 
	{//bast�� 3s�� ����Ǿ� �̹� ������ ���
		for (i = 0; i < 3; i++)
			bast[9][i] = bast[trc - 1][i];
	}
	else
		FinP(trc-1,bast); //�߰� ���� �� 3s�� ��� ����

	printf("������������������������������������������������������������������������������������ \n");
	printf("��              ����� %2d ȸ              �� \n", T);
	printf("������������������������������������������������������������������������������������ \n");

	*score += 1; //���ӽ���Ƚ�� ����
	return;
}

int Try(int trc,int bast[10][5])  //����, �������, BS�� ��ȯ
{
	int a=3; //bast�迭�� ����
	char str[30]; // ���ڿ� �Է¹���
	int s, i;
	char k; //���ڿ��� ��������

	T++;//Try�Լ� ȣ�� ȸ��


	printf("������������������������������������������������������������������������������������ \n");
	printf("��    %d.          %d %d %d                   �� \n", T, bast[trc][0], bast[trc][1], bast[trc][2]);
	printf("������������������������������������������������������������������������������������ \n  >>>  ");

	fgets(str, sizeof(str), stdin);
	s = strlen(str); //���ڿ� ����

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
	return bast[trc][3]+bast[trc][4]; //BS�� ��ȯ
}

void ReAr(int arr[3][3], int bast[10][5]) //�������ġ
{
	char i, j;
	int sum;
	int v[3] = { 0,0,0 }; //���� ���� ����ִ� ���� ã��
	int t[3] = { 1,2,3 }; //arr[0]�࿡ ������ ��
	int r[3] = { 1,2,3 }; //(a,c,c)�� ��� ���� ó���ϱ� ���� �ʱ�ȭ��

	for (i = 0; i < 3; i++) //v�� ������ �� ���� // ��迭:0
	{
		for (j = 0; j < 3; j++)
			v[i] += arr[i][j];
	}
	j = 0;
	for (i = 0; i < 3; i++) //���� ����ִ� �� ���� ����
	{
		if (v[i] != 0)
			j++;
	}
	switch (j)
	{
	case 1: //�ϳ��� �࿡�� ���� �ִ� ���
		for (i = 1; i < 3; i++)
		{
			for (j = 0; j < 3; j++) // ���� arr[0]�� ����
			{
				if (v[i] != 0)
					arr[0][j] = arr[i][j];
			}
		}
		for (i = 0; i < 3; i++) //arr[0]�� �����ϰ� 0 ����
		{
			arr[1][i] = 0;
			arr[2][i] = 0;
		}
		break;
	case 2: //2���� �࿡ ���� �ִ� ���
		for (i = 0; i < 2; i++)
		{
			sum = bast[i][3] + bast[i][4]; //sum = �� ���� BS��

			switch (sum)
			{
			case 1: //BS���� 1�� ���
				for (j = 0; j < 3; j++) 
					t[j] = arr[i][j];//arr[1]�� �����ϱ� ����
				break;
			case 2: //BS���� 2�� ���
				for (j = 0; j < 3; j++)
					r[j] = arr[i][j]; //arr[0]�� �����ϱ� ����
				break;
			case 3: //BS���� 3�� ��� ({{0,0,0},{4,5,6},{7,8,9}})
				for (j = 0; j < 3; j++)
					t[j] = j + 1; //arr[1]�� 4,5,6 ����
				break;
			}
		}
		for (i = 0; i < 3; i++)
		{
			arr[0][i] = r[i]; //arr[0]�� BS�� 2�� ���� �� ����
			arr[1][i] = t[i]; //arr[1]�� BS�� 1�� ���� �� ����
			arr[2][i] = 0; //arr[2]�� {0,0,0}����
			if (arr[0][i] == arr[1][i]) // (a,a,c)�� ��� ����ó��
				arr[1][i] = 7 + i;
		}
		break;
	case 3: //3���� �࿡ ���� �ִ� ��� ���������� ����
		break;
	}
	return;
}

void SetP(int trc, int BS, int arr[3][3], int bast[10][5]) // BAST�� ���� ���� �� ����
{
	int i;
	int *p;

	//�� ��� �ڿ� �ٴ� ���ڴ� ���� ������ BS��

	//A~ (a,b,c) �� ���
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

	//B~ (a,a,b) �� ���
	int B[3] = { arr[1][2],arr[0][0],arr[0][1] },B1[3] = { arr[0][2],arr[1][0],arr[0][0] },
		B11[3] = { arr[0][1],arr[1][1],arr[0][2] },B12[3] = { arr[0][0],arr[0][2],arr[1][1] },
		B121[3] = { arr[0][1],arr[1][0],arr[0][2] },

		B2[3] = { arr[0][2],arr[1][2],arr[0][0] },B21[3] = { arr[0][1],arr[1][0],arr[0][0] },
		B22[3] = { arr[0][1],arr[0][2],arr[1][2] },B212[3] = { arr[1][1],arr[0][0],arr[0][1] };
		
	//C~ (a,a,a) �� ���
	int C[3] = { arr[0][0],arr[0][1],arr[0][2] };


	if (arr[1][0] == 0) //(aaa)(bbb)(ccc), C�� ���
			p = C;

	////////////////////////////////////////

	else if (((trc + 1) == 3) && (arr[2][0] != 0)) // A ��������
		p = A;

	else if (((trc + 1) == 4) && (bast[trc - 1][0] == A[0]) && (bast[trc - 1][1] == A[1])) // A ���� �� ���ó��
	{
		if (BS == 0)
			p = A0;
		else if (BS == 1)
			p = A1;
		else // (BS == 2)
			p = A2;
	}

	///////////////////////////////////// A0

	else if (((trc + 1) == 5) && (bast[trc - 1][0] == A0[0]) && (bast[trc - 1][1] == A0[1])) // A0 ���� �� ���ó��
	{
		if (BS == 0) //3bs ����
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

	else if (((trc + 1) == 6) && (bast[trc - 1][0] == A01[0]) && (bast[trc - 1][1] == A01[1])) // A01 ���� �� ���ó��
	{
		if (BS == 1) //3bs ����
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

	else if (((trc + 1) == 6) && (bast[trc - 1][0] == A02[0]) && (bast[trc - 1][1] == A02[1])) // A02 ���� �� ���ó��
	{
		p = A022;
		bast[trc][3] = 3;
		bast[trc][4] = 3;
	}

	///////////////////////////////////// A1

	else if (((trc + 1) == 5) && (bast[trc - 1][0] == A1[0]) && (bast[trc - 1][1] == A1[1])) // A1 ���� �� ���ó��
	{
		if (BS == 0)
			p = A10;
		else if (BS == 1)
			p = A11;
		else //(BS == 2)
			p = A12;
	}

	else if (((trc + 1) == 6) && (bast[trc - 1][0] == A10[0]) && (bast[trc - 1][1] == A10[1])) // A10 ���� �� ���ó��
	{
		if (BS == 0) 
		{// ���ó���� ���� ���ڸ� ��� �˾Ƴ� ��� bast[trc][3]�� bast[trc][4]�� ��� 3 ����
			p = A100;
			bast[trc][3] = 3;
			bast[trc][4] = 3;
		}
		else if (BS == 1)
			p = A101;
		else if (BS == 2)
			p = A102;
	}

	else if (((trc + 1) == 7) && (bast[trc - 1][0] == A101[0]) && (bast[trc - 1][1] == A101[1])) // A101 ���� �� ���ó��
		p = A1011;

	else if (((trc + 1) == 8) && (bast[trc - 1][0] == A1011[0]) && (bast[trc - 1][1] == A1011[1])) // A1011 ���� �� ���ó��
	{
		p = A10111;
		bast[trc][3] = 3;
		bast[trc][4] = 3;
	}

	else if (((trc + 1) == 7) && (bast[trc - 1][0] == A102[0]) && (bast[trc - 1][1] == A102[1])) // A102 ���� �� ���ó��
		p = A1021;

	else if (((trc + 1) == 8) && (bast[trc - 1][0] == A1021[0]) && (bast[trc - 1][1] == A1021[01])) // A1021 ���� �� ���ó��
	{
		p = A10211;
		bast[trc][3] = 3;
		bast[trc][4] = 3;
	}

	else if (((trc + 1) == 6) && (bast[trc - 1][0] == A11[0]) && (bast[trc - 1][1] == A11[1])) // A11 ���� �� ���ó��
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

	else if (((trc + 1) == 7) && (bast[trc - 1][0] == A112[0]) && (bast[trc - 1][1] == A112[1])) // A112 ���� �� ���ó��
	{
		p = A1121;
		bast[trc][3] = 3;
		bast[trc][4] = 3;
	}

	else if (((trc + 1) == 6) && (bast[trc - 1][0] == A12[0]) && (bast[trc - 1][1] == A12[1])) // A12 ���� �� ���ó��
	{
		p = A122;
		bast[trc][3] = 3;
		bast[trc][4] = 3;
	}
	///////////////////////////////////// A2

	else if (((trc + 1) == 5) && (bast[trc - 1][0] == A2[0]) && (bast[trc - 1][1] == A2[1])) // A2 ���� �� ���ó��
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

	else if (((trc + 1) == 6) && (bast[trc - 1][0] == A21[0]) && (bast[trc - 1][1] == A21[1])) // A21 ���� �� ���ó��
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

	else if (((trc + 1) == 6) && (bast[trc - 1][0] == A22[0]) && (bast[trc - 1][1] == A22[1])&&(bast[trc-1][2]==A22[2])) // A22 ���� �� ���ó��
	{
		p = A222;
		bast[trc][3] = 3;
		bast[trc][4] = 3;
	}

	

	else if (((trc+1) == 3) && (arr[2][0] == 0)) // B ��������
		p = B;

	else if (((trc + 1) == 4) && (bast[trc - 1][0] == B[0]) && (bast[trc - 1][1] == B[1])) // B ���� �� ���ó��
	{
		if(BS==1)
			p = B1;
		else //(BS==2)
			p = B2;
	}

	///////////////////////////////////// B1

	else if (((trc + 1) == 5) && (bast[trc - 1][0] == B1[0]) && (bast[trc - 1][1] == B1[1])) // B1 ���� �� ���ó��
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

	else if (((trc + 1) == 6) && (bast[trc - 1][0] == B12[0]) && (bast[trc - 1][1] == B12[1])) // B12 ���� �� ���ó��
	{
		p = B121;
		bast[trc][3] = 3;
		bast[trc][4] = 3;
	}

	///////////////////////////////////// B2

	else if (((trc + 1) == 5) && (bast[trc - 1][0] == B2[0]) && (bast[trc - 1][1] == B2[1])) // B2 ���� �� ���ó��
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

	else if (((trc + 1) == 6) && (bast[trc - 1][0] == B21[0]) && (bast[trc - 1][1] == B21[1])) // B21 ���� �� ���ó��
	{
		p = B212;
		bast[trc][3] = 3;
		bast[trc][4] = 3;
	}

	else
		printf("�����߻�");

	for (i = 0; i < 3; i++)  //bast�� ���� ������ �� ����
		bast[trc][i] = p[i];

	return;
}

void FinP(int trc, int bast[10][5]) //������ ã�� �Լ�
{
	int i,j,k=0,t,s,a=0;
	int ball[3][10][3] = { 0 };
	int stri[3][10][3] = { 0 };

	// ���� ��Ʈ����ũ�� ��ġ�� �迭�� �����ϴ� �ݺ���
	for (i = 0; i < 3; i++) //i�� ������
	{
		for (j = 0; j <= trc; j++)//j�� ��
		{
			for (k = 0; k < 3; k++)//k�� ��
			{
				if ((bast[j][3] != 0) && (bast[j][4] != 0)) //���� ��Ʈ����ũ�� ��� �ִ� ���
					break;
				else if ((bast[j][3] == 0) && (bast[j][4] == 0)) //���� ��Ʈ����ũ�� ��� ���� ���
					break;
				else if (bast[trc][i] == bast[j][k]) //���� ��Ʈ����ũ�� �ϳ��� ���� ���
					(bast[j][4] == 0) ? (stri[i][j][k] = bast[trc][i]) : (ball[i][j][k] = bast[trc][i]);
			}
		}
	}

	//��Ʈ����ũ �迭 �ڸ�Ȯ��
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j <= trc; j++)
		{
			for (k = 0; k < 3; k++)
			{//��Ʈ����ũ�� �ִ� ��� bast�� 9��, �ش��ϴ� �ڸ��� ����
				if (stri[i][j][k] != 0) 
					bast[9][k] = stri[i][j][k];
			}
		}
	}

	s = 0;//Ȯ���� �ڸ� ���� ���� ����
	for (i = 0; i < 3; i++)
	{
		if (bast[9][i] != 0) //s�� �ڸ��� Ȯ���� ���� ���� ����
			s++;
	}

	//�ڸ����� �� 3s�϶� ������ ����
	for (t = 0; t < 2; t++)
	{
		if (s == 3)//3s�̸� ������ ���� �� ����
		{
			trc++;
			for (i = 0; i < 3; i++)
				bast[trc][i] = bast[9][i];
			Try(trc, bast);//����������
			return;
		}
		else if (s == 2)
		{//���� 2���� Ȯ���Ǹ� ������ �ϳ��� �ڵ� Ȯ��
			for (i = 0; i < 3; i++) //a�� ��ĭ ����
			{
				if (bast[9][i] == 0)
					a = i;
			}
			k = 0;
			for (i = 0; i < 3; i++)//k�� ���� ���� ����
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
			bast[9][a] = k; //��ĭ�� ���� �� ����
			trc++;
			for (i = 0; i < 3; i++)
				bast[trc][i] = bast[9][i];
			Try(trc, bast); //����������
			return;
		}
		else //s==1or s==0
		{//ball�� �̿��ؼ� �ڸ� Ȯ��
			for (i = 0; i < 3; i++) 
			{
				for (k = 0; k < 3; k++)
				{
					for (j = 0; j <=trc; j++)
						ball[i][9][k] += ball[i][j][k];
				}//ball�� �� ���� �� ball[i][9][k]�� ���� ����
			}
			for (i = 0; i < 3; i++)
			{
				j = 0;
				for (k = 0; k < 3; k++)
				{
					if (ball[i][9][k] != 0)//j�� �� �ڸ� �� ����
						j++;
					else
						s = k; //s�� �� �ڸ� ����
				}
				if (j == 2) //���� 2�ڸ����� ��Ÿ�� ��� ��ġ Ȯ��
					bast[9][s] = bast[trc][i];
			}

			s = 0;//Ȯ���� �ڸ� ���� ���� ����
			for (i = 0; i < 3; i++)
			{
				if (bast[9][i] != 0) //s�� �ڸ��� Ȯ���� ���� ���� ����
					s++;
			}
			if (s < 2) // Ȯ���� �ڸ��� 0�Ǵ� 1�϶� �߰�����
			{
				SetC(s, trc, bast);//���� ������ �� �����ϴ� �Լ�
				trc++;
				Try(trc, bast); //������ ã�� ���� �߰�����
				if (bast[trc][3] == 3)
					return; //�߰����࿡�� 3s�� ���
				else
				{// �߰����� ���� FinP�Լ� �ٽ� ȣ��
					FinP( trc,bast); 
					return;
				}
			}
		}
	}
	return;
}

void SetC(int s, int trc, int bast[10][5]) //s = ���ݱ��� Ȯ���� �ڸ� �� (0 �Ǵ� 1)
{
	int i,j,k;
	int b[3] = { bast[trc][0],bast[trc][1],bast[trc][2] }; //bast[trc][0,1,2]�� ���� b�� ����
	int x, y; //(1s2b),(0s3b) ������ ���� ã��

	//1,2ȸ ���࿡�� BS ��� 0�� ���
	if ((bast[0][3] + bast[0][4] == 0) && (bast[1][3] + bast[1][4] == 0)) 
	{//(c,c,c)�� ��� �ش��ϴ� �� ���� ��������
		bast[trc + 1][0] = 1;
		bast[trc + 1][1] = 2;
		bast[trc + 1][2] = 3;
		bast[0][3] = 5;
		bast[0][4] = 5;
		bast[1][3] = 5;
		bast[1][4] = 5;
		return;
	}

	for (x = 0; x <= trc; x++) //x�� 1s2b�� �õ��� ����� �� (�������� ��� ���� ���� �õ�)
	{
		if ((bast[x][3] == 1) && (bast[x][4] == 2))
			break;
	}
	for (y = 0; y <= trc; y++)//y�� 0s3b�� �õ��� ����� �� (�������� ��쿡 ���� ���� �õ�)
	{
		if ((bast[y][3] == 0) && (bast[y][4] == 3))
			break;
	}

	if (s == 1) //Ȯ���� ���� �ϳ� �ִ� ���
	{//bast[trc+1][0,1,2]�� ���� ������ �� ����
		for (i = 0; i < 3; i++)
		{
			if (bast[9][i] != 0) //i�� Ȯ���� ���ڸ��� ��ġ
				break;
		}

		bast[trc + 1][i] = bast[9][i]; //Ȯ���� ���ڸ��� ������ �õ��� �࿡ ����
		for (j = 0; j < 3; j++)
			b[j] = (b[j] == bast[9][i]) ? (0) : (b[j]); //�ڸ��� Ȯ���� �� b�迭���� ����

		if (y != trc+1) //�� �ڸ��� Ȯ���̰�, (0s3b)������ �ִ� ��� 3s�� Ȯ��
		{
			k = (i == 2) ? (0) : (i + 1); //i�� 0�̸� k�� 1, 1�̸� 2, 2�̸� 0
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
		else if (x != trc+1) //�� �ڸ��� Ȯ���̰�, (1s 2b) ������ �ִ� ��� 3s�� Ȯ��
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
		else //(0,3),(1,2) �Ѵ� ���� ��� (1s2b)�Ǵ� (3s0b) 
		{// (1,2) �� ������ ���� �Ѱ��� ����Ǽ��� 3S
			//���� ������ �� ����, Ȯ���� �ڸ� �� ���� ����
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
	else //s==0 Ȯ���� ���� �ϳ��� ���� ���
	{
		if(y!=trc+1)
		{//3b�� �ִ� ��� ����� ���� 2������ (�� ���� ���� ����)
			bast[trc + 1][0] = bast[y][1];
			bast[trc + 1][1] = bast[y][2];
			bast[trc + 1][2] = bast[y][0];
		}//trc+1�� ���� ����� (3,0) �Ǵ� (3,0�� �ƴ�)
		else if(x!=trc+1)
		{//1s2b�� �ִ� ��� ����� ���� 3������ (�� ���� ���� ����)
			bast[trc + 1][0] = bast[x][0];
			bast[trc + 1][1] = bast[x][2];
			bast[trc + 1][2] = bast[x][1];
		}//trc+1�� ���� ����� (3,0) �Ǵ� (0,3)
		else
		{//���� ���� 3BS�� �˾Ƴ� ��� (������ ���� ������ �� ����)
			bast[trc + 1][0] = bast[trc][0];
			bast[trc + 1][1] = bast[trc][1];
			bast[trc + 1][2] = bast[trc][2];
		}//trc+1�� ���� ����� (3,0),(1,2),(0,3)
	}
	return;
}
