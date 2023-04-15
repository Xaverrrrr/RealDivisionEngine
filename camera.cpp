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

				double adjustedAngleXY = angleXY - myRotation[0];
				double adjustedAngleXZ = angleXZ - myRotation[1];

				if (adjustedAngleXY <= this->FovXY && adjustedAngleXY >= -this->FovXY && adjustedAngleXZ <= this->FovXZ && adjustedAngleXZ >= -this->FovXZ) {
					output.push_back(
						{ 
							(int)round(MathFuns::map(adjustedAngleXY, -this->FovXY, this->FovXY, 0, 960)), //X-Position on screen
							(int)round(MathFuns::map(adjustedAngleXZ, -this->FovXZ, this->FovXZ, 0, 540))  //Y-Position on screen
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



		double deltaX2 = (var->getCoordinates()[1][0] - myPosition[0]);
		double deltaY2 = (var->getCoordinates()[1][1] - myPosition[1]);


		double vectorLen1 = sqrt(pow(deltaX1, 2) + pow(deltaY1, 2));
		double vectorLen2 = sqrt(pow(deltaX2, 2) + pow(deltaY2, 2));

		double deltaZ1 = (var->getCoordinates()[0][2] + ((1 - (vectorLen1 / this->renderDistance / 2)) * (var->getDimensions()[2])) - myPosition[2]);
		double deltaZ2 = (var->getCoordinates()[1][2] + ((1 - (vectorLen2 / this->renderDistance / 2)) * (var->getDimensions()[2])) - myPosition[2]);

		double deltaZ1u = (var->getCoordinates()[0][2] - ((1 - (vectorLen1 / this->renderDistance / 2)) * (var->getDimensions()[2])) - myPosition[2]);
		double deltaZ2u = (var->getCoordinates()[1][2] - ((1 - (vectorLen2 / this->renderDistance / 2)) * (var->getDimensions()[2])) - myPosition[2]);

		if (vectorLen1 <= this->renderDistance || vectorLen2 <= this->renderDistance) {

			double angleXY1 = MathFuns::radToDeg(atan2(deltaY1, deltaX1));
			double angleXZ1 = MathFuns::radToDeg(atan2(deltaZ1, deltaX1));
			double angleXZ1u = MathFuns::radToDeg(atan2(deltaZ1u, deltaX1));
			double angleXY2 = MathFuns::radToDeg(atan2(deltaY2, deltaX2));
			double angleXZ2 = MathFuns::radToDeg(atan2(deltaZ2, deltaX2));
			double angleXZ2u = MathFuns::radToDeg(atan2(deltaZ2u, deltaX2));

			double adjustedAngleXY1 = (angleXY1 - myRotation[0]);
			double adjustedAngleXZ1 = angleXZ1 - myRotation[1];
			double adjustedAngleXZ1u = angleXZ1u - myRotation[1];
			double adjustedAngleXY2 = (angleXY2 - myRotation[0]);
			double adjustedAngleXZ2 = angleXZ2 - myRotation[1];
			double adjustedAngleXZ2u = angleXZ2u - myRotation[1];

			double adjustedDeltaY1 = deltaY1 - myRotation[0];
			double adjustedDeltaY2 = deltaY2 - myRotation[0];


			output.push_back(
			{
				{

					(int)round(MathFuns::map(adjustedAngleXY1, -this->FovXY, this->FovXY, 0, 960)),				//X-Position on Screen
					(int)round(MathFuns::mapLinear(adjustedAngleXZ1, -this->FovXZ, this->FovXZ, 0, 540)),		//Upper Y Position
					(int)round(MathFuns::mapLinear(adjustedAngleXZ1u, -this->FovXZ, this->FovXZ, 0, 540))		//Lower Y Position
				},
				{

					(int)round(MathFuns::map(adjustedAngleXY2, -this->FovXY, this->FovXY, 0, 960)),
					(int)round(MathFuns::mapLinear(adjustedAngleXZ2, -this->FovXZ, this->FovXZ, 0, 540)),
					(int)round(MathFuns::mapLinear(adjustedAngleXZ2u, -this->FovXZ, this->FovXZ, 0, 540))
				}

			});
		}
	}
	return output;
}