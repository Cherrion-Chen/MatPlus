#include "Mat.cpp"
#include <stdlib.h>
#include <vector>
#include <iostream>
using namespace std;

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

