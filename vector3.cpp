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
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Vector3 Vector3::normalise()
{
	double myXsquared = this->x * this->x;
	double myYsquared = this->y * this->y;
	double myZsquared = this->z * this->z;

	double betrag = sqrt(pow(sqrt(myXsquared + myYsquared), 2) + myZsquared);

	Vector3 out = Vector3(0, 0, 0);
		out.x = this->x / betrag;
		out.y = this->y / betrag;
		out.z = this->z / betrag;

	return out;
}

double Vector3::length()
{
	double myXsquared = this->x * this->x;
	double myYsquared = this->y * this->y;
	double myZsquared = this->z * this->z;

	return abs(sqrt(pow(sqrt(myXsquared + myYsquared), 2) + myZsquared));
}

void Vector3::add(Vector3 vec)
{
	this->x += vec.x;
	this->y += vec.y;
	this->z += vec.z;
}

void Vector3::subtract(Vector3 vec)
{
	this->x -= vec.x;
	this->y -= vec.y;
	this->z -= vec.z;
}
