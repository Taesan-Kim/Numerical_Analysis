/*
================================================

------------------------------------------------
Author           : Tae-san Kim
Created          : 14-10-2024
Modified         : 24-06-2026
Language/ver     : C++ in MSVS2019
------------------------------------------------

================================================
*/

#include "myNP.h"

void printVec(double *vec, int size)
{
	for (int i = 0; i < size; i++)
		printf("Vector[%d] = %.1f \n", i, vec[i]);
	printf("\n");
}

// factorial function
double factorial(int N)
{
	int y = 1;
	for (int k = 2; k <= N; k++)
		y = y * k;
	return y;
}

//  Taylor series approximation for sin(x) (input unit: [rad])
double sinTaylor(double _x)
{
	int N_max = 10;
	double S_N = 0;
	for (int k = 0; k < N_max; k++)
		S_N = S_N + pow(-1, k) * pow(_x, 2 * k + 1) / factorial(2 * k + 1);
	return S_N;
}

double cosTaylor(double _x)
{
	int N_max = 10;
	double S_N = 0;

	for (int k = 0; k < N_max; k++)
		S_N = S_N + pow(-1, k) * pow(_x, 2 * k) / factorial(2 * k);

	return S_N;
}

double expTaylor(double _x)
{
	int N_max = 10;
	double S_N = 0;

	for (int k = 0; k < N_max; k++)
		S_N = S_N + pow(_x, k) / factorial(k);

	return S_N;
}

// power fuction
double power(double _x, int N)
{
	double temp = _x;
	for (int i = 1; i < N; i++)
	{
		_x = _x * temp;
	}
	return _x;
}

double differ1(double func(double x), double x, double h)
{
	double N = func(x + h) - func(x - h);
	double D = 2 * h;
	return N / D;
}

double differ2(double func(double x), double x, double h)
{
	double N = func(x + h) - 2 * func(x) + func(x - h);
	double D = 4 * h * h;
	return N / D;
}

double differ3(double func(double x), double x, double h)
{
	double N = func(x + 2 * h) - 2 * func(x + h) + 2 * func(x - h) - func(x - 2 * h);
	double D = 2 * h * h * h;
	return N / D;
}

double differ4(double func(double x), double x, double h)
{
	double N = func(x - 2 * h) - 4 * func(x - h) + 6 * func(x) - 4 * func(x + h) + func(x + 2 * h);
	double D = h * h * h * h;
	return N / D;
}

double differ5(double func(double x), double x, double h)
{
	double N = -func(x - 3 * h) + 5 * func(x - 2 * h) - 10 * func(x - h) + 10 * func(x + h) - 5 * func(x + 2 * h) + func(x + 3 * h);
	double D = pow(h, 5);
	return N / D;
}

double gradx(double func(double x, double y), double x, double y, double h)
{
	double N = func(x + h, y) - func(x - h, y);
	double D = 2 * h;
	return N / D;
}

double grady(double func(double x, double y), double x, double y, double h)
{
	double N = func(x, y + h) - func(x, y - h);
	double D = 2 * h;
	return N / D;
}

double Taylorh(double func(double x), double x, double h)
{
	int N_max = 100;
	double out = 0.0;
	for (int i = 0; i < N_max; i++)
	{
		double term;
		if (i == 0)
		{
			term = func(x);
		}
		else if (i == 1)
		{
			term = differ1(func, x, h);
		}
		else if (i == 2)
		{
			term = differ2(func, x, h);
		}
		else if (i == 3)
		{
			term = differ3(func, x, h);
		}
		else if (i == 4)
		{
			term = differ4(func, x, h);
		}
		else if (i == 5)
		{
			term = differ5(func, x, h);
		}
		else
		{
			break; // �� ���� ���� �̺��� ����
		}
		out += term * pow(h, i) / factorial(i);
	}
	return out;
}

void biSection(double func(double x), double tol, double a, double b)
{
	// �ִ� ������, ����, x0��
	int Nmax = 1000;
	double ep = 10.0;
	double xk = 0.0;

	int i = 0;
	if (func(a) * func(b) > 0)
		printf("Solution dont exists in this area!");
	else
		while (Nmax > i && ep > tol)
		{
			xk = 0.5 * (a + b);
			if (func(a) * func(xk) < 0)
			{
				b = xk;
			}
			else
			{
				a = xk;
			}
			i++;
			ep = fabs(func(xk));
			printf("Iteration: %2d		 Xn(k): %f	Tolerance: %f\n", i, xk, ep);
		}
	if (i == Nmax)
		printf("Solution did not converge !!!");
	printf("Final Solution: %f\n", xk);
}

void newtonRaphson(double func(double x), double dfunc(double x), double x0, double tol)
{
	// �ִ� ������, ����, x0��
	int Nmax = 1000;
	double ep = 10.0;
	double xk = x0;
	double h = 0.0;
	int i = 0;

	while (i < Nmax && ep > tol)
	{
		if (dfunc(xk) == 0)
			printf("Error!! dF=0 !!");
		h = -func(xk) / dfunc(xk);
		xk = xk + h;
		i++;
		ep = fabs(func(xk));
		printf("Iteration: %2d		 Xn(k): %f	Tolerance: %f\n", i, xk, ep);
	}
	if (i == Nmax)
		printf("Solution did not converge !!!");
	printf("Final Solution: %f\n", xk);
}

double secantfzero(double func(double x), double x0, double x1, double tol)
{

	double xk = x0; // ���� xk�� �����ش�.
	double temp = 0.0;
	double ep = 10.0;
	int Nmax = 1000;
	int i = 0;
	while (ep > tol && i < Nmax)
	{
		if ((func(x1) - func(x0)) * func(x1) == 0)
		{
			printf("Error!! dF=0 !!");
			break;
		}
		temp = xk;
		xk = x1 - (x1 - x0) / (func(x1) - func(x0)) * func(x1);
		x0 = x1;
		x1 = temp;
		i++;
		ep = fabs(func(xk));
		printf("Iteration: %2d		 Xn(k): %f	Tolerance: %f\n", i, xk, ep);
	}
	return xk;
	printf("Final Solution: %f\n", xk);
}

// y�� �̺а��� ���ؼ� �������ش�.
// ù��°�� ������ ������ ���� 3-Point forward backward difference ����
// �߾��� 2-Point central difference ����
void gradient1D(double _x[], double _y[], double dydx[], int m)
{
	int i = 0;
	for (i = 0; i < m - 1; i++)
	{
		if (i == 0)
			dydx[i] = (-3 * _y[i] + 4 * _y[i + 1] - _y[i + 2]) / (_x[i + 2] - _x[i]);
		else
		{
			dydx[i] = (_y[i + 1] - _y[i - 1]) / (_x[i + 1] - _x[i - 1]);
		}
	}
	dydx[m - 1] = (_y[m - 3] - 4 * _y[m - 2] + 3 * _y[m - 1]) / (_x[m - 1] - _x[m - 3]);
}

// gradient1D���� �������� �������� ����� ���� �Ϳ� ����, �̹����� �Լ��� �޴´�.
void gradientFunc(double func(const double x), double _x[], double dydx[], int m)
{
	dydx[0] = 0.5 * (-3 * func(_x[0]) + 4 * func(_x[1]) - func(_x[2])) / (_x[1] - _x[0]);
	for (int i = 1; i < m - 1; i++)
	{
		dydx[i] = 0.5 * (func(_x[i + 1]) - func(_x[i - 1])) / (_x[i + 1] - _x[i]);
	}
	dydx[m - 1] = 0.5 * (func(_x[m - 3]) - 4 * func(_x[m - 2]) + 3 * func(_x[m - 1])) / (_x[m - 1] - _x[m - 2]);
}

// ����� �޾� �װ��� �̰赵�Լ��� ���Ѵ�.
void acceleration(double x[], double y[], double dy2dx2[], int m)
{
	int i = 0;
	for (i = 0; i < m - 1; i++)
	{
		if (i == 0)
			dy2dx2[i] = (2 * y[i] + -5 * y[i + 1] + 4 * y[i + 2] - y[i + 3]) / ((x[i + 1] - x[i]) * (x[i + 1] - x[i]));
		else
		{
			dy2dx2[i] = (y[i - 1] - 2 * y[i] + y[i + 1]) / ((x[i] - x[i - 1]) * (x[i] - x[i - 1]));
		}
	}
	dy2dx2[m - 1] = (-y[m - 4] + 4 * y[m - 3] - 5 * y[m - 2] + 2 * y[m - 1]) / ((x[m - 1] - x[m - 2]) * (x[m - 1] - x[m - 2]));
}

double intep1(double x[], double y[], int m, double xq)
{
	int func_num = -1;
	for (int i = 0; i < m - 1; i++)
	{
		if (x[i] <= xq && xq < x[i + 1])
		{
			func_num = i;
		}
	}
	if (func_num == -1)
	{
		printf("xq is not in this interval!");
		return NAN;
	}
	double yq = 0.0;
	yq = y[func_num] * (xq - x[func_num + 1]) / (x[func_num] - x[func_num + 1]) + y[func_num + 1] * (xq - x[func_num]) / (x[func_num + 1] - x[func_num]);
	return yq;
}

double rectangular(double x[], double y[], int m)
{
	double I = 0.0;
	for (int i = 0; i < m - 1; i++)
	{
		I = I + y[i] * (x[i + 1] - x[i]);
	}
	return I;
}

double trapz(double x[], double y[], int m)
{
	double I = 0.0;
	for (int i = 0; i < m - 1; i++) // m�� �ƴ϶� m-1�̴�.
	{
		I = I + (y[i + 1] + y[i]) / 2 * (x[i + 1] - x[i]);
	}
	return I;
}

double simpson13(double x[], double y[], int m)
{
	double I = 0.0;
	double h = (x[m - 1] - x[0]) / (m - 1);
	if (m % 2 == 1)
	{

		I = y[m - 1] + y[0];

		for (int i = 1; i < m - 1; i = i + 2)
		{
			I = I + 4 * y[i];
		}

		for (int j = 2; j < m - 2; j = j + 2)
		{
			I = I + 2 * y[j];
		}

		I = (h / 3) * I;
		return I;
	}
	else
	{
		I = y[m - 2] + y[0];

		for (int i = 1; i < m - 2; i = i + 2)
		{
			I = I + 4 * y[i];
		}

		for (int j = 2; j < m - 3; j = j + 2)
		{
			I = I + 2 * y[j];
		}

		I = (h / 3) * I;
		I = I + 0.5 * (y[m - 1] + y[m - 2]) * h;
		return I;
	}
}

double integral(double func(const double x), double a, double b, int n)
{
	double I = 0.0;
	double h = (b - a) / n;
	if (n % 2 == 0)
	{

		I = func(a) + func(b);
		for (int i = 1; i < n; i = i + 2)
		{
			I = I + 4 * func(a + i * h);
		}
		for (int j = 2; j < n - 1; j = j + 2)
		{
			I = I + 2 * func(a + j * h);
		}
		I = (h / 3.0) * I;
	}
	else
	{
		I = func(a) + func(b - h);
		for (int i = 1; i < n - 1; i = i + 2)
		{
			I = I + 4 * func(a + i * h);
		}
		for (int j = 2; j < n - 1; j = j + 2)
		{
			I = I + 2 * func(a + j * h);
		}
		I = (h / 3.0) * I;
		I = I + func(b - h * 0.5) * h;
	}
	return I;
}

/*==========================================================================*/
/*							  Function Definitions							*/
/*==========================================================================*/

// Gradient function for ODE - 1st order

double odeFunc_rc(const double t, const double v)
{

	double tau = 0.01;
	double f = 100;
	double Vm = 1;
	double omega = 2 * PI * f;
	double dvdt = 0;

	dvdt = -100 * v + 100 * cos(omega * t);
	return dvdt;
}

// Gradient function for ODE - 2nd order
void odeFunc_mck(double dYdt[], const double t, const double Y[])
{
	// Y[0] = �Ÿ�
	// Y[1] = �ӵ�
	double m = 1.0;
	double k = 6.9;
	double c = 7.0;
	double finDC = 2.0; // Acos(2pif)���� A
	double f = 5.0;

	// Y[] => y, y�������̴�.
	dYdt[0] = Y[1]; // dy = z
	// dz = ��
	dYdt[1] = 1.0 / m * (-c * Y[1] - k * Y[0] + finDC * cos(2.0 * PI * f * t));
}

/*------------------------------------------------------------------------------------------*/
/*			MOVEfunction definitions to  myNP.cpp								 		*/
/*------------------------------------------------------------------------------------------*/

void odeEU(double y[], double odeFunc(const double t, const double y), const double t0, const double tf, const double h, const double y_init)
{
	//
	// [BRIEF DESCRIPTION OF THE FUNCTION  GOES HERE]
	//
	// Variable Initialization
	int N = (tf - t0) / h + 1;

	// Initial Condition
	double ti = t0;
	y[0] = y_init;

	// Euler Explicit ODE Method
	for (int i = 0; i < N - 1; i++)
	{
		ti += h;
		y[i + 1] = y[i] + odeFunc(ti, y[i]) * h;
	}
}

void odeRK2(double y[], double odeFunc(const double t, const double y), const double t0, const double tf, const double h, const double y_init)
{

	int N = (tf - t0) / h + 1;
	double y2 = 0;
	double t2 = 0;

	// Initial Condition
	double ti = t0;
	y[0] = y_init;

	// RK Design Parameters
	double C1 = 0.5;
	double C2 = 1.0 - C1;
	double alpha = 1.0;
	double beta = alpha;
	double K1 = 0.0, K2 = 0.0;

	// RK2 ODE Solver
	for (int i = 0; i < N - 1; i++)
	{

		// [First-point Gradient]
		K1 = odeFunc(ti, y[i]);

		// [Second-point Gradient]
		t2 = ti + alpha * h;

		// Calculate y2 = y(i) + beta * K1 * h
		y2 = y[i] + beta * K1 * h;

		// Calculate: K2   using t2 and y2
		K2 = odeFunc(t2, y2);

		// Estimate: y(i+1) using RK2
		y[i + 1] = y[i] + (C1 * K1 + C2 * K2) * h;
		ti += h;
	}
}

void odeRK3(double y[], double odeFunc(const double t, const double y), const double t0, const double tf, const double h, const double y0)
{
	//
	// [BRIEF DESCRIPTION OF THE FUNCTION  GOES HERE]
	//
	int N = (tf - t0) / h + 1;

	double alpha2 = 0.5;
	double alpha3 = 1.0;
	double c1 = 1.0 / 6.0;
	double c2 = 2.0 / 3.0;
	double c3 = 1.0 / 6.0;
	double beta21 = 0.5;
	double beta31 = -1.0;
	double beta32 = 2.0;

	double ti = t0;
	y[0] = y0;

	for (int i = 0; i < N - 1; i++)
	{
		double k1 = odeFunc(ti, y[i]);
		double k2 = odeFunc(ti + 1.0 / 2.0 * h, y[i] + 0.5 * k1 * h);
		double k3 = odeFunc(ti + h, y[i] - k1 * h + 2.0 * k2 * h);
		y[i + 1] = y[i] + 1.0 / 6.0 * (k1 + 4 * k2 + k3) * h;
		ti += h;
	}
}

void odeRK4(double y[], double odeFunc(const double t, const double y), const double t0, const double tf, const double h, const double y_init)
{
	int N = (tf - t0) / h + 1;
	double K1, K2, K3, K4;

	// Initial Condition
	double ti = t0;
	y[0] = y_init;

	// RK4 ODE Solver
	for (int i = 0; i < N - 1; i++)
	{
		// Gradients
		K1 = odeFunc(ti, y[i]);
		K2 = odeFunc(ti + h / 2, y[i] + h * K1 / 2);
		K3 = odeFunc(ti + h / 2, y[i] + h * K2 / 2);
		K4 = odeFunc(ti + h, y[i] + h * K3);

		// Update y(i+1)
		y[i + 1] = y[i] + (h / 6) * (K1 + 2 * K2 + 2 * K3 + K4);

		// Update time
		ti += h;
	}
}

// ODE RK2 for 2nd order ODE
void sys2RK2(double y[], double v[], void odeFuncSys(double dYdt[], const double t, const double Y[]), const double t0, const double tf, const double h, const double y1_init, const double y2_init)
{
	//
	// [BRIEF DESCRIPTION OF THE FUNCTION  GOES HERE]
	//

	// Variable Initialization
	int N = (tf - t0) / h + 1;
	double ti = t0;

	// Initial Condition
	y[0] = y1_init;
	v[0] = y2_init;

	double t1 = t0;
	double alpha = 1.0;
	double beta = 1.0;
	double c1 = 0.5;
	double c2 = 0.5;

	for (int i = 0; i < N - 1; i++)
	{
		double dYdt[2] = {0};
		double Y[2] = {0};
		Y[0] = y[i];
		Y[1] = v[i];
		odeFuncSys(dYdt, t1, Y);

		double Ky1 = dYdt[0];
		double Kv1 = dYdt[1];
		double t2 = t1 + alpha * h;
		double y2 = y[i] + beta * Ky1 * h;
		double v2 = v[i] + beta * Kv1 * h;

		double dYdt2[2] = {0};
		double Y2[2] = {0};

		Y2[0] = y2;
		Y2[1] = v2;

		odeFuncSys(dYdt2, t2, Y2);
		double Ky2 = dYdt2[0];
		double Kv2 = dYdt2[1];
		y[i + 1] = y[i] + (c1 * Ky1 + c2 * Ky2) * h;
		v[i + 1] = v[i] + (c1 * Kv1 + c2 * Kv2) * h;

		t1 += h;
	}
}

void sys2RK4(double y[], double v[], void odeFuncSys(double dYdt[], const double t, const double Y[]), const double t0, const double tf, const double h, const double y1_init, const double y2_init)
{

	int N = (tf - t0) / h + 1;
	double ti = t0;

	// Initial Condition
	y[0] = y1_init;
	v[0] = y2_init;

	double t1 = t0;
	double alpha2 = 0.5;
	double alpha3 = 0.5;
	double beta21 = 0.5;
	double beta32 = 0.5;
	double c1 = 1.0 / 6;
	double c4 = 1.0 / 6;
	double c2 = 1.0 / 3;
	double c3 = 1.0 / 3;

	double alpha4 = 1.0;
	double beta43 = 1.0;
	double beta31 = 0.0;
	double beta41 = 0.0;
	double beta42 = 0.0;

	for (int i = 0; i < N - 1; i++)
	{
		double dYdt[2] = {0};
		double Y[2] = {0};
		Y[0] = y[i];
		Y[1] = v[i];

		odeFuncSys(dYdt, t1, Y);

		double Ky1 = dYdt[0];
		double Kv1 = dYdt[1];
		double t2 = t1 + alpha2 * h;
		double y2 = y[i] + beta21 * Ky1 * h;
		double v2 = v[i] + beta21 * Kv1 * h;

		double dYdt2[2] = {0};
		double Y2[2] = {0};
		Y2[0] = y2;
		Y2[1] = v2;

		odeFuncSys(dYdt2, t2, Y2);
		double Ky2 = dYdt2[0];
		double Kv2 = dYdt2[1];

		double t3 = t1 + alpha3 * h;
		double y3 = y[i] + beta31 * Ky1 * h + beta32 * Ky2 * h;
		double v3 = v[i] + beta31 * Kv1 * h + beta32 * Kv2 * h;

		double dYdt3[2] = {0};
		double Y3[2] = {0};
		Y3[0] = y3;
		Y3[1] = v3;

		odeFuncSys(dYdt3, t3, Y3);
		double Ky3 = dYdt3[0];
		double Kv3 = dYdt3[1];

		y[i + 1] = y[i] + beta41 * Ky1 * h + beta42 * Ky2 * h + beta43 * Ky3 * h;
		v[i + 1] = v[i] + beta41 * Kv1 * h + beta42 * Kv2 * h + beta43 * Kv3 * h;

		t1 += h;
	}
}
