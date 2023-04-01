#include "wall.h"

Wall::Wall(string name) : Entity(name)
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

