#ifndef POINT_H
	#define POINT_H

#include "vector3.h"

class Point {

public:
	Point();
	Point(double x, double y, double z);
	Vector3 getCoordinates();
	void	setCoordinates(Vector3 vector);
private:
	Vector3 coordinates = Vector3(0, 0, 0);
};

#endif