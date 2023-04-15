#include "vector3.h"
#include <iostream>

Vector3::Vector3(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::Vector3()
{
}

Vector3* Vector3::normalise()
{
	double myXsquared = this->x * this->x;
	double myYsquared = this->y * this->y;
	double myZsquared = this->z * this->z;

	double betrag = sqrt(pow(sqrt(myXsquared + myYsquared), 2) + myZsquared);

	Vector3* out = new Vector3(0, 0, 0);
		out->x = this->x / betrag;
		out->y = this->y / betrag;
		out->z = this->z / betrag;

	return out;
}

double Vector3::length()
{
	double myXsquared = this->x * this->x;
	double myYsquared = this->y * this->y;
	double myZsquared = this->z * this->z;

	return sqrt(pow(sqrt(myXsquared + myYsquared), 2) + myZsquared);
}

Vector3* Vector3::add(Vector3* vec)
{
	Vector3* out = new Vector3(0, 0, 0);

	out->x += vec->x;
	out->y += vec->y;
	out->z += vec->z;

	return out;
}

Vector3* Vector3::subtract(Vector3* vec)
{
	Vector3* out = new Vector3(0, 0, 0);

	out->x -= vec->x;
	out->y -= vec->y;
	out->z -= vec->z;

	return out;
}
