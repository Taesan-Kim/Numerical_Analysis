

#include "stdio.h"
#include "stdlib.h"
#include <math.h>

#include "../../include/myNP.h"
#include "../../include/myMatrix_22300203.h"

// Defined in main code
Matrix myFuncEx1(Matrix X);
Matrix myJacobEx1(Matrix X);
Matrix myFuncEx2(Matrix X);
Matrix myJacobEx2(Matrix X);

void main()
{

	/*==========================================================================*/
	/*					Variables declaration & initialization					*/
	/*--------------------------------------------------------------------------*/
	/*   - You can change the variable names									*/
	/*   - However, you must use the specified file name						*/
	/*	   : For each assignment, the file name will be notified on HISNET		*/
	/*==========================================================================*/

	/************      Variables declaration & initialization      ************/
	double loss = 0;
	double n = 2;
	Matrix J = zeros(n, n);
	Matrix F = zeros(n, 1);
	Matrix H = zeros(n, 1);
	Matrix Z = zeros(n, 1);

	// Initial condition
	double z0[2] = {2.5, 2};
	Z = arr2Mat(z0, n, 1);

	/*==========================================================================*/
	/*					Apply your numerical method algorithm					*/
	/*==========================================================================*/
	printf("----------------------------------------------------------------------------------------------\n");
	printf("			            System of NonLinear													  \n");
	printf("----------------------------------------------------------------------------------------------\n\r");

	Z = nonlinearSys(myFuncEx1, myJacobEx1, Z, 0.001);
	printMat(Z, "Z");

	/************      Variables declaration & initialization      ************/
	loss = 0;
	n = 3;
	Matrix Z2 = zeros(n, 1);

	// Initial condition
	double z0_2[3] = {25 / 180 * PI, 90, 90}; // (theta, dx, dy)
	Z2 = arr2Mat(z0_2, n, 1);

	/*==========================================================================*/
	/*					Apply your numerical method algorithm					*/
	/*==========================================================================*/
	printf("----------------------------------------------------------------------------------------------\n");
	printf("			            System of NonLinear													  \n");
	printf("----------------------------------------------------------------------------------------------\n\r");

	Z2 = nonlinearSys(myFuncEx2, myJacobEx2, Z2, 0.00001);
	printMat(Z2, "Z2");

	/*==========================================================================*/
	/*							  Deallocate memory 							*/
	/*==========================================================================*/
	freeMat(J);
	freeMat(H);
	freeMat(F);
	freeMat(Z);
	freeMat(Z2);

	system("pause");
}

/*==========================================================================*/
/*						Function Definitions								*/
/*==========================================================================*/

Matrix myFuncEx1(Matrix X)
{
	int n = X.rows;
	Matrix F = zeros(n, 1);
	double x1 = X.at[0][0];
	double x2 = X.at[1][0];

	// [TO-DO] YOUR CODE GOES HERE
	F.at[0][0] = x2 - 0.5 * (exp(x1 * 0.5) + exp(-x1 * 0.5));
	F.at[1][0] = 9 * pow(x1, 2) + 25 * pow(x2, 2) - 225;

	return F;
}

Matrix myJacobEx1(Matrix X)
{
	int n = X.rows;
	Matrix J = zeros(n, n);
	double x1 = X.at[0][0];
	double x2 = X.at[1][0];

	// [TO-DO] YOUR CODE GOES HERE
	J.at[0][0] = -0.25 * (exp(x1 * 0.5) - exp(-x1 * 0.5));
	J.at[0][1] = 1.0;
	J.at[1][0] = 18 * x1;
	J.at[1][1] = 50 * x2;

	return J;
}

Matrix myFuncEx2(Matrix X)
{
	int n = X.rows;
	Matrix F = zeros(n, 1);
	double th = X.at[0][0];
	double dx = X.at[1][0];
	double dy = X.at[2][0];

	// Initial positions
	double P0x = 0.0;
	double P0y = 100.0;
	double P1x = 0.0;
	double P1y = -100.0;
	double P3x = 0.0;
	double P3y = 0.0;

	// Final positions
	double P0x_new = 50.0;
	double P0y_new = 186.6025;
	double P1x_new = 150.0;
	double P1y_new = 13.3975;
	double P2x_new = 100.0;
	double P2y_new = 100.0;

	F.at[0][0] = cos(th) * P0x - sin(th) * P0y + dx - P0x_new;
	F.at[1][0] = sin(th) * P0x + cos(th) * P0y + dy - P0y_new;
	F.at[2][0] = cos(th) * P1x - sin(th) * P1y + dx - P1x_new;

	return F;
}

Matrix myJacobEx2(Matrix X)
{
	int n = X.rows;
	Matrix J = zeros(n, n);
	double th = X.at[0][0];
	double dx = X.at[1][0];
	double dy = X.at[2][0];

	double P0x = 0.0;
	double P0y = 100.0;
	double P1x = 0.0;
	double P1y = -100.0;

	// [TO-DO] YOUR CODE GOES HERE
	J.at[0][0] = -sin(th) * P0x - cos(th) * P0y;
	J.at[0][1] = 1.0;
	J.at[0][2] = 0.000001;
	J.at[1][0] = cos(th) * P0x - sin(th) * P0y;
	J.at[1][1] = 0.000001;
	J.at[1][2] = 1.0;
	J.at[2][0] = -sin(th) * P1x - cos(th) * P1y;
	J.at[2][1] = 1.0;
	J.at[2][2] = 0.000001;

	return J;
}
