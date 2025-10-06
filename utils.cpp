/*
Advanced matrix operations.
Matrix container.
*/

#include "utils.hpp"
#include <stdlib.h>
#include <cmath>
#include <iostream>
using namespace std;

Mat abs(Mat A) {
	Mat op(A.rows, A.columns);
	for (int i = 0; i < A.rows; ++i) {
		for (int j = 0; j < A.columns; ++j) op(i, j) = abs(A(i, j));
	}
	return op;
}

pos find_max(Mat A, int row_start, int column_start, int row_end, int column_end) {
	double max = A(row_start, column_start);
	pos op = {row_start, column_start};
	
	if (row_end == -1) row_end = A.rows;
	if (column_end == -1) column_end = A.columns;
	
	for (int i = row_start; i < row_end; ++i) {
		for (int j = column_start; j < column_end; ++j) {
			if (A(i, j) > A(op.row, op.column)) {
				op.row = i, op.column = j, max = A(i, j);
			}
		}
	}
	return op;
}

mat_tuple LUPQ(Mat A) {
	mat_tuple op;
	
	op.L = zeros(A.rows, A.rows);  // L 是 m×m 单位下三角矩阵
	op.U = A;  // U 是 m×n 上三角矩阵
	op.P = eye(A.rows);
	op.Q = eye(A.columns);
	op.n = 0;
	
	pos maxpos;
	for (int i = 0; i < min(A.rows, A.columns)-1; ++i) {
		maxpos = find_max(abs(op.U), i, i);
		
		if (maxpos.row != i) {
			op.U.swap_row(i, maxpos.row);
			op.L.swap_row(i, maxpos.row);
			op.P.swap_row(i, maxpos.row);
			++op.n;
		}
		if (maxpos.column != i) {
			op.U.swap_column(i, maxpos.column);
			op.Q.swap_column(i, maxpos.column);
			++op.n;
		}
		
		op.L(i, i) = 1;
		if (abs(op.U(i, i)) > 1e-16) {
			for (int j = i+1; j < A.rows; ++j) {
				op.L(j, i) = op.U(j, i) / op.U(i, i);
				for (int k = i; k < A.columns; ++k)
					op.U(j, k) -= op.L(j, i) * op.U(i, k);
			}
		}
	}
	op.L(A.rows-1, A.rows-1) = 1;
	
	return op;
}

double det(Mat A) {
	mat_tuple op = LUPQ(A);
	
	double d = 1;
	for (int i = 0; i < A.rows; ++i) 
		d *= op.U(i, i);
	
	if (op.n % 2) d = -d;
	return d;
}

Mat L_solve(Mat L, Mat y) {
	double *arr = new double[y.rows];
	arr[0] = y(0, 0) / L(0, 0);
	double sum;
	for (int i = 1; i < y.rows; ++i) {
		sum = 0;
		for (int j = 0; j < i; ++j) sum += L(i, j) * arr[j];
		arr[i] = (y(i, 0) - sum) / L(i, i);
	}
	Mat op(y.rows, 1, arr);
	delete []arr;
	return op;
}

Mat U_solve(Mat U, Mat y) {
	double *arr = new double[y.rows];
	arr[y.rows-1] = y(y.rows-1, 0) / U(y.rows-1, y.rows-1);
	double sum;
	for (int i = y.rows-2; i >=0; --i) {
		sum = 0;
		for (int j = y.rows-1; j > i; --j) sum += U(i, j) * arr[j];
		arr[i] = (y(i, 0) - sum) / U(i, i);
	}
	Mat op (y.rows, 1, arr);
	delete []arr;
	return op;
}

Mat solve(Mat A, Mat y) {
	mat_tuple MT = LUPQ(A);
	Mat x(y.rows, 1);
	x = L_solve(MT.L, MT.P*y);
	x = MT.Q * U_solve(MT.U, x);
	return x;
}

mat_tuple QR(Mat A) {
	mat_tuple op;
	op.Q = A, op.R = zeros_like(A);
	double proj, mod;
	for (int i = 0; i < A.columns; ++i) {
		for (int j = 0; j < i; ++j) {
			proj = 0;
			for (int k = 0; k < A.columns; ++k) proj += op.Q(k, i) * op.Q(k, j);
			op.R(j, i) = proj;
			for (int k = 0; k < A.columns; ++k) op.Q(k, i) -= proj * op.Q(k, j);
		}
		mod = 0;
		for (int k = 0; k < A.columns; ++k) mod += op.Q(k, i) * op.Q(k, i);
		mod = sqrt(mod);
		for (int k = 0; k < A.columns; ++k) op.Q(k, i) /= mod;
		op.R(i, i) = mod;
	}
	return op;
}

Mat QR_solve(Mat A, Mat y) {
	mat_tuple op = QR(A);
	Mat x(y.rows, 1);
	x = U_solve(op.R, transpose(op.Q)*y);
	return x;
}

Mat inv(Mat A) {
	Mat op = zeros_like(A);
	Mat y(A.rows, 1), x(A.rows, 1);
	for (int i = 0; i < A.columns; ++i) {
		y = zeros_like(y);
		y(i, 0) = 1;
		x = solve(A, y);
		for (int k = 0; k < A.rows; ++k) op(k, i) = x(k, 0);
	}
	return op;
}

