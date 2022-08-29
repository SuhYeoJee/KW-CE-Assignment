//2019202009 ¼­¿©Áö

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define RVsize	10000 // amount - particular value

int mu=0, b=1;
void GetMuB(void); //get mu, b
void GetRV_X(double *arr); //get Random Variable X // RV_X.txt
void GetRV_Y(double *arr); //get Random Variable Y // RV_Y.txt
double GetY(double x); //calculate T(x,mu,b)

int main(void) {
	double arr[RVsize] = {0,};

	GetMuB();
	GetRV_X(arr);
	GetRV_Y(arr);

	return 0;
}

void GetMuB(void) {
	printf("=========GetMuB=========\n");
	printf("input (int)mu:"); //get mu
	scanf("%d", &mu);
	printf("input (int)b:"); //get b
	scanf("%d", &b);
	return;
}

void GetRV_X(double *arr) {
	printf("=========GetRV_X=========\n");
	FILE* fp;
	int i, j;
	double temp = 0;
	fp = fopen("RV_X.txt", "wt");
	srand(time(NULL));

	for (i = 0; i < RVsize; i++) {
		temp = (double)rand()/ RAND_MAX;	//(double) range 0 ~ 1
		fprintf(fp, "%f,",temp );	//save in .txt
		arr[i]= temp;	//save in array
	}

	fclose(fp);
	return;
}

void GetRV_Y(double *arr) {
	printf("=========GetRV_Y=========\n");
	FILE* fp;
	int i, j;
	fp = fopen("RV_Y.txt", "wt");

	for (i = 0; i < RVsize; i++)
		fprintf(fp, "%f,",GetY(arr[i])); //calculate T(x,mu,b)

	fclose(fp);
	return;
}

double GetY(double x) {
	double y = 0;
	if ((x > 0.5)||(x== 0.5))	//x>= 0.5
		y = mu - b * (log(2 - 2 * x));
	else						// x<0.5
		y = mu + b * log(2 * x);
	return y;
}