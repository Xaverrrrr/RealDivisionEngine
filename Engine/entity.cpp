#include "entity.h"
#include "string"

Entity::Entity(string name) {
	this->name = name;
}

Entity::Entity(string name, Vector3 position)
{
	this->name = name;
	this->setPosition(position);
}

void Entity::setPosition(Vector3 myPosition) {
	this->position = myPosition;
}

void Entity::updatePosition() {
	this->position.x += this->velocity.x;
	this->position.y += this->velocity.y;
	this->position.z += this->velocity.z;
}

void Entity::setVelocity(Vector3 vel) {
	this->velocity.x = vel.x;
	this->velocity.y = vel.y;
	this->velocity.z = vel.z;
}

Vector3 Entity::getVelocity()
{
	return this->velocity;
}


Vector3 Entity::getPosition() 
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

void Entity::setDimensions(Vector3 dimensions)
{
	this->dimensions = dimensions;
}

Vector3 Entity::getDimensions()
{
	return this->dimensions;
}
