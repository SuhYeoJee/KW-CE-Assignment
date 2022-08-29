# include <stdio.h>

int main(void)
{
	int arr[50] ;  //충분히 큰 수를 배열의 길이로 지정
	int n, sum=0, i, k=0;

	printf("입력할 정수의 수 : ");
	scanf("%d", &n);

	for (i=0; i < n; i++)  //정수 입력
	{
		printf("%d번째 정수입력: ",i+1);
		scanf("%d", &arr[i]);
	}
	printf("\n");

	for (i = 0; i < n; i++)   //최댓값 구하기
		k = arr[i] > arr[k] ? i : k;
	printf("입력된 정수 중에서 최댓값: %d \n", arr[k]);

	for (i = 0; i < n; i++)   //최솟값 구하기
		k = arr[i] < arr[k] ? i : k;
	printf("입력된 정수 중에서 최솟값: %d \n", arr[k]);

	for (i = 0; i < n; i++)   //총 합 구하기
		sum += arr[i];
	printf("입력된 정수의 총 합 %d \n",sum);

	return 0;
}