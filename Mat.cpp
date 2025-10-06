/*
The implementation of the data structure of matrix.
Basic algebraic operations of matrix.
Special type matrix.
*/

#include "Mat.hpp"
#include <vector>
#include <iostream>
using namespace std;

Mat transpose(Mat M) {
	Mat op(M.columns, M.rows);
	for (int i = 0; i < M.rows; ++i) {
		for (int j = 0; j < M.columns; ++j) {
			op.mem[op.columns*i + j] = M.mem[M.columns*j + i];
		}
	}
	return op;
}

Mat zeros(int r, int c) {
	Mat op(r, c);
	for (int i = 0; i < r*c; ++i) op[i] = 0;
	return op;
}

Mat zeros_like(Mat a) {
	return zeros(a.rows, a.columns);
}

Mat eye(int n) {
	Mat op = zeros(n, n);
	for (int i = 0; i < n; ++i) op(i, i) = 1;
	return op;
}

Mat operator+(const Mat &A, const Mat &B) {
	Mat op(A.rows, A.columns);
	for (int i = 0; i < A.rows*A.columns; ++i) op.mem[i] = A.mem[i] + B.mem[i];
	return op;
}

Mat operator+(double s, const Mat &A) {
	Mat op(A.rows, A.columns);
	for (int i = 0; i < A.rows*A.columns; ++i) op.mem[i] = A.mem[i] + s;
	return op;
}

Mat operator+(const Mat &A, double s) {
	return s + A;
}

Mat operator-(const Mat &A, const Mat &B) {
	Mat op(A.rows, A.columns);
	for (int i = 0; i < A.rows*A.columns; ++i) op.mem[i] = A.mem[i] - B.mem[i];
	return op;
}

Mat operator-(const Mat& A) {
	return (-1.) * A;
}

Mat operator-(double s, const Mat &A) {
	return s + (-A);
}

Mat operator-(const Mat &A, double s) {
	return (-s) + A;
}

Mat operator*(const Mat &A, const Mat &B) {
	Mat op = zeros(A.rows, A.columns);
	double sum;
	for (int i = 0; i < A.rows; ++i) {
		for (int j = 0; j < B.columns; ++j) {
			sum = 0;
			for (int k = 0; k < A.columns; ++k) sum += A.mem[A.columns*i + k] * B.mem[B.columns*k + j];
			op.mem[op.columns*i + j] = sum;
		}
	}
	return op;
}

Mat operator*(double a, const Mat &A) {
	Mat op(A.rows, A.columns);
	for (int i = 0; i < A.rows*A.columns; ++i) op.mem[i] = a * A.mem[i];
	return op;
}

Mat operator*(const Mat& A, double s) {
	return s * A;
}

