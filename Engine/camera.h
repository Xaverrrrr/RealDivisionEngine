#ifndef CAMERA_H
	#define CAMERA_H

#include <vector>
#include <iostream>

#include "entity.h"
#include "point.h"
#include "wall.h"
#include "mathFuns.h"
#include "vector3.h"
#include "vector2.h"
#include "vector4.h"


class Camera: public Entity {
public:
	Camera(string name);

	void setFov(int fov);
	int getFov();

	void setRotation(Vector3 rotation);
	Vector3 getRotation();
	void updateRotation(double x, double y, double z);

	Vector2 renderPoint(Point point);
	vector<vector<Vector2>> renderWalls(vector<Wall> walls); 
	vector<vector<Vector2>> renderEntities(vector<Entity> entities);
	void setRenderDistance(int x);
	int getRenderDistance();

private:

	string name;

	int Fov; //in degrees from center => double to get actual visual field

	int renderDistance;

	Vector3 rotation = { 0, 0, 0 }; 
	//Orientation of camera, for more info: https://en.wikipedia.org/wiki/Euler_angles#Tait%E2%80%93Bryan_angles
};

#endif //CAMERA_H