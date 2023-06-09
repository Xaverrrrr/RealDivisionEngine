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

Vector3 Vector3::normalize(const Vector3& a)
{
	double myXsquared = a.x * a.x;
	double myYsquared = a.y * a.y;
	double myZsquared = a.z * a.z;

	double betrag = sqrt(pow(sqrt(myXsquared + myYsquared), 2) + myZsquared);

	Vector3 out = Vector3(0, 0, 0);
		out.x = a.x / betrag;
		out.y = a.y / betrag;
		out.z = a.z / betrag;

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

Vector3 Vector3::cross(const Vector3& a, const Vector3& b)
{
	Vector3 result;
	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return result;

}

double Vector3::dot(const Vector3& a, const Vector3& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}
