#ifndef MATRIX4X4_H
#define MATRIX4X4_H

#include <vector>
#include <iostream>
class Matrix4x4
{
public:

	Matrix4x4 addMatrices(Matrix4x4 a, Matrix4x4 b);
	void setElements(std::vector<double> x);

	double x1, x2, x3, x4;
	double y1, y2, y3, y4;
	double z1, z2, z3, z4;
	double w1, w2, w3, w4;
};

#endif 
