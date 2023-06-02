#ifndef MATRIX4X4_H
#define MATRIX4X4_H

#include <vector>
#include <iostream>
#include "vector3.h"
class Matrix4x4
{
public:

	static Matrix4x4 addMatrices(Matrix4x4 a, Matrix4x4 b);
	static Vector3 multPointMatrix(const Vector3 in, const Matrix4x4 M);
	static Matrix4x4 multiplyMatrices(const Matrix4x4& matrixA, const Matrix4x4& matrixB);
	Matrix4x4();

	double M[4][4];
};

#endif 
