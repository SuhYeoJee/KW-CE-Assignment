#include <stdio.h>

int super(int money)  // ������ ������ ���ϴ� �Լ�
{
	int a, b, c;  // a,b,c�� ũ����, �����, �ݶ��� ������ ����
	for (a = 0;; a++)
	{
		for (b = 0;; b++)
		{
			for (c = 0;; c++)
			{
				if (500 * a + 700 * b + 400 * c == money)
				{
					printf("ũ���� %2d, ����� %2d, �� �� %2d \n",a+1,b+1,c+1);
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

	printf("\n ���� ����� �����ϰ� �ִ� �ݾ��� 100�� ������ �Է�: ");
	scanf("%d", &money);
	money -= 1600;    //�ϳ��� ����
	if (money % 100 != 0)
		printf("100�� ������ �ƴմϴ�\n");
	else if (money < 0)
		printf("���� �����մϴ�\n");
	else if (money < 400 && 0<money)    // �ܵ��� �߻��ϴ� ���1 (1700,1800,1900 ��)
	{
		printf("ũ���� %2d, ����� %2d, �� �� %2d \n", 1, 1, 1);
		printf("\t�ܵ��� �߻��մϴ� %d ��\n", money);
	}
	else if (money == 600)   // �ܵ��� �߻��ϴ� ���2 (2200 ��)
	{
		printf("ũ���� %2d, ����� %2d, �� �� %2d \n", 1, 1, 2);
		printf("\t�ܵ��� �߻��մϴ� %d ��\n", money - 400);
		printf("ũ���� %2d, ����� %2d, �� �� %2d \n", 2, 1, 1);
		printf("\t�ܵ��� �߻��մϴ� %d ��\n", money-500);
	}
	else    // ũ����, �����, �ݶ� �����ϴ� ����� �� ���
	{
		super(money);
		printf("��� �����Ͻðڽ��ϱ�? \n");
	}
return 0;
}