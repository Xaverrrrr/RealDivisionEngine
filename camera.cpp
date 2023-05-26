#include "camera.h"
#include "matrix4x4.h"
#include <cmath>

double M_PI = 3.1415;

Camera::Camera(string name) : Entity(name) {
	this->name = name;
}

void Camera::setFov(int fov)
{
	this->Fov = fov;
}

void Camera::setRenderDistance(int x) {
	this->renderDistance = x;
}

int Camera::getRenderDistance() {
	return this->renderDistance;
}

int Camera::getFov()
{
	return this->Fov;
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



Vector2 Camera::renderPoint(Point point) {

	Vector2 output;

	Vector3 cameraPosition = this->getPosition();
	Vector3 cameraRotation = this->getRotation();
	Vector3 pointPosition = point.getCoordinates();

	double	width = 960.0;
	double	height = 540.0;
	double	nearClipping = 10;
	double	farClipping = this->getRenderDistance();
	double	aspectRatio = width / height;

	double  fovx = this->getFov();
	double	fovy = 2.0 * atan(tan(fovx * 0.5) / aspectRatio);

	double  widthViewPlane = tan(fovx) * nearClipping * 2;
	double  heightViewPlane = tan(fovy) * nearClipping * 2;

	Vector3 pointCamDelta;
	pointCamDelta.x = pointPosition.x - cameraPosition.x;
	pointCamDelta.y = pointPosition.y - cameraPosition.y;
	pointCamDelta.z = pointPosition.z - cameraPosition.z;

	double  angleXY = MathFuns::radToDeg(atan2(pointCamDelta.y, pointCamDelta.x));

	if (pointCamDelta.length() < farClipping && angleXY > -fovx && angleXY < fovx)
	{
		output.x = nearClipping / (pointCamDelta.x / pointCamDelta.y) * widthViewPlane;
		output.y = nearClipping / (pointCamDelta.x / pointCamDelta.z) * heightViewPlane;

		return output;
	}
}

vector<vector<Vector2>> Camera::renderWalls(vector<Wall> walls) {

	vector<vector<Vector2>> output;

	//for (Wall var : walls)
	//{
	//	Vector2 coordinatesOnScreen;
	//	for (Point point : var.getCoordinates()) {
	//		coordinatesOnScreen = this->renderPoints(point);
	//		output.push_back({ coordinatesOnScreen });
	//	}
	//		
	//}

	return output;
}