

#define ASGN	8		// enter your assignment number
#define EVAL	0		// set 0

#include "../../include/myNP.h"
#include "../../include/myMatrix_22300203.h"
#define PI 3.14159265368979323846264338327950288412



int main(int argc, char* argv[])
{
	/*------------------------------------------------------------------------------------------*/
		/*==========================================================================*/
		/*					Part 1:  1st order ODE-IVP (single equation)			*/
		/*--------------------------------------------------------------------------*/
		/*   - A simple RC circuit response to sinusoidal voltage input				*/
		/*   - You can change the variable names									*/
		/*   - You can create additional functions									*/
		/*==========================================================================*/


		/*==========================================================================*/
		/*						Initialization										*/
		/*==========================================================================*/
		// Initial Conditions
	double a = 0;
	double b = 0.1;
	double h = 0.001;


	unsigned int N = ((b - a) / h) + 1;
	double y_EU[200] = { 0 };				//Cannot use sytanx of  y_EU[N]={0};	
	double y_RK2[200] = { 0 };
	double y_RK3[200] = { 0 };

	// IVP initial values
	double y_init = 0;


	/*==========================================================================*/
	/*					Apply your numerical method algorithm					*/
	/*==========================================================================*/
	// Euler's Explicit Method (given)
	odeEU(y_EU, odeFunc_rc, a, b, h, y_init);

	//  Runge-Kutta 2nd order
	odeRK2(y_RK2, odeFunc_rc, a, b, h, y_init);

	//  Runge-Kutta 3rd order
	odeRK3(y_RK3, odeFunc_rc, a, b, h, y_init);



	/*==========================================================================*/
	/*							  Print your results							*/
	/*==========================================================================*/

	// Print outputs
	printf("----------------------------------------------------------------\n");
	printf("			       1st ODE - IVP  Results						\n");
	printf("----------------------------------------------------------------\n");

	printf("i\t t\t\t yEU\t\t yRK2\t\t yRK3\t \n\n");
	for (int i = 0; i < N; i++)
		printf("%d\t %0.5f\t %.5f\t %.5f\t %.5f\t \n", i, a + i * h, y_EU[i], y_RK2[i], y_RK3[i]);
	printf("\n");


	/*------------------------------------------------------------------------------------------*/

		/*==========================================================================*/
		/*					Part 2:  2nd order ODE-IVP								*/
		/*--------------------------------------------------------------------------*/
		/*   - A simple m-c-k  response to sinusoidal force input					*/
		/*   - You can change the variable names									*/
		/*   - You can create additional functions									*/
		/*==========================================================================*/

		/*==========================================================================*/
		/*						Initialization										*/
		/*==========================================================================*/
		//Parameter Definitions
	double t0 = 0;
	double tf = 1;
	h = 0.01;
	N = (tf - t0) / h + 1;
	double Y[200] = { 0 };
	double V[200] = { 0 };

	// Initial values
	double y_initQ2 = 0;
	double v_initQ2 = 0.2;//velocity


	/*==========================================================================*/
	/*					Apply your numerical method algorithm					*/
	/*==========================================================================*/
	//  Runge-Kutta 2nd order
	sys2RK2(Y, V, odeFunc_mck, t0, tf, h, y_initQ2, v_initQ2);


	printf("----------------------------------------------------------------\n");
	printf("			       2nd order ODE - IVP  Results					\n");
	printf("----------------------------------------------------------------\n");

	printf("i\t t\t\t Y\t\t V\t\t \n\n");
	for (int i = 0; i < N; i++)
		printf("%d\t %0.5f\t %.5f\t %.5f\t\n", i, a + i * h, Y[i], V[i]);
	printf("\n");




	double Y4[200] = { 0 };
	double V4[200] = { 0 };

	// Initial values
	double y_initQ4 = 0;
	double v_initQ4 = 0.2;
	// Extra: Runge-Kutta 4th order
	sys2RK4(Y4, V4, odeFunc_mck, t0, tf, h, y_initQ4, v_initQ4);


	/*==========================================================================*/
	/*							  Print your results							*/
	/*==========================================================================*/
	//
	printf("----------------------------------------------------------------\n");
	printf("			       4nd order ODE - IVP  Results					\n");
	printf("----------------------------------------------------------------\n");

	printf("i\t t\t\t Y\t\t V\t\t \n\n");
	for (int i = 0; i < N; i++)
		printf("%d\t %0.5f\t %.5f\t %.5f\t\n", i, a + i * h, Y4[i], V4[i]);
	printf("\n");

	system("pause");
	return 0;
}

