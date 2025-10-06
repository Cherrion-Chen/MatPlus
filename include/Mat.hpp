/*
The implementation of the data structure of matrix.
Basic algebraic operations of matrix.
Special type matrix.
*/

#ifndef MAT_HPP
#define MAT_HPP

#include <vector>
#include <iostream>
using namespace std;

struct pos {
	int row, column;
};

class Mat {
public:
	Mat() {mem = NULL;}
	Mat(int r, int c) {
		rows = r, columns = c;
		mem = new double[r*c];
	};
	Mat(int r, int c, double *l) {
		rows = r, columns = c;
		mem = new double[r*c];
		for (int i = 0; i < rows*columns; ++i) mem[i] = l[i];
	};
	Mat(const Mat &A) {
		rows = A.rows, columns = A.columns;
		mem = new double[A.rows*A.columns];
		for (int i = 0; i < rows*columns; ++i) mem[i] = A.mem[i];
	}
	~Mat() {if (mem) delete []mem;}
	
	Mat &operator=(const Mat &A) {
		if (this == &A) return *this;
		rows = A.rows, columns = A.columns;
		if (mem) delete []mem;
		mem = new double[A.rows*A.columns];
		for (int i = 0; i < rows*columns; ++i) mem[i] = A.mem[i];
		return *this;
	}
	
	double &operator()(int row, int column) {
		return mem[columns*row + column];
	}
	const double &operator()(int row, int column) const {
		return mem[columns*row + column];
	}
	double &operator[](int n) {
		return mem[n];
	}
	double &operator[](pos p) {
		return mem[columns*p.row + p.column];
	}
	
	void swap_row(int i, int j) {
		double temp;
		for (int k = 0; k < columns; ++k) {
			temp = mem[columns*i + k];
			mem[columns*i + k] = mem[columns*j + k];
			mem[columns*j + k] = temp;
		}
	}
	void swap_column(int i, int j) {
		double temp;
		for (int k = 0; k < rows; ++k) {
			temp = mem[columns*k + i];
			mem[columns*k + i] = mem[columns*k + j];
			mem[columns*k + j] = temp;
		}
	}
	
	friend Mat transpose(Mat M);
	
	friend ostream &operator<<(ostream &os, const Mat &mat) {
		for (int r = 0; r < mat.rows; ++r) {
			for (int c = 0; c < mat.columns-1; ++c) os << mat.mem[mat.columns*r + c] << ", ";
			os << mat.mem[mat.columns*r + mat.columns-1] << endl;
		}
		return os;
	}
	
	friend Mat operator+(const Mat &A, const Mat &B);
	friend Mat operator+(double s, const Mat &A);
	friend Mat operator+(const Mat &A, double s);
	friend Mat operator-(const Mat &A, const Mat &B);
	friend Mat operator-(const Mat& A);
	friend Mat operator-(double s, const Mat &A);
	friend Mat operator-(const Mat &A, double s);
	friend Mat operator*(const Mat &A, const Mat &B);
	friend Mat operator*(double a, const Mat &B);
	friend Mat operator*(const Mat& A, double s);
	
	int rows, columns;
private:
	double *mem;
};

Mat zeros(int r, int c);
Mat eye(int n);
Mat zeros_like(Mat A);

#endif
