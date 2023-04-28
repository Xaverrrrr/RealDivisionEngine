#include "wall.h"

Wall::Wall(string name)
{
	this->name = name;
}

void Wall::setCoordinates(Point lowerLeft, Point lowerRight, Point upperLeft, Point upperRight)
{
	this->coordinates = { lowerLeft, lowerRight, upperLeft, upperRight };
}

vector<Point> Wall::getCoordinates()
{
	return this->coordinates;
}
