#ifndef EXTENSION_HPP
#define EXTENSION_HPP

#include "Mat.hpp"
#include <vector>
//using namespace std;

Mat operator^(const Mat &A, int n);
Mat map(double (*f)(double), Mat A);
Mat row_vector(int n, double *arr);
Mat column_vector(int n, double *arr);
Mat diag(int n, double *arr);
Mat row_cat(Mat A, Mat B);
Mat column_cat(Mat A, Mat B);
Mat block(vector<vector<Mat>> &blocks);

#endif
