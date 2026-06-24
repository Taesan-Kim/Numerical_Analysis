/*----------------------------------------------------------------\
Author           : Tae-san Kim
Created          : 14-10-2024
Modified         : 24-06-2026
Language/ver     : C++ in MSVS2019

Description      : myMatrix.h
----------------------------------------------------------------*/

#ifndef		_MY_MATRIX_H		// use either (#pragma once) or  (#ifndef ...#endif)
#define		_MY_MATRIX_H

#include <iostream>
#include <string>
#include <fstream>

typedef struct { 
	double** at;
	int rows, cols;
}Matrix;

#define PI 3.14159265358979323846264338327950288419716939937510
// Create Matrix with specified size
extern	Matrix	createMat(int _rows, int _cols);

// Free a memory allocated matrix
extern	void	freeMat(Matrix _A);

// Create a matrix from a text file
extern	Matrix	txt2Mat(std::string _filePath, std::string _fileName);

//// Print matrix
extern	void	printMat(Matrix _A, const char* _name);

// Matrix addition
extern	Matrix	addMat(Matrix _A, Matrix _B);


// initialization of Matrix elements
extern	void	initMat(Matrix _A, double _val);

// Create matrix of all zeros
extern	Matrix	zeros(int _rows, int _cols);

// Create matrix of all ones
extern	Matrix	ones(int _rows, int _cols);

// Create identity matrix
extern	Matrix	eye(int _rows, int _cols);


// Matrix subtraction
extern	Matrix	subMat(Matrix _A, Matrix _B);

// Multiply  matrix A and matrix B
extern	Matrix	multMat(Matrix _A, Matrix _B);

// Multiply  matrix A with a scalar k
extern	Matrix	smultMat(Matrix _A, double _k);

// Create Transpose matrix
extern	Matrix	transpose(Matrix _A);

// Copy matrix
extern	Matrix	copyMat(Matrix _A);











//Gauss elimination
void gaussElim(Matrix A, Matrix b, Matrix U, Matrix d, Matrix P);

//Back substitution
void backsub(Matrix U, Matrix& y, Matrix& x);

//Forward substitution
void fwdsub(Matrix L, Matrix& b, Matrix& y);

//Partial pivoting
void Pivot(Matrix A, Matrix& P);

//LU decomposition
void LUdecomp(Matrix A, Matrix& L, Matrix& U, Matrix& P);

void solveLU(Matrix L, Matrix U, Matrix P, Matrix b, Matrix& x);

void invMat(Matrix A, Matrix& Ainv);








//Eigenfunction

double norm02(Matrix A);

double norm_mat(Matrix A);


extern Matrix householder(Matrix v);

void QRdecomp(Matrix A, Matrix& R, Matrix& Q);

Matrix eigval(Matrix A);

Matrix eigvec(Matrix A);

void eig(Matrix A, Matrix& V, Matrix& D);



//Polyfit
// Create a matrix from 1D-array
Matrix	arr2Mat(double* _1Darray, int _rows, int _cols);

//Option 1
Matrix	linearFit_mat(Matrix _vecX, Matrix _vecY);

Matrix	polyFit_mat(Matrix _vecX, Matrix _vecY, int orderN);

// [Option 2]

void linearFit(double vecZ[], double vecX[], double vecY[], int dataL);

void polyFit(double vecZ[], double vecX[], double vecY[], int dataL, int orderN);


//exponential linear fit

// Option 1
Matrix expFit_mat(Matrix _X, Matrix _Y);

// Option 2
void expFit(double z[], double _x[], double _y[], double dataL);


//Nonlinear System
Matrix nonlinearSys(Matrix Funcs(Matrix _Z), Matrix Jacob(Matrix _Z), Matrix _Z0, double tol);



#endif


