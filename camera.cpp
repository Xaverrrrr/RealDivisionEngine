#include "camera.h"
#include "mathFuns.h"

#include <iostream>
#include <string.h>
#include <math.h>

Camera::Camera(string name) : Entity(name) {
	this->name = name;
}

void Camera::setFovXY(int fov)
{
	this->FovXY = fov;
	this->FovXZ = round(fov / (16/9));
}

void Camera::setRenderDistance(int x) {
	this->renderDistance = x;
}

int Camera::getRenderDistance() {
	return this->renderDistance;
}

int Camera::getFovXY()
{
	return this->FovXY;
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

vector<vector<int>> Camera::renderScreen(vector<Entity*> entities) {

	vector<vector<int>> output;
	vector<double> myRotation = this->getRotation();
	vector<double> myPosition = this->getPosition();


		for (Entity* var : entities) {
			double deltaX = (var->getPosition()[0] - myPosition[0]);
			double deltaY = (var->getPosition()[1] - myPosition[1]);
			double deltaZ = (var->getPosition()[2] - myPosition[2]);

			double vectorLen = sqrt(pow(deltaX, 2) + pow(deltaY, 2));

			if (vectorLen <= this->renderDistance) {
				double angleXY = MathFuns::radToDeg(atan2(deltaY, deltaX));
				double angleXZ = MathFuns::radToDeg(atan2(deltaZ, deltaX));

				double adjustedAngelXY = angleXY - myRotation[0];
				double adjustedAngelXZ = angleXZ - myRotation[1];

				if (adjustedAngelXY <= this->FovXY && adjustedAngelXY >= -this->FovXY && adjustedAngelXZ <= this->FovXZ && adjustedAngelXZ >= -this->FovXZ) {
					output.push_back(
						{ 
							(int)round(MathFuns::map(adjustedAngelXY, -this->FovXY, this->FovXY, 0, 980)), 
							(int)round((1- (vectorLen / this->renderDistance)) * var->getDimensions()[2])
						});
				}
			}
		}
		return output;
}
