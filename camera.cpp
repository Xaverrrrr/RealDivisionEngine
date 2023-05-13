#include "camera.h"
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

vector<Vector3> Camera::createRotationMatrix(Vector3 rotationAngles) {
	double x = rotationAngles.x;
	double y = rotationAngles.y;
	double z = rotationAngles.z;

	// Convert rotation angles to radians
	double radX = MathFuns::degToRad(x);
	double radY = MathFuns::degToRad(y);
	double radZ = MathFuns::degToRad(z);

	// Calculate sine and cosine values
	double sinGam = sin(radX);
	double cosGam = cos(radX);
	double sinBet = sin(radY);
	double cosBet = cos(radY);
	double sinAlp = sin(radZ);
	double cosAlp = cos(radZ);

	// Create the rotation matrix
	vector<Vector3> rotationMatrix;
	rotationMatrix.push_back(Vector3(cosAlp * cosBet, cosAlp * sinBet * sinGam - sinAlp * cosGam, cosAlp * sinBet * cosGam + sinAlp * sinGam));
	rotationMatrix.push_back(Vector3(sinAlp * cosBet, sinAlp * sinBet * sinGam + cosAlp * cosGam, sinAlp * sinBet * cosGam - cosAlp * sinGam));
	rotationMatrix.push_back(Vector3(-sinBet, cosBet * sinGam, cosBet * cosGam));

	return rotationMatrix;
}

Vector3 Camera::multiplyMatrixVector(const vector<Vector3>& matrix, const Vector3& vector) {
	double x = vector.x;
	double y = vector.y;
	double z = vector.z;

	double resultX = matrix[0].x * x + matrix[0].y * y + matrix[0].z * z;
	double resultY = matrix[1].x * x + matrix[1].y * y + matrix[1].z * z;
	double resultZ = matrix[2].x * x + matrix[2].y * y + matrix[2].z * z;

	return Vector3(resultX, resultY, resultZ);
}

Vector2 Camera::renderPoint(Point point) {
    Vector2 output;

    Vector3 cameraPosition	= this->getPosition();
    Vector3 cameraRotation	= this->getRotation();
    Vector3 pointPosition	= point.getCoordinates();

	double	width			= 960.0;
	double	height			= 540.0;
    double	nearClipping	= 10;
    double	farClipping		= this->getRenderDistance();
    double	aspectRatio		= width / height;

	double  fovx			= this->getFov();
    double	fovy			= 2.0 * atan(tan(fovx * 0.5) / aspectRatio);

	double  widthViewPlane	= tan(fovx) * nearClipping * 2;
	double  heightViewPlane	= widthViewPlane * (9 / 16);

	vector<Vector3> rotationMatrix = createRotationMatrix(cameraRotation);
	Vector3 rotatedPointPosition = multiplyMatrixVector(rotationMatrix, pointPosition);

	Vector3 pointCamDelta;
	pointCamDelta.x = rotatedPointPosition.x - cameraPosition.x;
	pointCamDelta.y = rotatedPointPosition.y - cameraPosition.y;
	pointCamDelta.z = rotatedPointPosition.z - cameraPosition.z;

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