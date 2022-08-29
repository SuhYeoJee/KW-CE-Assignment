#include <stdio.h>

int main(void)
{
	int arr[5];
	int i, M, m, suM;

	for (i=0;i<5;i++)
		scanf("%d", &arr[i]);

	for (i=0;i<5;i++)
		printf("%d", arr[i]);

	M = arr[0]; m = arr[0];
	for (i = 0; i < 5; i++)
		M = (M > arr[i]) ? M : arr[i];
	for (i = 0; i < 5; i++)
		m = (m < arr[i]) ? m : arr[i];

	suM = arr[0];
	for (i = 1; i < 5; i++)
		suM += arr[i];

	printf("\n%d %d %d\n", M, m, suM);

	return 0;
}