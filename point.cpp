#include "point.h"

Point::Point()
{
}

Point::Point(double x, double y, double z)
{
	this->coordinates = Vector3(x, y, z);
}

Vector3 Point::getCoordinates()
{
	return this->coordinates;
}

void Point::setCoordinates(Vector3 vector)
{
	this->coordinates = vector;
}
