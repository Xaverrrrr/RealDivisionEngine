#include "matrix4x4.h"
#include <iostream>

Matrix4x4 Matrix4x4::addMatrices(Matrix4x4 a, Matrix4x4 b)
{
	Matrix4x4 output;

	output.x1 = a.x1 + b.x1;
	output.x2 = a.x2 + b.x2;
	output.x3 = a.x3 + b.x3;
	output.x4 = a.x4 + b.x4;

	output.y1 = a.y1 + b.y1;
	output.y2 = a.y2 + b.y2;
	output.y3 = a.y3 + b.y3;
	output.y4 = a.y4 + b.y4;

	output.z1 = a.z1 + b.z1;
	output.z2 = a.z2 + b.z2;
	output.z3 = a.z3 + b.z3;
	output.z4 = a.z4 + b.z4;

	output.w1 = a.w1 + b.w1;
	output.w2 = a.w2 + b.w2;
	output.w3 = a.w3 + b.w3;
	output.w4 = a.w4 + b.w4;

	return output;
}

void Matrix4x4::setElements(std::vector<double> x)
{
	this->x1 = x[0];
	this->x2 = x[4];
	this->x3 = x[8];
	this->x4 = x[12];

	this->y1 = x[1];
	this->y2 = x[5];
	this->y3 = x[9];
	this->y4 = x[13];

	this->z1 = x[2];
	this->z2 = x[6];
	this->z3 = x[10];
	this->z4 = x[14];

	this->w1 = x[3];
	this->w2 = x[7];
	this->w3 = x[11];
	this->w4 = x[15];
}

