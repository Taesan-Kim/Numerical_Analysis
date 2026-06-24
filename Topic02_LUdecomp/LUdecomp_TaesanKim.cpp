

#define ASGN 6 // enter your assignment number
#define EVAL 0 // [���� DO NOT EDIT !!!]

#include "../../include/myMatrix_22300203.h"
#include "../../include/myNP.h"

int main(int argc, char *argv[])
{
	std::string path = "../../NP_Data/Assignment" + std::to_string(ASGN) + "/";
#if EVAL
	path += "eval/";
#endif

	// Option 1:  Read from datafile
	Matrix Q1_A = txt2Mat(path, "prob1_matA");
	Matrix Q2_A = txt2Mat(path, "prob2_matA");
	Matrix Q1_b = txt2Mat(path, "prob1_vecb");
	Matrix Q2_b = txt2Mat(path, "prob2_vecb");

	printMat(Q1_A, "Q1_A");
	printMat(Q1_b, "Q1_b");
	printMat(Q2_A, "Q2_A");
	printMat(Q2_b, "Q2_b");

	// LU����
	Matrix P01 = zeros(Q1_A.rows, Q1_A.cols);
	Matrix L01 = eye(Q1_A.rows, Q1_A.cols);
	Matrix U01 = zeros(Q1_A.rows, Q1_A.cols);
	LUdecomp(Q1_A, L01, U01, P01);
	printMat(P01, "P_Q1");
	printMat(L01, "L_Q1");
	printMat(U01, "U_Q1");

	// LUx=b Ǯ��
	Matrix x01 = zeros(Q1_b.rows, 1);
	Matrix y01 = zeros(Q1_b.rows, 1);
	// fwdsub(L01, Q1_b, y01);
	// printMat(y01, "Solution of Q1(y01)");
	// backsub(U01, y01, x01);
	solveLU(L01, U01, P01, Q1_b, x01);
	printMat(x01, "Solution of Q1(x01)");

	Matrix Q1_Ainv = zeros(Q1_A.rows, Q1_A.cols);
	invMat(Q1_A, Q1_Ainv);
	printMat(Q1_Ainv, "Q1_Ainv");

	// LU����
	Matrix P02 = zeros(Q2_A.rows, Q2_A.cols);
	Matrix L02 = eye(Q2_A.rows, Q2_A.cols);
	Matrix U02 = zeros(Q2_A.rows, Q2_A.cols);
	LUdecomp(Q2_A, L02, U02, P02);
	printMat(P02, "P_Q2");
	printMat(L02, "L_Q2");
	printMat(U02, "U_Q2");

	// LUx=b Ǯ��
	Matrix x02 = zeros(Q2_b.rows, 1);
	Matrix y02 = zeros(Q2_b.rows, 1);
	// fwdsub(L02, Q2_b, y02);
	// printMat(y02, "Solution of Q1(y02)");
	// backsub(U02, y02, x02);
	solveLU(L02, U02, P02, Q2_b, x02);
	printMat(x02, "Solution of Q2(x02)");

	Matrix Q2_Ainv = zeros(Q2_A.rows, Q2_A.cols);
	invMat(Q2_A, Q2_Ainv);
	printMat(Q2_Ainv, "Q2_Ainv");

	/*==========================================================================*/
	/*							  Deallocate memory 							*/
	/*==========================================================================*/
	freeMat(Q1_A);
	freeMat(Q1_b);
	freeMat(Q2_A);
	freeMat(Q2_b);
	freeMat(P01);
	freeMat(P02);
	freeMat(L01);
	freeMat(L02);
	freeMat(U01);
	freeMat(U02);
	freeMat(x01);
	freeMat(x02);
	freeMat(y01);
	freeMat(y02);
	freeMat(Q1_Ainv);
	freeMat(Q2_Ainv);

	system("pause");
	return 0;
}
