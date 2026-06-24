

#define ASGN 5
#define EVAL 0

#include "../../include/myMatrix_22300203.h"
#include "../../include/myNP.h"

int main(int argc, char *argv[])
{
	std::string path = "../../NP_Data/Assignment" + std::to_string(ASGN) + "/";
#if EVAL
	path += "eval/";
#endif

	Matrix q1matA = txt2Mat(path, "prob1_matA");
	Matrix q1vecb = txt2Mat(path, "prob1_vecb");
	Matrix extra_matP = txt2Mat(path, "extra_matP");
	// Matrix extra_matA = txt2Mat(path, "extra_matA");
	// Matrix extra_matU = txt2Mat(path, "extra_matU");

	Matrix matUq1 = zeros(q1matA.rows, q1matA.cols);
	Matrix vecdq1 = zeros(q1vecb.rows, q1vecb.cols);
	gaussElim(q1matA, q1vecb, matUq1, vecdq1, extra_matP);
	printf("-------------------------------------------------------------------\n");
	printf("                          Gauss Elimination Results Q1             \n");
	printf("-------------------------------------------------------------------\n");
	printMat(q1matA, "matrix A\n");
	printMat(q1vecb, "vector b\n");
	printMat(matUq1, "Calculate matrix U\n");
	printMat(vecdq1, "Calculate vector bn\n");

	Matrix q1matx = zeros(q1vecb.rows, q1vecb.cols);
	backsub(matUq1, vecdq1, q1matx);
	printMat(q1matx, "vector x\n");

	// Option 1:  Read from datafile
	Matrix q2matA = txt2Mat(path, "prob2_matK");
	Matrix q2vecb = txt2Mat(path, "prob2_vecf");

	Matrix matUq2 = zeros(q2matA.rows, q2matA.cols);
	Matrix vecdq2 = zeros(q2vecb.rows, q2vecb.cols);
	gaussElim(q2matA, q2vecb, matUq2, vecdq2, extra_matP);
	printf("-------------------------------------------------------------------\n");
	printf("                          Gauss Elimination Results Q2             \n");
	printf("-------------------------------------------------------------------\n");
	printMat(q2matA, "matrix A\n");
	printMat(q2vecb, "vector b\n");
	printMat(matUq2, "Calculate matrix U\n");
	printMat(vecdq2, "Calculate vector bn\n");

	Matrix q2matx = zeros(q2vecb.rows, q2vecb.cols);
	backsub(matUq2, vecdq2, q2matx);
	printMat(q2matx, "vector x\n");

	/*
	Matrix matUq2 = zeros(extra_matA.rows, extra_matA.cols);
	Matrix vecdq2 = zeros(vecb.rows, vecb.cols);
	gaussElim(extra_matA, vecb, matUq2, vecdq2, extra_matP);
	printf("-------------------------------------------------------------------\n");
	printf("                          Gauss Elimination Results                \n");
	printf("-------------------------------------------------------------------\n");
	printMat(extra_matA, "matrix A\n");
	printMat(vecb, "vector b\n");
	printMat(matUq2, "Calculate matrix U\n");
	printMat(extra_matU, "True matrix U\n");
	*/

	/*==========================================================================*/
	/*							  Deallocate memory 							*/
	/*==========================================================================*/
	freeMat(q1matA);
	freeMat(q1vecb);
	freeMat(matUq1);
	freeMat(vecdq1);
	freeMat(q1matx);
	freeMat(q2matA);
	freeMat(q2vecb);
	freeMat(matUq2);
	freeMat(vecdq2);
	freeMat(q2matx);
	freeMat(extra_matP);
	// freeMat(extra_matU);
	// freeMat(extra_matA);
	// freeMat(matUq2);	freeMat(vecdq2);

	// free other  created  matrices

	int n = 3;
	Matrix A = txt2Mat(path, "prob1_matA");
	Matrix L = eye(n, n);
	Matrix U = zeros(n, n);

	for (int k = 0; k < n - 1; k++)
	{
		for (int i = k + 1; i < n - 1; i++)
		{
			L.at[i][k] = -A.at[i][k] / A.at[k][k];
		}
		A = multMat(L, A);
	}
	U = A;

	Matrix b = txt2Mat(path, "prob2_vecf");
	Matrix y = zeros(n, 1);
	Matrix x = zeros(n, 1);
	backsub(L, b, y);
	backsub(U, y, x);

	system("pause");
	return 0;
}
