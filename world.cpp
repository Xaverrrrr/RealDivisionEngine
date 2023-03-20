#include "world.h"

World::World(string name)
{
	this->name = name;
}

void World::addEntity(Entity* entity)
{
	this->entityList.push_back(entity);
}

vector<Entity*> World::getEntities() {
	return this->entityList;
}

void World::deleteEtity(Entity* entity)
{
	//todo
}

void World::setMeasurements(vector<double> measurements)
{
	this->measurements = measurements;
}

vector<double> World::getMeasurements()
{
	return this->measurements;
}
