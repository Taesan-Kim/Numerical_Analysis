#include "../../include/myNP.h"

#define pi 3.141592653589793238462643383279

/**
* Name:		example non-linear function
* Date:		2024/09/09
* Input:	x
* Return:	function output
**/
double func(double x)
{
	//return 8 - 4.5 * (x - sin(x));
	x = x * pi / 180; // deg2rad
	return 20 * tanf(x) - 9.8 * 200 / (17*17 * cosf(x)*cosf(x))-2;
}

/**
* Name:		example non-linear differential function
* Date:		2024/09/09
* Input:	x
* Return:	differential function output
**/
double dfunc(double x)
{
	//return -4.5 * (1 - cos(x));
	return 20 * (1/cosf(x)) * (1/cos(x)) - 9.8 * 400 * tanf(x) * (1/cosf(x)) * (1/cosf(x)) /289;
}



int main()
{
	biSection(func, 1e-5, 20,30);
	newtonRaphson(func, dfunc, 28.22, 1e-5);
	printf("%f", secantfzero(func, 29, 30, 1e-5));
}


