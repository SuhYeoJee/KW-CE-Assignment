#include <stdio.h>
#include <string.h>
//2:19~2:40

int main(void)
{
	int i;
	char name[10];
	//���ڿ� ���
	char *emps[6][2] = { "��ҹ�","���� ���ʱ� ����������",
		"������","�λ�� �ؿ��","�����","����� ������ ���ﵿ SDS��Ƽ ķ�۽�",
		"���޷�","���ʽ� ������ �ٴ� 1����","�Ѽ���","��õ�� ���� ������ ����Ʈ",NULL,NULL };

	printf("�˻��� ���� ? ");
	scanf("%s", name);
	for (i = 0; i < 5; i++)
	{
		if (strcmp(name, *emps[i]) == 0) //��ġ�ϴ°��
			break;
	}
	emps[5][0] = ""; //��ġ���� �ʴ� ���
	emps[5][1] = "�˻����� �ʽ��ϴ�";
	printf("%s, %s\n", emps[i][0], emps[i][1]);
	return 0;
}