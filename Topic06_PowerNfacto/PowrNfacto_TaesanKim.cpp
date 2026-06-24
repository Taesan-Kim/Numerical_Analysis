#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double factorial(int _x);
double power(double _x, int N);

int main(int argc, char* argv[])
{

	double x = 2.5;
	int N = 5;
	double y1 = 1;
	double y2 = 1;

	y1 = power(x, N);
	y2 = factorial(N);


	printf("\n\n");
	printf("=======================================\n");
	printf("    power(%f,%d ) Calculation   \n", x, N);
	printf("=======================================\n");
	printf("   -  My     result = %3.12f    \n", y1);
	printf("   -  Math.h result = %3.12f    \n", pow(x, N));
	printf("   -  absolute err. = %3.12f    \n", y1 - pow(x, N));
	printf("=======================================\n");

	printf("\n\n");
	printf("=======================================\n");
	printf("    factorial( %d) Calculation   \n", N);
	printf("=======================================\n");
	printf("   -  My     result = %.0f    \n", y2);
	printf("=======================================\n");


	system("pause");
	return 0;
}

// power fuction
double power(double x, int N)
{
	double y = 1.0;
	for (int i = 0; i < N; i++) y = y * x;
	return y;
}

// factorial function
double factorial(int N)
{
	double y = 1.0;
	for (int k = 2; k <= N; k++) y = y * k;
	return y;
}