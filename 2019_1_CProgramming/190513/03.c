# include <stdio.h>

int main(void)
{
	int arr[50] ;  //����� ū ���� �迭�� ���̷� ����
	int n, sum=0, i, k=0;

	printf("�Է��� ������ �� : ");
	scanf("%d", &n);

	for (i=0; i < n; i++)  //���� �Է�
	{
		printf("%d��° �����Է�: ",i+1);
		scanf("%d", &arr[i]);
	}
	printf("\n");

	for (i = 0; i < n; i++)   //�ִ� ���ϱ�
		k = arr[i] > arr[k] ? i : k;
	printf("�Էµ� ���� �߿��� �ִ�: %d \n", arr[k]);

	for (i = 0; i < n; i++)   //�ּڰ� ���ϱ�
		k = arr[i] < arr[k] ? i : k;
	printf("�Էµ� ���� �߿��� �ּڰ�: %d \n", arr[k]);

	for (i = 0; i < n; i++)   //�� �� ���ϱ�
		sum += arr[i];
	printf("�Էµ� ������ �� �� %d \n",sum);

	return 0;
}