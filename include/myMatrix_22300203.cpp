/*----------------------------------------------------------------\
Author           : Tae-san Kim
Created          : 14-10-2024
Modified         : 24-06-2026
Language/ver     : C++ in MSVS2019

Description      : myMatrix.cpp
----------------------------------------------------------------*/

#include "myMatrix_22300203.h"



// Free a memory allocated matrix
void	freeMat(Matrix _A)
{
	// 1. Free allocated column memory
	for (int i = 0; i < _A.rows; i++)
		free(_A.at[i]);
	// 2. Free allocated row memory
	free(_A.at);
}

// Create a matrix from a text file
Matrix	txt2Mat(std::string _filePath, std::string _fileName)
{
	std::ifstream file;
	std::string temp_string, objFile = _filePath + _fileName + ".txt";
	int temp_int = 0, nRows = 0;

	file.open(objFile);
	if (!file.is_open()) {
		printf("\n*********************************************");
		printf("\n  Could not access file: 'txt2Mat' function");
		printf("\n*********************************************\n");
		return createMat(0, 0);
	}
	while (getline(file, temp_string, '\t'))
		temp_int++;
	file.close();

	file.open(objFile);
	while (getline(file, temp_string, '\n'))
		nRows++;
	file.close();

	int nCols = (temp_int - 1) / nRows + 1;
	Matrix Out = createMat(nRows, nCols);

	file.open(objFile);
	for (int i = 0; i < nRows; i++)
		for (int j = 0; j < nCols; j++) {
			file >> temp_string;
			Out.at[i][j] = stof(temp_string);
		}
	file.close();

	return Out;
}

// Create Matrix with specified size
Matrix	createMat(int _rows, int _cols)
{
	// check matrix dimension
	if (_rows < 0 || _cols < 0) {
		printf("\n****************************************************");
		printf("\n  ERROR!!: dimension error at 'createMat' function");
		printf("\n****************************************************\n");
		return createMat(0, 0);
	}

	Matrix Out;
	// 1. Allocate row array first
	Out.at = (double**)malloc(sizeof(double*) * _rows);
	// 2. Then, allocate column 
	for (int i = 0; i < _rows; i++)
		Out.at[i] = (double*)malloc(sizeof(double) * _cols);
	// 3. Initialize row & column values of a matrix
	Out.rows = _rows;
	Out.cols = _cols;

	// 4. Initialize with zero (optional)
	initMat(Out, 0);
	return Out;
}


// initialization of Matrix elements
void	initMat(Matrix _A, double _val)
{
	for (int i = 0; i < _A.rows; i++)
		for (int j = 0; j < _A.cols; j++)
			_A.at[i][j] = _val;
}

// Print matrix
void	printMat(Matrix _A, const char* _name)
{
	printf("%s =\n", _name);
	for (int i = 0; i < _A.rows; i++) {
		for (int j = 0; j < _A.cols; j++)
			printf("%15.6f\t", _A.at[i][j]);
		printf("\n");
	}
	printf("\n");
}

// Matrix addition
Matrix	addMat(Matrix _A, Matrix _B)
{
	if (_A.rows != _B.rows || _A.cols != _B.cols) {
		printf("\n*************************************************");
		printf("\n  ERROR!!: dimension error at 'addMat' function");
		printf("\n*************************************************\n");
		return createMat(0, 0);
	}

	Matrix Out = createMat(_A.rows, _B.cols);
	for (int i = 0; i < _A.rows; i++)
		for (int j = 0; j < _B.cols; j++)
			Out.at[i][j] = _A.at[i][j] + _B.at[i][j];

	return Out;
}



// Create matrix of all zeros
extern Matrix	zeros(int _rows, int _cols)
{
	Matrix Out = createMat(_rows, _cols);
	initMat(Out, 0.00);
	return Out;
}


// Create matrix of all zeros
extern Matrix	ones(int _rows, int _cols)
{
	Matrix Out = createMat(_rows, _cols);
	initMat(Out, 1.00);
	return Out;
}


// Create identity matrix
extern Matrix eye(int _rows, int _cols)
{
	Matrix Out = createMat(_rows, _cols);
	for (int i = 0; i < _rows; i++)
	{
		for (int j = 0; j < _cols; j++)
		{
			if (i == j)
			{
				Out.at[i][j] = 1.00;
			}
			else
			{
				Out.at[i][j] = 0.00;
			}
		}
	}
	return Out;
}


// Matrix subtraction
extern	Matrix	subMat(Matrix _A, Matrix _B) {
	if (_A.cols != _B.cols || _A.rows != _B.rows)
	{
		printf("SubMat error!! : Size is unsame");
	}
	Matrix Out = createMat(_A.rows, _A.cols);
	for (int i = 0; i < _A.rows; i++)
	{
		for (int j = 0; j < _A.cols; j++)
		{
			Out.at[i][j] = _A.at[i][j] - _B.at[i][j];
		}
	}
	return Out;
}


// Multiply  matrix A and matrix B  OUT=AB
extern	Matrix	multMat(Matrix _A, Matrix _B) {
	if (_A.cols != _B.rows) {
		printf("Matrix dimensions do not match for multiplication.\n");
	}
	Matrix Out = createMat(_A.rows, _B.cols);
	for (int i = 0; i < _A.rows; i++) {
		for (int j = 0 ;  j < _B.cols; j++) {
			Out.at[i][j] = 0;  // �ʱ�ȭ
			for (int k = 0; k < _A.cols; k++) {
				Out.at[i][j] += _A.at[i][k] * _B.at[k][j];
			}
		}
	}
	return Out;//freeMat(Out); ������ ��.

}


// Multiply matrix A with a scalar k
extern Matrix smultMat(Matrix _A, double _k) {
	Matrix Out = createMat(_A.rows, _A.cols);  // ��� ũ�⸦ �����ϰ� ����
	for (int i = 0; i < _A.rows; i++) {
		for (int j = 0; j < _A.cols; j++) {
			Out.at[i][j] = _A.at[i][j] * _k;  // �� ��ҿ� ��Į�� _k ���ϱ�
		}
	}
	return Out;
}


// Create Transpose matrix
extern Matrix transpose(Matrix _A) {
	Matrix Out = createMat(_A.cols, _A.rows);  // ��ġ ����� ��� ���� �ݴ�
	for (int i = 0; i < _A.rows; i++) {
		for (int j = 0; j < _A.cols; j++) {
			Out.at[j][i] = _A.at[i][j];  // ��� ���� ��ȯ�Ͽ� �� ����
		}
	}
	return Out;
}


// Copy matrix
extern	Matrix	copyMat(Matrix _A) {
	Matrix Out = createMat(_A.rows, _A.cols);
	for (int i = 0; i < _A.rows; i++)
	{
		for (int j = 0; j < _A.cols; j++)
		{
			Out.at[i][j] = _A.at[i][j];
		}
	}
	return Out;
}

void gaussElim(Matrix A, Matrix b, Matrix U, Matrix d, Matrix P)
{
	//A = multMat(P, A);
	for (int i = 0; i < A.rows; i++)
	{
		for (int j = 0; j < A.cols; j++)
		{
			U.at[i][j] = A.at[i][j];
		}
	}
	for (int i = 0; i < b.rows; i++)
	{
		for (int j = 0; j < b.cols; j++)
		{
			d.at[i][j] = b.at[i][j];
		}
	}
	for (int k = 0; k < A.cols-1; k++)
	{
		for (int i = k+1; i < A.rows; i++)
		{
			double factor = U.at[i][k] / U.at[k][k];//������ ���� ����
			for (int j = k; j < A.cols; j++)
			{
				U.at[i][j] = U.at[i][j] - factor * U.at[k][j];
			}
			d.at[i][0] = d.at[i][0] - factor * d.at[k][0];
		}
	}
}

void backsub(Matrix U, Matrix& y, Matrix& x)
{
	int m = U.rows;
	int n = U.cols;
	x.at[m - 1][0] = y.at[m - 1][0] / U.at[m - 1][m - 1];
	for (int i = m-2; i >=0; i--)
	{
		for (int j = i + 1; j < n; j++)
		{
			y.at[i][0] = y.at[i][0] - U.at[i][j] * x.at[j][0];
		}
		x.at[i][0] = y.at[i][0] / U.at[i][i];
	}
}

void fwdsub(Matrix L, Matrix& b, Matrix& y)
{
	for (int i = 0; i < L.rows; i++)
	{
		double sum = b.at[i][0];

		for (int j = 0; j < i; j++) {
			sum -= L.at[i][j] * y.at[j][0];
		}

		y.at[i][0] = sum / L.at[i][i];
	}
}


void Pivot(Matrix A, Matrix& P)
{
	//Make P identity M
	for (int i = 0; i < A.rows; i++)
	{
		for (int j = 0; j < A.cols; j++)
		{
			if (i == j)
			{
				P.at[i][j] = 1.00;
			}
			else
			{
				P.at[i][j] = 0.00;
			}
		}
	}

	//Pivoting if A pivot is 0.
	if (A.at[0][0] == 0)
	{
		for (int i = 1; i < A.rows; i++)
		{
			if (A.at[i][0] != 0)
			{
				for (int k = 0; k < A.rows; k++)
				{
					P.at[0][k] = 0;
					P.at[i][k] = 0;
				}
				P.at[0][i] = 1;
				P.at[i][0] = 1;
				break;
			}
		}
	}
	//printMat(P, "P");
}

void LUdecomp(Matrix A, Matrix& L, Matrix& U, Matrix& P)
{
	Pivot(A, P);

	A = multMat(P, A);
	Matrix Atemp = copyMat(A);
	Matrix Ltemp = eye(A.rows, A.cols);

	//LU Decomposition --> Find inverse L
	for (int k = 0; k < A.rows - 1; k++)
	{
		for (int i = k+1; i < A.rows; i++)
		{
			Ltemp.at[i][k] = -(A.at[i][k]) / (A.at[k][k]);
			L.at[i][k] = -(A.at[i][k]) / (A.at[k][k]);
		}
		A = multMat(L, A);
		L = eye(A.rows, A.cols);
	}
	U = copyMat(A);
	//printMat(U, "U");

	L = copyMat(Ltemp);
	for (int i = 0; i < A.rows; i++)
	{
		for (int j = 0; j < A.cols; j++)
		{
			if (i > j)
			{
				L.at[i][j] = -L.at[i][j];
			}
		}
	}
	//printMat(L, "L");

	A = copyMat(Atemp);
	//printMat(A, "A");

	freeMat(Atemp);
	freeMat(Ltemp);
}


void solveLU(Matrix L, Matrix U, Matrix P, Matrix b, Matrix& x)
{
	Matrix Pb = multMat(P, b);
	Matrix y = copyMat(b);
	fwdsub(L, b, y);
	backsub(U, y, x);
	freeMat(y);
	freeMat(Pb);
}

void invMat(Matrix A, Matrix& Ainv)
{
	int n = A.rows;
	int m = A.cols;
	if (n != m)
	{
		printf("It is not Square Matrix!");
		return;
	}
	Matrix P = eye(n, m);
	Pivot(A, P);
	Matrix L = eye(n, m);
	Matrix U = eye(n, m);
	LUdecomp(A, L, U, P);

	//Check if it is Singular Matrix
	for (int i = 0; i < m; i++)
	{
		if (U.at[i][i] == 0.00)
		{
			printf("It is Singular Matrix!");
			return;
		}
	}
	// b�� ��������� �Ǹ�, x�� Ainv�� �ȴ�.
	Matrix b = eye(n, m);
	for (int k = 0; k < A.cols; k++)
	{
		Matrix col_b = zeros(A.rows, 1);
		Matrix col_Ainv = zeros(A.rows, 1);

		//K�� ���� �� ����� �����Ѵ�.
		for (int i = 0; i < A.rows; i++)
		{
			col_b.at[i][0] = b.at[i][k];
		}
		solveLU(L, U, P, col_b, col_Ainv);

		//���� col_Ainv���� Ainv�� ����Ѵ�.
		for (int i = 0; i < A.rows; i++)
		{
			Ainv.at[i][k] = col_Ainv.at[i][0];
		}
		freeMat(col_b);
		freeMat(col_Ainv);
	}

	freeMat(P);
	freeMat(L);
	freeMat(U);
	freeMat(b);
}


double norm02(Matrix A)
{
	double out;
	double sum = 0.0;

	for (int i = 0; i < A.cols; i++)
	{
		sum = sum + pow(A.at[i][0], 2);
	}
	out = sqrtf(sum);
	return out;
}

double norm_mat(Matrix A)
{
	double out;
	double sum = 0.0;
	for (int j = 0; j < A.cols; j++)
	{
		for (int i = 0; i < A.rows; i++)
			{
				sum = sum + pow(A.at[i][j], 2);
			}
	}
	
	out = sqrtf(sum);
	return out;
}


extern Matrix householder(Matrix v)
{
	Matrix I = eye(v.rows, v.rows);
	Matrix v_vT = multMat(v, transpose(v));
	Matrix vT_v = multMat(transpose(v), v);

	double norm_v_square = vT_v.at[0][0];
	if (norm_v_square == 0.0) {
		printf("Error:v is a zero vector\n");
		freeMat(I);
		freeMat(v_vT);
		freeMat(vT_v);
		return I;
	}

	double scalar = 2.0 / vT_v.at[0][0];

	Matrix H = subMat(I, smultMat(v_vT, scalar));
	freeMat(I);
	freeMat(v_vT);
	freeMat(vT_v);

	return H;
}

//eigen
void QRdecomp(Matrix A, Matrix &R, Matrix &Q) 
{
	if (A.rows != A.cols) {
		printf("A is not a square Matrix!!");
		return;
	}

	// Initialize R, c, e, v, H, and Q matrices
	R = copyMat(A);
	Q = eye(A.rows, A.cols);   // Identity matrix for Q

	// Householder transformations
	for (int j = 0; j < A.cols; j++) {
		// Calculate vector c
		Matrix c = createMat(R.cols, 1);
		for (int i = 0; i < R.cols; i++) {
			c.at[i][0] = R.at[i][j];
		}
		for (int i = 0; i < j; i++)
		{
			c.at[i][0] = 0.0;
		}

		// Calculate vector e
		Matrix e = zeros(R.cols, 1);
		e.at[j][0] = (c.at[j][0] < 0) ? -1 : 1;

		// Calculate vector v
		double norm_c = norm02(c);
		Matrix v = createMat(R.rows, 1);
		for (int i = 0; i < R.rows; i++) {
			v.at[i][0] = c.at[i][0] + norm_c * e.at[i][0];
		}

		// Calculate Householder matrix H
		Matrix H = householder(v);

		// Update Q and R using Householder matrix H
		Matrix newQ = multMat(Q, H);
		freeMat(Q);
		Q = newQ;

		Matrix newR = multMat(H, R);
		freeMat(R);
		R = newR;

		// Free the temporary matrix H after its usage
		freeMat(H);
		freeMat(c);
		freeMat(e);
		freeMat(v);
	}
	
}

Matrix eigval(Matrix A) 
{
	//Matrix A�� �밢���п� 0�� �ִ°� ����
	for (int i = 0; i < A.cols; i++)
	{
		if (A.at[i][i] == 0)
		{
			A.at[i][i] = 0.000001;
		}
	}



	int N = 100;
	Matrix U = copyMat(A);

	for (int i = 0; i < N; i++) {
		Matrix R = createMat(A.rows, A.cols);
		Matrix Q = createMat(A.rows, A.cols);

		QRdecomp(U, R, Q);   // QR ���� ����

		Matrix newU = multMat(R, Q);   // �� U �޸� �Ҵ�
		freeMat(U);                    // ���� U �޸� ����
		U = newU;                      // �� U �޸𸮸� U�� �Ҵ�

		freeMat(R);                    // R �޸� ����
		freeMat(Q);                    // Q �޸� ����
	}

	//�������� ũ���� ����
	for (int i = 0; i < U.rows - 1; i++) {
		int maxIdx = i;
		for (int j = i + 1; j < U.rows; j++) {
			if (U.at[j][j] > U.at[maxIdx][maxIdx]) {
				maxIdx = j;
			}
		}
		if (maxIdx != i) {
			double temp = U.at[i][i];
			U.at[i][i] = U.at[maxIdx][maxIdx];
			U.at[maxIdx][maxIdx] = temp;
		}
	}
	

	// ������ �������� ���
	Matrix eigen = createMat(U.rows, 1);

	for (int i = 0; i < U.rows; i++) {
		eigen.at[i][0] = U.at[i][i];
	}

	freeMat(U);

	return eigen;
}

Matrix eigvec(Matrix A)
{
	//Matrix A�� �밢���п� 0�� �ִ°� ����
	for (int i = 0; i < A.cols; i++)
	{
		if (A.at[i][i] == 0)
		{
			A.at[i][i] = 0.000001;
		}
	}

	int N = 100;
	Matrix U = copyMat(A);

	for (int i = 0; i < N; i++) {
		Matrix R = createMat(A.rows, A.cols);
		Matrix Q = createMat(A.rows, A.cols);

		QRdecomp(U, R, Q);   // QR ���� ����

		Matrix newU = multMat(R, Q);   // �� U �޸� �Ҵ�
		freeMat(U);                    // ���� U �޸� ����
		U = newU;                      // �� U �޸𸮸� U�� �Ҵ�

		freeMat(R);                    // R �޸� ����
		freeMat(Q);                    // Q �޸� ����
	}

	//�������� ũ���� ����
	for (int i = 0; i < U.rows - 1; i++) {
		int maxIdx = i;
		for (int j = i + 1; j < U.rows; j++) {
			if (U.at[j][j] > U.at[maxIdx][maxIdx]) {
				maxIdx = j;
			}
		}
		if (maxIdx != i) {
			double temp = U.at[i][i];
			U.at[i][i] = U.at[maxIdx][maxIdx];
			U.at[maxIdx][maxIdx] = temp;
		}
	}


	//eigen vector matrix V
	Matrix V = eye(U.rows, U.cols);

	if (U.rows == 3)
	{
		for (int i = 0; i < U.rows; i++)
		{
			//Matrix eigv = zeros(U.rows, 1);
			//eigv.at[i][0] = 1.0;
			//B = (A - Lambda * I)
			Matrix B = subMat(A , smultMat(eye(A.cols, A.rows), U.at[i][i]));
			

			if (i == 0)
			{
				//eigen_col = inv(b4)*b2
				Matrix b4 = zeros(2, 2);
				Matrix b2 = zeros(2, 1);

				b4.at[0][0] = B.at[1][1];
				b4.at[0][1] = B.at[1][2];
				b4.at[1][0] = B.at[2][1];
				b4.at[1][1] = B.at[2][2];
				b2.at[0][0] = -B.at[1][0];
				b2.at[1][0] = -B.at[2][0];

				Matrix inv_b4 = copyMat(b4);
				invMat(b4, inv_b4);


				//eigenvector column
				Matrix eigen_col = multMat(inv_b4, b2);




				V.at[1][0] = eigen_col.at[0][0];
				V.at[2][0] = eigen_col.at[1][0];

				double norm = sqrtf(1.0 + powf(V.at[1][0], 2.0) + powf(V.at[2][0], 2.0));
				if (norm == 0)
				{
					printf("divided by zero");
				}
				V.at[0][0] = V.at[0][0] / norm;
				V.at[1][0] = V.at[1][0] / norm;
				V.at[2][0] = V.at[2][0] / norm;

				freeMat(inv_b4);
				freeMat(eigen_col);
				freeMat(b4);
				freeMat(b2);
			}
			else if(i == 1)
			{
				//eigen_col = inv(b4)*b2
				Matrix b4 = zeros(2, 2);
				Matrix b2 = zeros(2, 1);

				b4.at[0][0] = B.at[0][0];
				b4.at[0][1] = B.at[0][2];
				b4.at[1][0] = B.at[2][0];
				b4.at[1][1] = B.at[2][2];
				b2.at[0][0] = -B.at[0][1];
				b2.at[1][0] = -B.at[2][1];

				Matrix inv_b4 = copyMat(b4);
				invMat(b4, inv_b4);


				//eigenvector column
				Matrix eigen_col = multMat(inv_b4, b2);

				V.at[0][1] = eigen_col.at[0][0];
				V.at[2][1] = eigen_col.at[1][0];

				double norm = sqrtf(1.0 + powf(V.at[0][1], 2.0) + powf(V.at[2][1], 2.0));
				if (norm == 0)
				{
					printf("divided by zero");
				}
				V.at[0][1] = V.at[0][1] / norm;
				V.at[1][1] = V.at[1][1] / norm;
				V.at[2][1] = V.at[2][1] / norm;

				freeMat(inv_b4);
				freeMat(eigen_col);
				freeMat(b4);
				freeMat(b2);
			}
			else
			{
				//eigen_col = inv(b4)*b2
				Matrix b4 = zeros(2, 2);
				Matrix b2 = zeros(2, 1);

				b4.at[0][0] = B.at[0][0];
				b4.at[0][1] = B.at[0][1];
				b4.at[1][0] = B.at[1][0];
				b4.at[1][1] = B.at[1][1];
				b2.at[0][0] = -B.at[0][2];
				b2.at[1][0] = -B.at[1][2];

				Matrix inv_b4 = copyMat(b4);
				invMat(b4, inv_b4);


				//eigenvector column
				Matrix eigen_col = multMat(inv_b4, b2);


				V.at[0][2] = eigen_col.at[0][0];
				V.at[1][2] = eigen_col.at[1][0];

				double norm = sqrtf(1.0 + powf(V.at[0][2], 2.0) + powf(V.at[1][2], 2.0));
				if (norm == 0)
				{
					printf("divided by zero");
				}
				V.at[0][2] = V.at[0][2] / norm;
				V.at[1][2] = V.at[1][2] / norm;
				V.at[2][2] = V.at[2][2] / norm;

				freeMat(inv_b4);
				freeMat(eigen_col);
				freeMat(b4);
				freeMat(b2);
			}
			freeMat(B);
			//freeMat(eigv);
		}

		return V;
	}
	else if (U.rows == 2)
	{
		Matrix V = eye(2, 2);
		for (int i = 0; i < U.rows; i++)
		{
			if (i == 0)
			{
				//B = (A - Lambda * I)
				Matrix B = subMat(A, smultMat(eye(A.cols, A.rows), U.at[i][i]));
				V.at[1][0] = -B.at[0][0] / B.at[0][1];


				freeMat(B);
				double norm = sqrtf(1.0 + powf(V.at[1][0], 2.0));
				if (norm == 0)
				{
					printf("divided by zero!!");
				}
				V.at[0][0] = V.at[0][0] / norm;
				V.at[1][0] = V.at[1][0] / norm;
			}
			else if (i == 1)
			{
				Matrix B = subMat(A, smultMat(eye(A.cols, A.rows), U.at[i][i]));
				V.at[0][1] = -B.at[0][1] / B.at[0][0];

				freeMat(B);
				double norm = sqrtf(1.0 + powf(V.at[0][1], 2.0));
				if (norm == 0)
				{
					printf("divided by zero!!");
				}
				V.at[1][1] = V.at[1][1] / norm;
				V.at[0][1] = V.at[0][1] / norm;
			}
		}
		return V;
	}
	else
	{
		printf("It is only for 2 or 3");
		return U;
	}
	freeMat(U);

}

void eig(Matrix A, Matrix& V, Matrix& D)
{
	//D ���
	int N = 100;
	for (int i = 0; i < N; i++) {
		Matrix R = createMat(A.rows, A.cols);
		Matrix Q = createMat(A.rows, A.cols);

		QRdecomp(D, R, Q);   // QR ���� ����

		Matrix newD = multMat(R, Q);   // �� U �޸� �Ҵ�
		freeMat(D);                    // ���� U �޸� ����
		D = newD;                      // �� U �޸𸮸� U�� �Ҵ�

		freeMat(R);                    // R �޸� ����
		freeMat(Q);                    // Q �޸� ����
	}


	//V���
	V = eigvec(A);
}




//Polyfit


// Create a matrix from 1D-array
Matrix	arr2Mat(double* _1Darray, int _rows, int _cols)
{
	Matrix Output = createMat(_rows, _cols);

	for (int i = 0; i < _rows; i++)
		for (int j = 0; j < _cols; j++)
			Output.at[i][j] = _1Darray[i * _cols + j];

	return Output;
}

// Returns the parameters of the linear least square function.
Matrix	linearFit_mat(Matrix _vecX, Matrix _vecY) {

	// Initialization
	double Sx = 0;
	double Sxx = 0;
	double Sxy = 0;
	double Sy = 0;
	double a1 = 0;
	double a0 = 0;


	// Check m = length(X) and length(Y)
	int mx = _vecX.rows;
	int my = _vecY.rows;

	// Is length(X)~= length(Y) ? Exit: Continue
	// [YOUR CODE GOES HERE]
	if ((mx != my) || (mx == 1))
	{
		printf("ERROR: The number of elements in x must be the same as in y.");
		a1 = 0; a0 = 0;
	}

	// Solve for Sx, Sxx, Sy, Sxy,
	// [YOUR CODE GOES HERE]
	for (int k = 0; k < mx; k++)
	{
		Sx = Sx + _vecX.at[k][0];
		Sxx = Sxx + _vecX.at[k][0] * _vecX.at[k][0];
		Sxy = Sxy + _vecX.at[k][0] * _vecY.at[k][0];
		Sy = Sy + _vecY.at[k][0];
	}

	// Solve for a1, a2
	// [YOUR CODE GOES HERE]
	a1 = (mx * Sxy - Sx * Sy) / (mx * Sxx - Sx * Sx);
	a0 = (Sxx * Sy - Sx * Sxy) / (mx * Sxx - Sx * Sx);

	// Return z = [a0, a1]
	double z_array[] = { a0, a1 };
	return arr2Mat(z_array, 2, 1);
}



Matrix	polyFit_mat(Matrix _vecX, Matrix _vecY, int orderN) {

	// Initialization	
	Matrix vecZ = zeros(orderN + 1, 1);
	// [YOUR CODE GOES HERE]
	// [YOUR CODE GOES HERE]


	// Check m = length(X) and length(Y)
	int mx = _vecX.rows;
	int my = _vecY.rows;

	// Is length(X)~= length(Y) ? Exit: Continue
	// [YOUR CODE GOES HERE]
	if (mx != my)
	{
		printf("Error: ERROR: The number of elements in x must be the same as in y.");
	}
	if (mx < my || my < 1)
	{
		printf("ERROR: The order of polynomial must be smaller than m and bigger than 1");
	}

	// If n=1, use linearFit
	// [YOUR CODE GOES HERE]
	if (orderN == 1)
	{
		vecZ = linearFit_mat(_vecX, _vecY);
		return vecZ;
	}
	else if (orderN > 1)
	{
		// Calculate Sx(i)=sum(x[k]^(i)), for i=0 to 2n  #(2n+1) 
		// Note: Sx[0] to Sx[n*2] : (2n+1,1)	
		// [YOUR CODE GOES HERE]
		Matrix Sx = zeros(2 * orderN + 1, 1);
		double Sx_temp;
		for (int i = 0; i < 2 * orderN + 1; i++)
		{
			Sx_temp = 0;
			for (int k = 0; k < mx; k++)
			{
				Sx_temp = Sx_temp + pow(_vecX.at[k][0], i);
			}
			Sx.at[i][0] = Sx_temp;
		}

		// Construct matrix S with Sx(i).  
		// [YOUR CODE GOES HERE]
		Matrix S = zeros(orderN + 1, orderN + 1);
		for (int i = 0; i < orderN + 1; i++)
		{
			for (int j = 1; j < orderN + 2; j++)
			{
				S.at[i][j - 1] = Sx.at[i + j - 1][0]; //��Ʈ������ i+j+1�̾��µ� 2������.
			}
		}

		// Construct vector b=(A'y) from Sxy(j) = sum(y * (x ^ (j))), for j = 0 to n 
		// [YOUR CODE GOES HERE]
		Matrix Sxy = zeros(orderN + 1, 1);
		for (int i = 0; i < orderN + 1; i++)
		{
			double Sxytemp = 0.0;
			for (int k = 0; k < mx; k++)
			{
				Sxytemp = Sxytemp + _vecY.at[k][0] * pow(_vecX.at[k][0], i);
			}
			Sxy.at[i][0] = Sxy.at[i][0] + Sxytemp;
		}


		// Calculate optimal Z=inv(S)*(b)
		// [YOUR CODE GOES HERE]
		Matrix invX = copyMat(S);
		invMat(S, invX);

		vecZ = multMat(invX, Sxy);


		freeMat(invX);
		freeMat(S);
		freeMat(Sxy);
		freeMat(Sx);
		return vecZ;
	}
}


void linearFit(double vecZ[], double vecX[], double vecY[], int dataL) {

	// Initialization
	double Sx = 0;
	double Sxx = 0;
	double Sxy = 0;
	double Sy = 0;
	double a1 = 0;
	double a0 = 0;



	// NOTE:
	//		int mx = sizeof(vecX) / sizeof(vecX[0]); // <-- Does not work inside a function
	//		You need to pass the dataLength as an argument.
	//		OR you can use Option 2:  Matrix structure

	// Check m = length(X) and length(Y)
	int mx = dataL;
	int my = dataL;

	// Is length(X)~= length(Y) ? Exit: Continue
	// [YOUR CODE GOES HERE]
	if ((mx != my) || (mx == 1))
	{
		printf("ERROR: The number of elements in x must be the same as in y.");
		a1 = 0; a0 = 0;
	}

	// Solve for Sx, Sxx, Sy, Sxy,
	// [YOUR CODE GOES HERE]
	for (int k = 0; k < mx; k++)
	{
		Sx = Sx + vecX[k];
		Sxx = Sxx + vecX[k] * vecX[k];
		Sxy = Sxy + vecX[k] * vecY[k];
		Sy = Sy + vecY[k];
	}

	// Solve for a1, a2
	// [YOUR CODE GOES HERE]
	a1 = (mx * Sxy - Sx * Sy) / (mx * Sxx - Sx * Sx);
	a0 = (Sxx * Sy - Sx * Sxy) / (mx * Sxx - Sx * Sx);

	// Return z = [a0, a1]
	vecZ[0] = a0;
	vecZ[1] = a1;
}

void polyFit(double vecZ[], double vecX[], double vecY[], int dataL, int orderN) {

	// Initialization
	double a1 = 0;
	double a0 = 0;
	// [YOUR CODE GOES HERE]
	// [YOUR CODE GOES HERE]


	// Check m = length(X) and length(Y)
	double mx = dataL;
	double my = dataL;

	// Is length(X)~= length(Y) ? Exit: Continue
	// NOTE:
	//		int mx = sizeof(vecX) / sizeof(vecX[0]); // <-- Does not work inside a function
	//		You need to pass the dataLength as an argument.
	//		OR you can use Option 2:  Matrix structure
	if (mx != my)
	{
		printf("Error: ERROR: The number of elements in x must be the same as in y.");
	}
	if (mx < my || my < 1)
	{
		printf("ERROR: The order of polynomial must be smaller than m and bigger than 1");
	}


	// If n=1, use linearFit
	if (orderN == 1)
	{
		linearFit(vecZ, vecX, vecY, dataL);
		return;
	}
	else if (orderN > 1)
	{
		// Calculate Sx(i)=sum(x[k]^(i)), for i=0 to 2n  #(2n+1)
		// Note: Sx[0] to Sx[n*2] : (2n+1,1)
		// [YOUR CODE GOES HERE]
		Matrix Sx = zeros(2 * orderN + 1, 1);
		double Sx_temp;
		for (int i = 0; i < 2 * orderN + 1; i++)
		{
			Sx_temp = 0;
			for (int k = 0; k < mx; k++)
			{
				Sx_temp = Sx_temp + pow(vecX[k], i);
			}
			Sx.at[i][0] = Sx_temp;
		}


		// Construct matrix S with Sx(i).
		// [YOUR CODE GOES HERE]
		Matrix S = zeros(orderN + 1, orderN + 1);
		for (int i = 0; i < orderN + 1; i++)
		{
			for (int j = 1; j < orderN + 2; j++)
			{
				S.at[i][j - 1] = Sx.at[i + j - 1][0]; //��Ʈ������ i+j+1�̾��µ� 2������.
			}
		}


		// Construct vector b=(A'y) from Sxy(j) = sum(y * (x ^ (j))), for j = 0 to n
		// [YOUR CODE GOES HERE]
		Matrix Sxy = zeros(orderN + 1, 1);
		for (int i = 0; i < orderN + 1; i++)
		{
			double Sxytemp = 0.0;
			for (int k = 0; k < mx; k++)
			{
				Sxytemp = Sxytemp + vecY[k] * pow(vecX[k], i);
			}
			Sxy.at[i][0] = Sxy.at[i][0] + Sxytemp;
		}


		// Calculate optimal Z=inv(S)*(b)
		// [YOUR CODE GOES HERE]
		Matrix invX = copyMat(S);
		invMat(S, invX);

		Matrix tempZ = multMat(invX, Sxy);
		for (int i = 0; i < orderN+1; i++)
		{
			vecZ[i] = tempZ.at[i][0];
		}


		// Return z
		freeMat(invX);
		freeMat(S);
		freeMat(Sxy);
		freeMat(Sx);
		freeMat(tempZ);
		return;
	}
}


Matrix expFit_mat(Matrix _X, Matrix _Y)
{
	int dataL = _Y.rows;
	Matrix lnYdata = copyMat(_Y);
	for (int i = 0; i < dataL; i++)
	{
		lnYdata.at[i][0] = log(_Y.at[i][0]);
	}
	Matrix C = linearFit_mat(_X, lnYdata);
	double Q3_m = C.at[1][0];
	double Q3_R = 0.005; //���װ�
	double Q3_c = -1.0 / (Q3_R * Q3_m);
	double Q3_b = exp(C.at[0][0]);
	double Q3_V0 = Q3_b;
	Matrix out = zeros(2, 1);
	out.at[0][0] = Q3_c; //C//������ �з�
	out.at[1][0] = Q3_V0; //V0 


	freeMat(lnYdata);
	freeMat(C);
	return out;
}



void expFit(double z[], double _x[], double _y[], double dataL)
{
	double lnYdata[15] = { 0 };
	for (int i = 0; i < 15; i++)
	{
		lnYdata[i] = log(_y[i]);
	}
	double C[2] = { 0 };
	linearFit(C, _x, lnYdata, 15);
	double Q3_m = C[1];
	double Q3_R = 0.005;
	double Q3_c = -1.0 / (Q3_R * Q3_m);
	double Q3_b = exp(C[0]);
	double Q3_V0 = Q3_b;
	z[0] = Q3_c;
	z[1] = Q3_V0;
}


//Nonlinear sys

Matrix nonlinearSys(Matrix Funcs(Matrix _Z), Matrix Jacob(Matrix _Z), Matrix _Z0, double tol) {
	// Initialization
	int n = _Z0.rows;
	double loss = 10;
	Matrix J = zeros(n, n);
	Matrix F = zeros(n, 1);
	Matrix H = zeros(n, 1);
	Matrix Z = copyMat(_Z0); //�Էº��� ����


	// Initial condition
	F = Funcs(Z);

	for (int k = 0; k < 20; k++) {

		J = Jacob(Z);

		// [TO-DO]  YOUR CODE GOES HERE
		// F =-1*F;
		// F�� �������� ������� ����� �����߾�� �Ѵ�.
		for (int i = 0; i < n; i++)
		{
			F.at[i][0] = -F.at[i][0];
		}

		// [TO-DO]  YOUR CODE GOES HERE
		// Solve for H in  JH = (-F)	
		Matrix invJ = zeros(J.rows, J.cols);
		invMat(J, invJ);
		H = multMat(invJ, F);
		freeMat(invJ);

		// [TO-DO]  YOUR CODE GOES HERE
		//	Z = Z + H;
		// Z�� �������� ������� ����� �����ؾ� for�� �Ǽ� ���Ѵ�.
		for (int i = 0; i < n; i++)
		{
			Z.at[i][0] += H.at[i][0];
		}


		// After Z update, print loss
		F = Funcs(Z);


		// [TO-DO]  YOUR CODE GOES HERE
		//Z������ �� ���� �����ؼ� ��Ʈ���� ��.
		loss = norm02(F);   // sqrt((F.at[0][0])^2+(F.at[1][0])^2+...)


		printf("iter =%d \t x=%0.3f \t y=%0.3f \t loss=%0.3f\n", k, Z.at[0][0], Z.at[1][0], loss);

		if (loss < tol) {
			printf("Early Termination\n\r");
			freeMat(J);
			freeMat(F);
			freeMat(H);
			return Z;
		}
	}

	freeMat(J);
	freeMat(F);
	freeMat(H);

	return Z;
}