#include <stdio.h>
#include <math.h>

void floatingPoint(void) {	//bisection method - floating point
	float a = 1.0, b = 2.0, c,temp, tol = 1/pow(2,16);	//[1,2]
	int iter = 0;
	printf("floatingPoint\n------------------");

	while (a + tol != b) {
		++iter;
		c = a + (b - a) / 2; //bisection
		temp = getYsign_floating(&a) * getYsign_floating(&c);	// is y(a) * y(c) negative?
		if (temp < 0) b = c;		//[a,c]
		else if (temp > 0) a = c;	//[c,b]
		else break; //y(c)==0
	}
	printf("iter: %d\n", iter);

	if (temp != 0) printf("[a,b] = [%f, %f]\n\n\n", a, b);
	else printf("x = %f\n\n\n", c);

	return;
}

void fixedPoint(void) {	//bisection method - fixed point
	int temp, iter=0, tol = 1;
	int a = 1 << 16, b = 2 << 16, c;	//[1,2]
	printf("fixedPoint\n------------------");

	while (a + tol != b) {
		++iter;
		c = a + ((b - a) >> 1);//bisection
		temp = getYsign_fixed(&a) * getYsign_fixed(&c);	// is y(a) * y(c) negative?
		if (temp < 0) b = c;		//[a,c]
		else if (temp > 0) a = c;	//[c,b]
		else break;	//y(c)==0
	}
	printf("iter: %d\n", iter);
	if (temp != 0) printf("[a,b] = [%X >> 16, %X >> 16]\n\n\n", a, b);
	else printf("x = %d >> 16\n\n\n", c);

	return;
}

int getYsign_floating(float* x) {
	float tol = 1 / pow(2, 16);
	float y = pow((*x), 3) + 4 * pow((*x), 2) - 10;	//y(x)

	if (y > 0) return 1;
	else if ((y > -tol) && (y < tol)) return 0;
	else return -1;
}

int getYsign_fixed(int* x) {
	int tol = 1;
	long long t1 = (long long)(*x) * (*x) * (*x);	//x^3
	long long t2 = (long long)4 * (*x) * (*x);		//x^2
	long long t3 = (long long)10;
	t1 >>= 32; t2 >>= 16; t3 <<= 16;	//fixed point mult.
	long long temp = t1 + t2 - t3;	// y(x)
	int y = 0xFFFFFFFF & temp;		// use 4byte

	if (y > 0) return 1;
	else if ((y > -tol) && (y < tol)) return 0;
	else return -1;
}


int main(void) {
	fixedPoint();
	floatingPoint();

	return 0;
}