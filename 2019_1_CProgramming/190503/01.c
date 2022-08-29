#include <stdio.h>

int super(int money)  // 구입할 개수를 구하는 함수
{
	int a, b, c;  // a,b,c에 크림빵, 새우깡, 콜라의 개수를 저장
	for (a = 0;; a++)
	{
		for (b = 0;; b++)
		{
			for (c = 0;; c++)
			{
				if (500 * a + 700 * b + 400 * c == money)
				{
					printf("크림빵 %2d, 새우깡 %2d, 콜 라 %2d \n",a+1,b+1,c+1);
					continue;
				}
				else if (500 * a + 700 * b + 400 * c > money)
					break;
			}
			if (500 * a + 700 * b > money) break;
		}
		if (500 * a > money) break;
	}
}


int main (void)
{
	int money;

	printf("\n 현재 당신이 소유하고 있는 금액을 100원 단위로 입력: ");
	scanf("%d", &money);
	money -= 1600;    //하나씩 구매
	if (money % 100 != 0)
		printf("100원 단위가 아닙니다\n");
	else if (money < 0)
		printf("돈이 부족합니다\n");
	else if (money < 400 && 0<money)    // 잔돈이 발생하는 경우1 (1700,1800,1900 원)
	{
		printf("크림빵 %2d, 새우깡 %2d, 콜 라 %2d \n", 1, 1, 1);
		printf("\t잔돈이 발생합니다 %d 원\n", money);
	}
	else if (money == 600)   // 잔돈이 발생하는 경우2 (2200 원)
	{
		printf("크림빵 %2d, 새우깡 %2d, 콜 라 %2d \n", 1, 1, 2);
		printf("\t잔돈이 발생합니다 %d 원\n", money - 400);
		printf("크림빵 %2d, 새우깡 %2d, 콜 라 %2d \n", 2, 1, 1);
		printf("\t잔돈이 발생합니다 %d 원\n", money-500);
	}
	else    // 크림빵, 새우깡, 콜라를 구입하는 경우의 수 계산
	{
		super(money);
		printf("어떻게 구입하시겠습니까? \n");
	}
return 0;
}