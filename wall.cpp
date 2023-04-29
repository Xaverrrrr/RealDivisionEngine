#include "wall.h"

Wall::Wall(string name)
{
	this->name = name;
}

Wall::Wall(string name, vector<Point> vertices)
{
	this->name = name;
	this->coordinates = { vertices[0], vertices[1], vertices[2], vertices[3] };
}

void Wall::setCoordinates(Point lowerLeft, Point lowerRight, Point upperLeft, Point upperRight)
{
	this->coordinates = { lowerLeft, lowerRight, upperLeft, upperRight };
}

vector<Point> Wall::getCoordinates()
{
	return this->coordinates;
}
