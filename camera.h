#ifndef CAMERA_H
	#define CAMERA_H

#include <vector>
#include <iostream>

#include "entity.h"
#include "wall.h"
#include "mathFuns.h"


class Camera: public Entity {
public:
	Camera(string name);

	void setFovXY(int fov);
	int getFovXY();

	void setRotation(vector<double> rotation);
	vector<double> getRotation();
	void updateRotation(double xy, double xz);

	vector<vector<int>> renderEntities(vector<Entity*> entities);
	vector<vector<vector<int>>> renderWalls(vector<Wall*> walls); //Returns a list of pairs (left and right side of wall) which themselfes contain a pair of both the x coordinate on the screen and the height of the line 

	void setRenderDistance(int x);
	int getRenderDistance();

private:

	string name;

	int FovXY; //in degrees from center => double to get actual visual field
	int FovXZ;

	int renderDistance;

	vector<double> rotation = { 0.0, 0.0, 0.0 }; //Richtungsvektor
};

#endif //CAMERA_H