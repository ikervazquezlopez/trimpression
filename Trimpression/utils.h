#pragma once
#include "global.h"

float determinant(float matrix[4][4], int n);

bool point_in_circle(Trimpression_Mesh::Point p, 
						Trimpression_Mesh::Point p0, 
						Trimpression_Mesh::Point p1, 
						Trimpression_Mesh::Point p2);