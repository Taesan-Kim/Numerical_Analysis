
#define ASGN 7 // enter your assignment number
#define EVAL 0 // set 0

// [ MODIFY Path and name of Headerfiles]
#include "../../include/myMatrix_22300203.h"
#include "../../include/myNP.h"

// [ CREATE FUNCTIONS ]
// These must be in myMatrix.h, myMatrix.cpp
// Matrix eigval(Matrix A);
// void QRdecomp(Matrix A, Matrix Q, Matrix R);
// Matrix eigvec(Matrix A);
// void eig(Matrix A, Matrix V, Matrix D);

int main(int argc, char *argv[])
{
#if _WIN64 | _WIN32
	/*	 [���� DO NOT EDIT !!!]   Resources file path setting for evaluation	*/
	std::string path = "../../NP_Data/Assignment" + std::to_string(ASGN) + "/";
#elif __APPLE__
	// std::string path = "~/NP_Data/Assignment" + std::to_string(ASGN) + "/";
	std::string path = "../../NP_Data/Assignment" + std::to_string(ASGN) + "/";
#endif
#if EVAL
	path += "eval/";
#endif

	// void  eig(Matrix A, Matrix V, Matrix D)
	// �׷���  V, D�� �����  Eigenvalue ũ��� sorting

	// Q1
	Matrix matA_Q1 = txt2Mat(path, "prob1_matA");

	Matrix V = copyMat(matA_Q1);
	Matrix D = copyMat(V);
	eig(matA_Q1, V, D);
	Matrix eigVals_Q1 = eigval(matA_Q1); // eigval(matA_Q1);
	Matrix eigVecs_Q1 = eigvec(matA_Q1);

	// Q2
	Matrix matA_Q2 = txt2Mat(path, "prob2_matA");
	Matrix eigVals_Q2 = eigval(matA_Q2);
	Matrix eigVecs_Q2 = eigvec(matA_Q2);

	// [Eigenval/vectors for Q1]
	printf("----------------------------------------------------------------------------------------------\n");
	printf("			       Eigenvalue & Eigenvector Results					\n");
	printf("----------------------------------------------------------------------------------------------\n");
	printf("\n[Eigen value]\n\n");
	printMat(eigVals_Q1, "");
	printf("\n[Eigen vector]\n\n");
	printMat(eigVecs_Q1, "");
	printf("\n\n");
	printf("\n[Eigen value]\n\n");
	printMat(D, "");
	printf("\n[Eigen vector]\n\n");
	printMat(V, "");
	printf("\n\n");

	// [Eigenval/vectors for Q2]
	printf("----------------------------------------------------------------------------------------------\n");
	printf("			       Eigenvalue & Eigenvector Results					\n");
	printf("----------------------------------------------------------------------------------------------\n");
	printMat(matA_Q2, "");
	printf("\n[Eigen value]\n\n");
	printMat(eigVals_Q2, "");
	printf("\n[Eigen vector]\n\n");
	printMat(eigVecs_Q2, "");
	printf("\n\n");

	/*==========================================================================*/
	/*							  Deallocate memory 							*/
	/*==========================================================================*/

	// [Deallocate for Q1]
	freeMat(matA_Q1);
	freeMat(eigVals_Q1);
	freeMat(eigVecs_Q1);
	freeMat(V);
	freeMat(D);

	// [Deallocate for Q2]
	freeMat(matA_Q2);
	freeMat(eigVals_Q2);
	freeMat(eigVecs_Q2);

	system("pause");
	return 0;
}