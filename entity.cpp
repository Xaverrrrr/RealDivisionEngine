#include "entity.h"
#include "string"

using namespace std;

Entity::Entity(string name) {
	this->name = name;
}

void Entity::setPosition(vector<double> myPosition) {
	this->position = myPosition;
}

void Entity::updatePosition(double x, double y, double z) {
	position[0] += x;
	position[1] += y;
	position[2] += z;
}

vector<double> Entity::getPosition() {
	return position;
}

string Entity::getName() {
	return this->name;
}