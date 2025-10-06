/*
Vector matrix.
Block matrix.
*/

#include "extension.hpp"
#include <stdlib.h>
#include <functional>
#include <vector>
#include <iostream>
using namespace std;

Mat operator^(const Mat &A, int n) {
	Mat op = eye(A.rows);
	for (int i = 0; i < n; ++i) op = op * A;
	return op;
}

Mat apply_func(function<double(double)> f, Mat A) {
	Mat op(A.rows, A.columns);
	for (int i = 0; i < A.rows*A.columns; ++i) op[i] = f(A[i]);
	return op;
}

Mat row_vector(int n, double *arr) {
	Mat op(1, n, arr);
	return op;
}

Mat column_vector(int n, double *arr) {
	Mat op(n, 1, arr);
	return op;
}

Mat diag(int n, double *arr) {
	Mat op = zeros(n, n);
	for (int i = 0; i < n; ++i) op(i, i) = arr[i];
	return op;
}

Mat row_cat(Mat A, Mat B) {
	Mat op(A.rows, A.columns + B.columns);
	for (int i = 0; i < A.rows; ++i) {
		for (int j = 0; j < A.columns; ++j) op(i, j) = A(i, j);
		for (int j = 0; j < B.columns; ++j) op(i, A.columns+j) = B(i, j);
	}
	return op;
}

Mat column_cat(Mat A, Mat B) {
	Mat op(A.rows + B.rows, A.columns);
	for (int i = 0; i < A.rows; ++i) {
		for (int j = 0; j < A.columns; ++j) op(i, j) = A(i, j);
	}
	for (int i = 0; i< B.rows; ++i) {
		for (int j = 0; j < B.columns; ++j) op(A.rows+i, j) = B(i, j);
	}
	return op;
}

Mat block(vector<vector<Mat>> &blocks) {
	int rows = blocks[0][0].rows, columns = blocks[0][0].columns;
	Mat op(blocks.size()*rows, blocks[0].size()*columns);
	for (int i = 0; i < op.rows; ++i) {
		for (int j = 0; j < op.columns; ++j) {
			op(i, j) = blocks[i/rows][j/columns](i%rows, j%columns);
		}
	}
	return op;
}

