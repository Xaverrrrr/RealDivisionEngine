#include "vector2.h"
#include "iostream"

Vector2::Vector2(double x, double y)
{
	this->x = x;
	this->y= y;
}

Vector2::Vector2()
{
}

Vector2 Vector2::normalise()
{
	double myXsquared = this->x * this->x;
	double myYsquared = this->y * this->y;

	double betrag = sqrt(myXsquared + myYsquared);

	Vector2 out = Vector2(0, 0);
	out.x = this->x / betrag;
	out.y = this->y / betrag;

	return out;
}

double Vector2::length()
{
	double myXsquared = this->x * this->x;
	double myYsquared = this->y * this->y;

	return sqrt(myXsquared + myYsquared);
}

void Vector2::add(Vector2 vector)
{
	this->x += vector.x;
	this->y += vector.y;
}

void Vector2::subtract(Vector2 vector)
{
	this->x -= vector.x;
	this->y -= vector.y;
}
