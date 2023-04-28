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


class Camera: public Entity {
public:
	Camera(string name);

	void setFovXY(int fov);
	int getFovXY();

	void setRotation(Vector3 rotation);
	Vector3 getRotation();
	void updateRotation(double x, double y, double z);

	vector<Vector2> renderPoints(vector<Point> points);
	vector<vector<Vector2>> renderWalls(vector<Wall> walls); //Returns a list of pairs (left and right side of wall) which themselfes contain a pair of both the x coordinate on the screen and the height of the line 

	void setRenderDistance(int x);
	int getRenderDistance();

private:

	string name;

	int FovXY; //in degrees from center => double to get actual visual field
	int FovXZ;

	int renderDistance;

	Vector3 rotation = { 0.0, 0.0, 0.0 }; //Richtungsvektor
};

#endif //CAMERA_H