#include "utils.h"
#include "global.h"
#include <iostream>


// Computes the determinant of a 4x4 matrix.
float determinant(float matrix[4][4], int n=4) {
	float det = 0;
	float submatrix[4][4];
	if (n == 2)
		return ((matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]));
	else {
		for (int x = 0; x < n; x++) {
			int subi = 0;
			for (int i = 1; i < n; i++) {
				int subj = 0;
				for (int j = 0; j < n; j++) {
					if (j == x)
						continue;
					submatrix[subi][subj] = matrix[i][j];
					subj++;
				}
				subi++;
			}
			det = det + (pow(-1, x) * matrix[0][x] * determinant(submatrix, n - 1));
		}
	}
	return det;
}


// Determines if point p is inside the circle defined by the triangle p0-p1-p2 (counterclockwise order)
bool point_in_circle(Trimpression_Mesh::Point p, 
						Trimpression_Mesh::Point p0, 
						Trimpression_Mesh::Point p1, 
						Trimpression_Mesh::Point p2)
{
	float matrix[4][4];

	matrix[0][0] = p0[0]; matrix[0][1] = p0[1]; matrix[0][2] = p0[0] * p0[0] + p0[1] * p0[1];
	matrix[1][0] = p1[0]; matrix[1][1] = p1[1]; matrix[1][2] = p1[0] * p1[0] + p1[1] * p1[1];
	matrix[2][0] = p2[0]; matrix[2][1] = p2[1]; matrix[2][2] = p2[0] * p2[0] + p2[1] * p2[1];
	matrix[3][0] = p[0]; matrix[3][1] = p[1]; matrix[3][2] = p[0] * p[0] + p[1] * p[1];
	
	matrix[0][3] = 1;
	matrix[1][3] = 1;
	matrix[2][3] = 1;
	matrix[3][3] = 1;

	float det = determinant(matrix);
	
	return det >= 0;
}
