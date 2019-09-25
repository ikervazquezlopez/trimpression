#include "utils.h"
#include "global.h"

bool point_in_circle(Trimpression_Mesh::Point p, 
						Trimpression_Mesh::Point p0, 
						Trimpression_Mesh::Point p1, 
						Trimpression_Mesh::Point p2)
{
	// Compute constant values in the formula
	float _2x10 = 2 * p1[0] - 2 * p0[0];
	float _2x20 = 2 * p2[0] - 2 * p0[0];
	float _2y10 = 2 * p1[1] - 2 * p0[1];
	float _2y20 = 2 * p2[1] - 2 * p0[1];
	float _px01 = p0[0] * p0[0] - p1[0] * p1[0];
	float _px02 = p0[0] * p0[0] - p2[0] * p2[0];
	float _py01 = p0[1] * p0[1] - p1[1] * p1[1];
	float _py02 = p0[1] * p0[1] - p2[1] * p2[1];

	// Compute circle center and radius
	float y_c = (-_px02 - _py02) / (_2x20 * (_2y10 + _px01 + _py01) / _2x10 + _2y20);
	float x_c = (y_c * _2y10 + _px01 + _py01) / _2x10;
	double r = sqrt((p0[0] - x_c) * (p0[0] - x_c) + (p0[1] - y_c) * (p0[1] - y_c));

	// Compute distance from circle center to point
	double d = sqrt((p[0] - x_c) * (p[0] - x_c) + (p[1] - y_c) * (p[1] - y_c));

	// Evaluate if the point is inside the circle
	return d < r;
}
