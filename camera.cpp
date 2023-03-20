#include "camera.h"
#include <iostream>
#include <string.h>
#include <math.h>

Camera::Camera(string name) : Entity(name) {
	this->name = name;
}

void Camera::setFOV(int fov)
{
	this->FOVX = fov;
	this->FOVY = round(fov / (16/9));
}

void Camera::setRenderDistance(int x) {
	this->renderDistance = x;
}

int Camera::getRenderDistance() {
	return this->renderDistance;
}

int Camera::getFOV()
{
	return this->FOVX;
}

void Camera::setRotation(vector<double> rotation) {
	this->rotation = rotation;
}

void Camera::updateRotation(double xy, double xz) {
	this->rotation[0] += xy;
	this->rotation[1] += xz;
}

vector<double> Camera::getRotation() {
	return this->rotation;
}

void Camera::renderScreen(vector<Entity*> entities) {
	vector<double> myRotation = this->getRotation();
	vector<double> myPosition = this->getPosition();
	int myFOV = this->getFOV();


		for (Entity* var : entities) {
			double deltaX = (var->getPosition()[0] - myPosition[0]);
			double deltaY = (var->getPosition()[1] - myPosition[1]);
			double deltaZ = (var->getPosition()[2] - myPosition[2]);

			double vectorLen = sqrt(pow(sqrt(pow(deltaX, 2) + pow(deltaY, 2)), 2) + pow(deltaZ, 2));

			if (vectorLen <= this->renderDistance) {
				double angleXY = round(radToDeg(atan2(deltaY, deltaX)) * 100) / 100; // *100 / 100 to round to 2 decimal points
				double angleXZ = round(radToDeg(atan2(deltaZ, deltaX)) * 100) / 100;

				double adjustedAngelXY = angleXY - this->rotation[0];
				double adjustedAngelXZ = angleXZ - this->rotation[1];

				if (adjustedAngelXY <= this->FOVX && adjustedAngelXZ <= this->FOVY) {
					std::cout << "Entity renderable: " << var->getName() << endl;
				}
			}



		}
}

double Camera::radToDeg(double x) {
	return (x * (180 / 3.1415926));
}