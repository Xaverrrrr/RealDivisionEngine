#include "entity.h"
#include "string"

Entity::Entity(string name) {
	this->name = name;
}

Entity::Entity(string name, Vector3 position, vector<Vector3> verteces)
{
	this->name = name;
	this->setPosition(position);
	this->verteces = verteces;
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

void Entity::setVerteces(vector<Vector3> v)
{
	this->verteces = v;
}

vector<Vector3> Entity::getVerteces()
{
	return this->verteces;
}

