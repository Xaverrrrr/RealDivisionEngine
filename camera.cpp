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
	double sinX = sin(radX);
	double cosX = cos(radX);
	double sinY = sin(radY);
	double cosY = cos(radY);
	double sinZ = sin(radZ);
	double cosZ = cos(radZ);

	// Create the rotation matrix
	vector<Vector3> rotationMatrix;
	rotationMatrix = {
		Vector3(cosY * cosZ, -cosY * sinZ, sinY),
		Vector3(sinX * sinY * cosZ + cosX * sinZ, -sinX * sinY * sinZ + cosX * cosZ, -sinX * cosY),
		Vector3(-cosX * sinY * cosZ + sinX * sinZ, cosX * sinY * sinZ + sinX * cosZ, cosX * cosY)
	};

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

	float angle = MathFuns::radToDeg(atan2(pointPosition.y - cameraPosition.y, pointPosition.x - cameraPosition.x));
	float fov = this->getFov();
	float width = 960;
	float height = 540;
	float aspectRatio = width / height;
	float far = this->getRenderDistance();
	float near = 1;


	// Transform the 3D point from world space to camera space
	Vector3 cameraSpacePoint = {
		pointPosition.z - cameraPosition.z,
		pointPosition.y - cameraPosition.y,
		pointPosition.x - cameraPosition.x
	};

	if (angle < fov && angle > -fov && cameraSpacePoint.length() < far) {

		// Create perspective projection matrix
		float f = 1.0f / std::tan(fov / 2.0f);

		float projMatrix[4][4] = {
			{f / aspectRatio, 0, 0, 0},
			{0, f, 0, 0},
			{0, 0, (far + near) / (far - near), 2 * far * near / (far - near)},
			{0, 0, 1, 0}
		};

		// Multiply the camera space point by the perspective projection matrix
		float clipSpacePoint[4] = {
			projMatrix[0][0] * cameraSpacePoint.x + projMatrix[0][1] * cameraSpacePoint.y + projMatrix[0][2] * cameraSpacePoint.z + projMatrix[0][3],
			projMatrix[1][0] * cameraSpacePoint.x + projMatrix[1][1] * cameraSpacePoint.y + projMatrix[1][2] * cameraSpacePoint.z + projMatrix[1][3],
			projMatrix[2][0] * cameraSpacePoint.x + projMatrix[2][1] * cameraSpacePoint.y + projMatrix[2][2] * cameraSpacePoint.z + projMatrix[2][3],
			projMatrix[3][0] * cameraSpacePoint.x + projMatrix[3][1] * cameraSpacePoint.y + projMatrix[3][2] * cameraSpacePoint.z + projMatrix[3][3]
		};

		// Perform perspective division to obtain the normalized device coordinates (NDC)
		Vector3 ndc = {
			clipSpacePoint[0] / clipSpacePoint[3],
			clipSpacePoint[1] / clipSpacePoint[3],
			clipSpacePoint[2] / clipSpacePoint[3]
		};

		// Convert the NDC to screen coordinates
		Vector2 screenPoint = {
			((ndc.y + 1.0f) / 2.0f) * width + MathFuns::mapLinear(cameraRotation.x, 0, 360, 0, width),
			((ndc.x + 1.0f) / 2.0f) * height + MathFuns::mapLinear(cameraRotation.y, 0, 360, 0, height)
		};

		return screenPoint;
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