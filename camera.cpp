#include "camera.h"



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

void Camera::setRotation(Vector3 rotation) {
	this->rotation = rotation;
}

void Camera::updateRotation(double x, double y, double z) {
	this->rotation.x += x;
	this->rotation.y += y;
	this->rotation.z += z;
}

Vector3 Camera::getRotation() {
	return this->rotation;
}

vector<Vector2> Camera::renderPoints(vector<Point> points) {
	vector<Vector2> output;
	Vector2 myRotation;
		myRotation.x = MathFuns::radToDeg(atan2(this->getRotation().y, this->getRotation().x));
		myRotation.y = MathFuns::radToDeg(atan2(this->getRotation().z, this->getRotation().x));
	Vector3 myPosition = this->getPosition();

	for (Point var : points)
	{
		Vector3 deltaPosition;
			deltaPosition.x = var.getCoordinates().x - myPosition.x;
			deltaPosition.y = var.getCoordinates().y - myPosition.y;
			deltaPosition.z = var.getCoordinates().z - myPosition.z;

		if (deltaPosition.length() <= this->getRenderDistance())
		{
			double angleXY = MathFuns::radToDeg(atan2(deltaPosition.y, deltaPosition.x)) - myRotation.x;
			double angleXZ = MathFuns::radToDeg(atan2(deltaPosition.z, deltaPosition.x)) - myRotation.y;

			output.push_back(
				Vector2(
					(int)round(MathFuns::map(angleXY, -this->FovXY, this->FovXY, 0 - 100, 960 + 100)),		//X-Position on Screen
					(int)round(MathFuns::map(angleXZ, -this->FovXZ, this->FovXZ, 0 - 100, 540 + 100))		//Y-Position on Screen
				)
			);	
		}
		else {
			output.push_back(Vector2(-1, -1)); //if not renderable, we push a dummy
		}
	}
	return output;
}

vector<vector<Vector2>> Camera::renderWalls(vector<Wall> walls) {

	vector<vector<Vector2>> output = { { Vector2(-1,-1), Vector2(-1,-1), Vector2(-1,-1), Vector2(-1,-1) } };

	for (Wall var : walls)
	{
		vector<Vector2> coordinatesOnScreen = Camera::renderPoints(var.getCoordinates());
		if (coordinatesOnScreen[0].x >= 0 &&
			coordinatesOnScreen[0].y >= 0 &&
			coordinatesOnScreen[1].x >= 0 &&
			coordinatesOnScreen[1].y >= 0 &&
			coordinatesOnScreen[2].x >= 0 &&
			coordinatesOnScreen[2].y >= 0 &&
			coordinatesOnScreen[3].x >= 0 &&
			coordinatesOnScreen[3].y >= 0
			) {

			output.push_back(coordinatesOnScreen);
		}
	}

	return output;
}