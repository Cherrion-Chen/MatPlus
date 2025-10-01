#include "include./MatPlus.hpp"
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
	double arr[9] = {1,2,3,4,1,2,1,3,3};
	Mat A(3, 3, arr);
	cout << fixed << setprecision(3);
	cout << A << endl;
	
	Mat B = inv(A);
	cout << "det(A)*det(inv(A)): " << det(A)*det(B) << endl << endl;
	cout << "inv(A): " << endl << B << endl;
	cout << "A*inv(A): " << endl << A * B << endl;
	
	Mat C = eye(3); Mat D = zeros(3, 3);
	Mat square = (2.*C)^2;
	cout << 2.*C << endl << square << endl;
	cout << row_cat(C, D) << endl << column_cat(C, D) << endl;
	vector<vector<Mat> > V = {{C, D}, {D, C}};
	Mat M = block(V);
	cout << M;
	
	cin >> arr[0];
}

