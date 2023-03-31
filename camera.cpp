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
	vector<double> myRotation = this->rotation;
	vector<double> myPosition = this->position;


		for (Entity* var : entities) {
			double deltaX = (var->getPosition()[0] - myPosition[0]);
			double deltaY = (var->getPosition()[1] - myPosition[1]);
			double deltaZ = (var->getPosition()[2] - myPosition[2]);

			double vectorLen = sqrt(pow(sqrt(pow(deltaX, 2) + pow(deltaY, 2)), 2) + pow(deltaZ, 2));

			if (vectorLen <= this->renderDistance) {
				double angleXY = MathFuns::roundToDigit(MathFuns::radToDeg(atan2(deltaY, deltaX)), 2);
				double angleXZ = MathFuns::roundToDigit(MathFuns::radToDeg(atan2(deltaZ, deltaX)), 2);

				double adjustedAngelXY = angleXY - myRotation[0];
				double adjustedAngelXZ = angleXZ - myRotation[1];

				if (adjustedAngelXY <= this->FovXY && adjustedAngelXY >= -this->FovXY && adjustedAngelXZ <= this->FovXZ && adjustedAngelXZ >= -this->FovXZ) {
					output.push_back(
						{ 
							(int)round(MathFuns::map(adjustedAngelXY, -this->FovXY, this->FovXY, 0, 980)), 
							(int)round((vectorLen / this->renderDistance) * 300) 
						});
				}
			}
		}
		return output;
}

