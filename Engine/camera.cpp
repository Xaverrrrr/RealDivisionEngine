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
    Vector3 pointPosition = point.getCoordinates();


    double width = 960.0;
    double height = 540.0;
    double near = 0.1;
    double far = this->getRenderDistance();
    double aspectRatio = width / height;
    double fov = this->getFov();
    double f = 1 / tan(MathFuns::degToRad(fov / 2));
    double angleXY = MathFuns::radToDeg(atan2(pointPosition.y - cameraPosition.y, pointPosition.x - cameraPosition.x));

    // Apply camera rotation
    Vector3 cameraRotation = this->getRotation(); // Assuming getRotation() returns Euler rotations in degrees
    double angleXRad = MathFuns::degToRad(cameraRotation.x);
    double angleYRad = MathFuns::degToRad(cameraRotation.y);
    double angleZRad = MathFuns::degToRad(cameraRotation.z);
    double cosX = cos(angleXRad);
    double sinX = sin(angleXRad);
    double cosY = cos(angleYRad);
    double sinY = sin(angleYRad);
    double cosZ = cos(angleZRad);
    double sinZ = sin(angleZRad);

    // Apply inverse camera rotation to object's position
    Vector3 rotatedObjectPosition;
    rotatedObjectPosition.x = (pointPosition.x - cameraPosition.x) * (cosY * cosZ) + (pointPosition.y - cameraPosition.y) * (cosX * sinZ + sinX * sinY * cosZ) + (pointPosition.z - cameraPosition.z) * (sinX * sinZ - cosX * sinY * cosZ);
    rotatedObjectPosition.y = (pointPosition.x - cameraPosition.x) * (-cosY * sinZ) + (pointPosition.y - cameraPosition.y) * (cosX * cosZ - sinX * sinY * sinZ) + (pointPosition.z - cameraPosition.z) * (sinX * cosZ + cosX * sinY * sinZ);
    rotatedObjectPosition.z = (pointPosition.x - cameraPosition.x) * (sinY)+(pointPosition.y - cameraPosition.y) * (-sinX * cosY) + (pointPosition.z - cameraPosition.z) * (cosX * cosY);

    Vector3 positionDelta;
    positionDelta.x = -rotatedObjectPosition.y; // Left-handed system
    positionDelta.y = rotatedObjectPosition.z - cameraPosition.z;
    positionDelta.z = rotatedObjectPosition.x - cameraPosition.x;

    if (positionDelta.length() < far && positionDelta.length() > near && angleXY > -fov && angleXY < fov) {
        Matrix4x4 perspectiveProjectionMatrix;

        perspectiveProjectionMatrix.M[0][0] = f / aspectRatio;
        perspectiveProjectionMatrix.M[1][1] = f;
        perspectiveProjectionMatrix.M[2][2] = (far + near) / (near - far);
        perspectiveProjectionMatrix.M[3][2] = (2 * far * near) / (near - far);
        perspectiveProjectionMatrix.M[2][3] = -1;

        Vector3 projectedPoint = Matrix4x4::multPointMatrix(positionDelta, perspectiveProjectionMatrix);

        // Map projected point to the screen
        output.x = (projectedPoint.x + 1) * (width / 2);
        output.y = (1 - projectedPoint.y) * (height / 2);

        // Convert to pixel coordinates
        output.x = round(output.x);
        output.y = round(output.y);

        return output;
    }
}


vector<vector<Vector2>> Camera::renderWalls(vector<Wall> walls) {

	vector<vector<Vector2>> output;

	for (Wall var : walls)
	{
        vector<Vector2> temp;
        double wallValid = true;
		for (Point point : var.getCoordinates()) {
            Vector2 coordinatesOnScreen = this->renderPoint(point);
			temp.push_back({ coordinatesOnScreen });
		}
        for (Vector2 v : temp) {
            if (v.x != 0 && v.y != 0) wallValid == true;
            else wallValid == false;
        }
        if (wallValid) {
            output.push_back(temp);
        }
	}

	return output;
}

vector<vector<Vector2>> Camera::renderEntities(vector<Entity> entities)
{
    vector<vector<Vector2>> output;

    for (Entity var : entities)
    {
        vector<Vector2> temp;
        bool entityValid = true;
        for (Vector3 point : var.getVerteces()) {
            Point p;
            p.setCoordinates(point);

            Vector2 coordinatesOnScreen = this->renderPoint(p);
            temp.push_back({ coordinatesOnScreen });
        }
        for (Vector2 v : temp) {
            if (v.x != 0 && v.y != 0) entityValid == true;
            else entityValid == false;
        }
        if (entityValid) {
            output.push_back(temp);
        }
    }

    return output;
}
