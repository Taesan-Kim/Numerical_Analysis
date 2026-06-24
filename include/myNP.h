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


#ifndef MYNP22300203_H
#define MYNP22300203_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define		PI		3.14159265358979323846264338327950288419716939937510582

//일계도함수
//1. Two point
//
// Forward
//	(y[i+1]-y[i])/(x[i+1]-x[i])
// Backward
//	(y[i]-y[i-1])/(x[i]-x[i-1])
// central
//	(y[i+1]-y[i-1])/(x[i+1]-x[i-1])
// 
//2. Three point
// 
// Forward
//  (-3 * y[i] + 4 * y[i + 1] - y[i + 2]) / (x[i + 2] - x[i])
// Backward
//  m-1 => (y[m - 3] - 4 * y[m - 2] + 3 * y[m - 1]) / (x[m - 1] - x[m - 3])
// 
//3. Four point
// 
//  Central
//   (y[i-2] - 8 * y[i-1] + 8 * y[i+1] - y[i+2])/(12 * (x[i] - x[i-1]))
// 
// 
//이계도함수 
// 
//1. Three Point
// 
// Forward
//  (y[i] - 2 * y[i+1] + y[i+2])/(h * h)
// Backward
//  (y[i-2] - 2 * y[i-1] + y[i])/(h * h)
// central
//  (y[i-1] - 2 * y[i] + y[i+1])/(h * h)
// 
//2. Four Point
// 
// Forward
//  (2 * y[i] - 5 * y[i+1] + 4 * y[i+2] - y[i+3])/(h * h)
// Backward
//  (-y[i-3] + 4 * y[i-2] - 5 * y[i-1] + 2 * y[i])/(h * h)
// 
//3. Five Point
// 
// Central
//  (-y[i-2] + 16 * y[i-1] - 30 * y[i] + 16 * y[i+1] - y[i+2])/(12 * h * h)
//






extern void printVec(double* vec, int row);

double factorial(int _x);

double sinTaylor(double _x);

double cosTaylor(double _x);

double expTaylor(double _x);

//power x^N
double power(double _x, int N);

double differ1(double func(double x), double x, double h);
double differ2(double func(double x), double x, double h);
double differ3(double func(double x), double x, double h);
double differ4(double (*func)(double), double x, double h);
double differ5(double func(double x), double x, double h);

double gradx(double func(double x, double y), double x, double y, double h);
double grady(double func(double x, double y), double x, double y, double h);

double Taylorh(double func(double x), double x, double h);

/**
* Name:		Non-linear approximation method biSection
* Date:		2024/09/09
* Input:
* - func:	non-linear function
* - tol:	allowence tolerance
* - a, b:	2D area [a, b]
* Return:	None(Print error)
**/
void biSection(double func(double x), double tol, double a, double b);

/**
* Name:		Non-linear approximation method newtonRaphson
* Date:		2024/09/09
* Input:	
* - func:	non-linear function
* - dfunc:	differential non-linear function
* - x0:		initial value
* - tol:	allowence tolerance
* Return:	None(Print error)
**/
void newtonRaphson(double func(double x), double dfunc(double x), double x0, double tol);

/**
* Name:		Non-linear approximation method secant
* Date:		2024/09/09
* Input:
* - func:	non-linear function
* - x0, x1:		initial value
* - tol:	allowence tolerance
* Return:	xk
**/
double secantfzero(double func(double x), double x0, double x1, double tol);


void gradient1D(double _x[], double _y[], double dydx[], int m);

void gradientFunc(double func(const double x), double _x[], double dydx[], int m);

void acceleration(double x[], double y[], double dy2dx2[], int m);


/**
* Name:		interpolation of linear spline
* Date:		20241004
* Input:
* -x[]:		x values
* -y[]:		y values
* m:		count of numbers
* xq:		user input x value
**/
double intep1(double x[], double y[], int m, double xq);

/**
* Name:		Rectangular method function
* Date:		20241004
* Input:
* -x[]:		x values
* -y[]:		y values
* m:		count of numbers
**/
double rectangular(double x[], double y[], int m);

/**
* Name:		Trapezoidal method function
* Date:		20241004
* Input:	
* -x[]:		x values
* -y[]:		y values
* m:		count of numbers
**/
double trapz(double x[], double y[], int m);

/**
* Name:		simpson13 method function
* Date:		20241004
* Input:
* -x[]:		x values
* -y[]:		y values
* m:		count of numbers
**/
double simpson13(double x[], double y[], int m);

/**
* Name:		integral method function
* Date:		20241004
* Input:
* func:		input function
* a:		start integral
* b:		final integral
* n:		count of numbers
**/
double integral(double func(const double x), double a, double b, int n);






double odeFunc_rc(const double t, const double v);
void odeFunc_mck(double dYdt[], const double t, const double Y[]);

/*------------------------------------------------------------------------------------------*/
/*			MOVEfunction definitions to  myNP.cpp								 		*/
/*------------------------------------------------------------------------------------------*/



void odeEU(double y[], double odeFunc(const double t, const double y), const double t0, const double tf, const double h, const double y_init);

void odeRK2(double y[], double odeFunc(const double t, const double y), const double t0, const double tf, const double h, const double y_init);

void odeRK3(double y[], double odeFunc(const double t, const double y), const double t0, const double tf, const double h, const double y0);

void odeRK4(double y[], double odeFunc(const double t, const double y), const double t0, const double tf, const double h, const double y_init);

void sys2RK2(double y[], double v[], void odeFuncSys(double dYdt[], const double t, const double Y[]), const double t0, const double tf, const double h, const double y1_init, const double y2_init);

void sys2RK4(double y[], double v[], void odeFuncSys(double dYdt[], const double t, const double Y[]), const double t0, const double tf, const double h, const double y1_init, const double y2_init);







#endif;