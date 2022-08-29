#include "BaseBall.h"

void Menu1(void)
{
	char score = 0; //야구게임 진행한 횟수
	int rep; //다시하기 메뉴 선택

	BaseQ(&score);
	while (1)
	{
		rep = 0;
		printf("┌────────────────────────────────────────┐ \n");
		printf("│            야구게임 문제풀기           │ \n");
		printf("│                                        │ \n");
		printf("│              (1)계속하기               │ \n");
		printf("│              (2)그만하기               │ \n");
		printf("└────────────────────────────────────────┘ \n  >>>  ");

		scanf("%d", &rep);
		while (getchar() != '\n'); //입력버퍼 지움
		
		if (rep == 1)
			BaseQ(&score);
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
	printf("┌────────────────────────────────────────┐ \n");
	printf("│              총점 %2d 점                │ \n",score);
	printf("└────────────────────────────────────────┘ \n");
	Sleep(3000);
	system("cls"); //화면지움
	printf("┌────────────────────────────────────────┐ \n");
	return ;
}
void BaseQ(char *score)
{
	char i, j,s; // for문에 사용
	int qu[3]; // 정답을 저장할 배열
	int an[3]; // 답을 입력받아 저장할 배열
	char st = 0, ba; // 스트라이크, 볼 카운트
	char str[30]; // 답을 입력받을 문자열 ( 입력형식 조정)
	char k; // str에서 문자 하나씩 저장
	int a = 0; //str에서 추출한 숫자 an저장에 사용
	
	system("cls");
	srand(time(NULL)); //시간을 이용한 난수 발생

	for (i = 0; i < 3; i++)
	{
		qu[i] = (rand() % 9) + 1; // 난수값을 9로 나눈 나머지(0~8)에 1을 더한 값(1~9) 생성
		for (j = 0; j < i; j++) // qu배열에 동일한 값이 이미 있는지 확인 (새로운 값의 앞까지)
		{
			if (qu[i] == qu[j]) // qu배열에 동일한 값이 이미 있을 때
			{
				i--; // 난수를 다시 발생시키기 위해 i값을 1감소시킴
				break;
			}
		}
	}

	while (st != 3) // 3스트라이크가 되기 전까지 반복
	{
		printf("┌────────────────────────────────────────┐ \n");
		printf("│          숫자 3개를 입력하세요!        │ \n");
		printf("└────────────────────────────────────────┘ \n  >>>  ");

		fgets(str, sizeof(str), stdin); //문자열 입력받음
		s = strlen(str); //길이계산
		a = 0;
		for (i = 0; i < s; i++)
		{
			k = str[i];
			if (((atoi(&str[i]) != 0) && (k != ' ')) || (k == '0')) //atoi: 문자-> 정수, 정수가 아닌경우 0 반환
			{
				an[a] = atoi(&str[i]);
				a++;
			}
		}

		st = 0; ba = 0; //스트라이크, 볼 초기화

		for (i = 0; i < 3; i++) // 배열 qn과 an을 비교하는 반복문
		{
			for (j = 0; j < 3; j++)
			{
				if (qu[j] == an[i]) // qn[j]와 an[i]의 값이 같은 경우
					(i == j) ? st++ : ba++;
			} // i와 j의 값이 같음 -> 자리수 같음 -> 스트라이크
		}

		if (st + ba == 0) // 0스트라이크 0볼인 경우에 아웃 출력
			printf("\t\t\t\t      OUT!\n");
		else if (!((st==3)&&(ba==0)))
			printf("\t\t\t  %d Strike, %d Ball\n", st, ba); // 스트라이크, 볼 개수 출력
	}
	printf("\t\t\t\t  HOMERUN!\n"); // while문 탈출시(3스트라이크) 홈런 출력
	*score += 1; // 게임시행횟수 1회 증가
	return;
}