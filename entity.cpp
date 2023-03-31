#include "entity.h"
#include "string"

Entity::Entity(string name) {
	this->name = name;
}

void Entity::setPosition(vector<double> myPosition) {
	this->position = myPosition;
}

void Entity::updatePosition() {
	this->position[0] += this->velocity[0];
	this->position[1] += this->velocity[1];
	this->position[2] += this->velocity[2];
}

void Entity::setVelocity(vector<double> vel) {
	this->velocity = vel;
}

vector<double> Entity::getVelocity()
{
	return this->velocity;
}

vector<double> Entity::getPosition() 
{
	return position;
}

void Entity::setName(string name)
{
	this->name = name;
}

string Entity::getName() 
{
	return this->name;
}

void Entity::setDimensions(vector<double> dimensions)
{
	this->dimensions = dimensions;
}

vector<double> Entity::getDimensions()
{
	return this->dimensions;
}
