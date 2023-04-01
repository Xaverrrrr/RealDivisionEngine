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

vector<vector<int>> Camera::renderEntities(vector<Entity*> entities) {

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
							(int)round(MathFuns::map(adjustedAngelXY, -this->FovXY, this->FovXY, 0, 980)), //X-Position on screen
							(int)round((1- (vectorLen / this->renderDistance)) * var->getDimensions()[2])  //Height on screen
						});
				}
			}
		}
		return output;
}

vector<vector<vector<int>>> Camera::renderWalls(vector<Wall*> walls) {

	vector<vector<vector<int>>> output;
	vector<double> myRotation = this->getRotation();
	vector<double> myPosition = this->getPosition();


	for (Wall* var : walls) {
		double deltaX1 = (var->getCoordinates()[0][0] - myPosition[0]);
		double deltaY1 = (var->getCoordinates()[0][1] - myPosition[1]);
		double deltaZ1 = (var->getCoordinates()[0][2] - myPosition[2]);

		double deltaX2 = (var->getCoordinates()[1][0] - myPosition[0]);
		double deltaY2 = (var->getCoordinates()[1][1] - myPosition[1]);
		double deltaZ2 = (var->getCoordinates()[1][2] - myPosition[2]);

		double vectorLen1 = sqrt(pow(deltaX1, 2) + pow(deltaY1, 2));
		double vectorLen2 = sqrt(pow(deltaX2, 2) + pow(deltaY2, 2));

		if (vectorLen1 <= this->renderDistance && vectorLen2 <= this->renderDistance) {

			double angleXY1 = MathFuns::radToDeg(atan2(deltaY1, deltaX1));
			double angleXZ1 = MathFuns::radToDeg(atan2(deltaZ1, deltaX1));

			double angleXY2 = MathFuns::radToDeg(atan2(deltaY2, deltaX2));
			double angleXZ2 = MathFuns::radToDeg(atan2(deltaZ2, deltaX2));

			double adjustedAngelXY1 = angleXY1 - myRotation[0];
			double adjustedAngelXZ1 = angleXZ1 - myRotation[1];

			double adjustedAngelXY2 = angleXY2 - myRotation[0];
			double adjustedAngelXZ2 = angleXZ2 - myRotation[1];

			if (adjustedAngelXY1 <= this->FovXY && adjustedAngelXY1 >= -this->FovXY && adjustedAngelXZ1 <= this->FovXZ && adjustedAngelXZ1 >= -this->FovXZ) {
				if (adjustedAngelXY2 <= this->FovXY && adjustedAngelXY2 >= -this->FovXY && adjustedAngelXZ2 <= this->FovXZ && adjustedAngelXZ2 >= -this->FovXZ)
				{
					output.push_back(
					{
						{
							(int)round(MathFuns::map(adjustedAngelXY1, -this->FovXY, this->FovXY, 0, 980)),
							(int)round((1 - (vectorLen1 / this->renderDistance)) * var->getDimensions()[2])
						},
						{
							(int)round(MathFuns::map(adjustedAngelXY2, -this->FovXY, this->FovXY, 0, 980)),
							(int)round((1 - (vectorLen2 / this->renderDistance)) * var->getDimensions()[2])
						}

					});
				}
			}
		}
	}
	return output;
}