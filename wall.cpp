#include "wall.h"

Wall::Wall(string name)
{
	this->name = name;
}

void Wall::setCoordinates(vector<vector<double>> cords)
{
	this->coordinates = cords;
}

vector<vector<double>> Wall::getCoordinates()
{
	return this->coordinates;
}

void Wall::setDimensions(vector<double> dimensions)
{
	this->dimensions = dimensions;
}

vector<double> Wall::getDimensions()
{
	return this->dimensions;
}