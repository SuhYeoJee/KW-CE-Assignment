#include <stdio.h>
//1:34~1:46

int main(void)
{
	char ch, *cp;
	int num, *ip;
	float f_num, *fp;
	double d_num, *dp;

	ch = 'A'; num = 100; //���� ������ ���� ������
	f_num = 5.6; d_num = 17.5;

	cp = &ch; //���� �����Ϳ� ������ �ּҸ� ������
	ip = &num;
	fp = &f_num;
	dp = &d_num;

	printf("1 �����ϱ� �� ������ ������ ����.\n"); //������ ����� ���� ������ ������ ����� �ּҸ� ���
	printf("�������� ��: %5c %5d %10.2f %10.2lf \n", ch, num, f_num, d_num);
	printf("������ ������ ����� �ּ� : %p %p %p %p \n\n", cp, ip, fp, dp);
	
	ch++; num++; f_num++; d_num++; //������ ����� ���� 1�� ����
	cp++; ip++; fp++; dp++; //�����ͺ����� ����� ���� 1�� ����

	printf("1 ������ �� ������ ������ ����.\n");
	printf("�������� ��: %5c %5d %10.2f %10.2lf \n", ch, num, f_num, d_num); // ������ ��µ� ���� +1 ���� ��µ�
	printf("������ ������ ����� �ּ� : %p %p %p %p \n\n", cp, ip, fp, dp); // ������ ��µ� ���� +4 ���� ��µ�

	return 0;
}