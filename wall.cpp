#include "wall.h"

Wall::Wall(string name)
{
	this->name = name;
}

void Wall::setCoordinates(Vector3 start, Vector3 end)
{
	this->coordinates = { start, end };
}

vector<Vector3> Wall::getCoordinates()
{
	return this->coordinates;
}

void Wall::setDimensions(Vector3 dimensions)
{
	this->dimensions = dimensions;
}

Vector3 Wall::getDimensions()
{
	return this->dimensions;
}