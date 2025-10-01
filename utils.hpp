#ifndef MATPLUS_HPP
#define MATPLUS_HPP

#include "Mat.hpp"

struct mat_tuple {
	Mat L, U, P, Q, R;
	int n;
};

Mat abs(Mat A);
pos find_max(Mat A, int row_start=0, int column_start=0, int row_end=-1, int column_end=-1);
mat_tuple LUPQ(Mat A);
Mat L_solve(Mat L, Mat y);
Mat U_solve(Mat U, Mat y);
Mat solve(Mat A, Mat y);
double det(Mat A);
mat_tuple QR(Mat A);
Mat QR_solve(Mat A, Mat y);
Mat inv(Mat A);

#endif
