#include "BaseBall.h"

int main(void)
{
	int Num; //메뉴선택

	system("mode con cols=50 lines=50 | title N.G.B."); //콘솔창의 제목, 크기 설정

	printf("┌────────────────────────────────────────┐ \n");
	printf("│  숫자야구게임에 오신 것을 환영합니다.  │ \n");
	printf("├────────────────────────────────────────┤ \n");

	while(1)
	{
		Num = 0xff;
		printf("│     원하시는 메뉴를 선택해주세요.      │ \n");
		printf("│                                        │ \n");
		printf("│         (1) 야구게임 문제풀기          │ \n");
		printf("│         (2) 야구게임 문제내기          │ \n");
		printf("│         (3) 규칙설명                   │ \n");
		printf("│         (4) 종료                       │ \n");
		printf("│                                        │ \n");
		printf("└────────────────────────────────────────┘ \n >>>  ");
		scanf("%d", &Num);
		Sleep(253);

		while (getchar() != '\n');

		switch (Num)
		{
		case 1:
			Menu1();
			break;
		case 2:
			Menu2();
			break;
		case 3:
			Menu3();
			break;
		case 4:
			system("cls");
			printf("\n\n┌────────────────────────────────────────┐ \n");
			printf("│          프로그램을 종료합니다.        │ \n");
			printf("└────────────────────────────────────────┘ \n\n");
			Sleep(2000); //2초 지연
			return 0;
		default :
			system("cls");
			printf("┌────────────────────────────────────────┐ \n");
			printf("│           잘못 입력하셨습니다.         │ \n");
			printf("│            다시 입력해주세요.          │ \n");
			printf("├────────────────────────────────────────┤ \n");
			Num = 0;
			continue;
		}
	}
}