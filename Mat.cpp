#include <stdlib.h>
#include <vector>
#include <iostream>
using namespace std;

struct pos {
	int row; int column;
};

class Mat {
public:
	Mat() {mem = nullptr;}
	Mat(int r, int c) {
		rows = r, columns = c;
		mem = (double*)calloc(rows*columns, sizeof(double));
	};
	Mat(int r, int c, double *l) {
		rows = r, columns = c;
		mem = (double*)calloc(rows*columns, sizeof(double));
		for (int i = 0; i < rows*columns; ++i) mem[i] = l[i];
	};
	Mat(const Mat &A) {
		rows = A.rows, columns = A.columns;
		mem = (double*)calloc(rows*columns, sizeof(double));
		for (int i = 0; i < rows*columns; ++i) mem[i] = A.mem[i];
	}
	~Mat() {if (mem) free(mem);}
	
	Mat &operator=(const Mat &A) {
		if (this == &A) return *this;
		rows = A.rows, columns = A.columns;
		mem = (double*)calloc(rows*columns, sizeof(double));
		for (int i = 0; i < rows*columns; ++i) mem[i] = A.mem[i];
		return *this;
	}
	
	double &operator()(int row, int column) {
		return mem[columns*row + column];
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
			for (int c = 0; c < mat.columns; ++c) cout << mat.mem[mat.columns*r + c] << " ";
			cout << endl;
		}
		return os;
	}
	
	friend Mat zeros(int r, int c);
	friend Mat eye(int n);
	friend Mat operator+(Mat a, Mat b);
	friend Mat operator-(Mat a, Mat b);
	friend Mat operator*(Mat a, Mat b);
	friend Mat operator*(double a, Mat b);
	
	int rows, columns;
private:
	double *mem;
};

Mat transpose(Mat M) {
	Mat op(M.columns, M.rows);
	double temp;
	for (int i = 0; i < M.rows; ++i) {
		for (int j = 0; j < M.columns; ++j) {
			op.mem[op.columns*i + j] = M.mem[M.columns*j + i];
		}
	}
	return op;
}

Mat zeros(int r, int c) {
	Mat op(r, c);
	for (int i = 0; i < r*c; ++i) op.mem[i] = 0;
	return op;
}

Mat zeros_like(Mat a) {
	return zeros(a.rows, a.columns);
}

Mat eye(int n) {
	Mat op = zeros(n, n);
	for (int i = 0; i < n; ++i) op.mem[n*i + i] = 1;
	return op;
}

Mat operator+(Mat a, Mat b) {
	Mat op(a.rows, a.columns);
	for (int i = 0; i < a.rows*a.columns; ++i) op.mem[i] = a.mem[i] + b.mem[i];
	return op;
}

Mat operator-(Mat a, Mat b) {
	Mat op(a.rows, a.columns);
	for (int i = 0; i < a.rows*a.columns; ++i) op.mem[i] = a.mem[i] - b.mem[i];
	return op;
}

Mat operator*(Mat a, Mat b) {
	Mat op = zeros(a.rows, b.columns);
	double sum;
	for (int i = 0; i < a.rows; ++i) {
		for (int j = 0; j < b.columns; ++j) {
			sum = 0;
			for (int k = 0; k < a.columns; ++k) sum += a.mem[a.columns*i + k] * b.mem[b.columns*k + j];
			op.mem[op.columns*i + j] = sum;
		}
	}
	return op;
}

