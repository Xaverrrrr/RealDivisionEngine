#include "matrix4x4.h"
#include <iostream>

Matrix4x4 Matrix4x4::addMatrices(Matrix4x4 a, Matrix4x4 b)
{
	Matrix4x4 output;

	output.M[0][0] = a.M[0][0] + b.M[0][0];
	output.M[0][1] = a.M[0][1] + b.M[0][1];
	output.M[0][2] = a.M[0][2] + b.M[0][2];
	output.M[0][3] = a.M[0][3] + b.M[0][3];

	output.M[1][0] = a.M[1][0] + b.M[1][0];
	output.M[1][1] = a.M[1][1] + b.M[1][1];
	output.M[1][2] = a.M[1][2] + b.M[1][2];
	output.M[1][3] = a.M[1][3] + b.M[1][3];

	output.M[2][0] = a.M[2][0] + b.M[2][0];
	output.M[2][1] = a.M[2][1] + b.M[2][1];
	output.M[2][2] = a.M[2][2] + b.M[2][2];
	output.M[2][3] = a.M[2][3] + b.M[2][3];

	output.M[3][0] = a.M[3][0] + b.M[3][0];
	output.M[3][1] = a.M[3][1] + b.M[3][1];
	output.M[3][2] = a.M[3][2] + b.M[3][2];
	output.M[3][3] = a.M[3][3] + b.M[3][3];

	return output;
}



Matrix4x4::Matrix4x4()
{
	M[0][0] = 0;
	M[0][1] = 0;
	M[0][2] = 0;
	M[0][3] = 0;

	M[1][0] = 0;
	M[1][1] = 0;
	M[1][2] = 0;
	M[1][3] = 0;

	M[2][0] = 0;
	M[2][1] = 0;
	M[2][2] = 0;
	M[2][3] = 0;

	M[3][0] = 0;
	M[3][1] = 0;
	M[3][2] = 0;
	M[3][3] = 0;
}

Vector3 Matrix4x4::multPointMatrix(const Vector3 in, const Matrix4x4 M)
{
	Vector3 out;

	out.x = in.x * M.M[0][0] + in.y * M.M[1][0] + in.z * M.M[2][0] + /* in.z = 1 */ M.M[3][0];
	out.y = in.x * M.M[0][1] + in.y * M.M[1][1] + in.z * M.M[2][1] + /* in.z = 1 */ M.M[3][1];
	out.z = in.x * M.M[0][2] + in.y * M.M[1][2] + in.z * M.M[2][2] + /* in.z = 1 */ M.M[3][2];
	float w = in.x * M.M[0][3] + in.y * M.M[1][3] + in.z * M.M[2][3] + /* in.z = 1 */ M.M[3][3];

	if (w != 1) {
		out.x /= w;
		out.y /= w;
		out.z /= w;
	}

	return out;
}