#include <stdio.h> // 10:52 ~ 11:28

int main(void)
{
	char str[50];
	int i,a,b=0;

	printf("���ܾ� �Է�: ");
	scanf("%s", str);
	printf("�Է��� ���ܾ�: %s\n", str);

	for (i = 0; str[i] != '\0'; i++)  //���ܾ��� ���� ��
		b++;
	b -= 1;  //������ �ε���

	for (i = 0; i!=b; i++)  //���� ������
	{
		a = str[i];
		str[i] = str[b];
		str[b] = a;
		b--;
	}
	printf("������ ���ܾ�: %s\n", str);

	return 0;
}