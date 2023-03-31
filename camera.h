#ifndef CAMERA_H
	#define CAMERA_H

#include <vector>
#include <iostream>

#include "entity.h"
#include "mathFuns.h"


class Camera: public Entity {
public:
	Camera(string name);

	void setFovXY(int fov);
	int getFovXY();

	void setRotation(vector<double> rotation);
	vector<double> getRotation();
	void updateRotation(double xy, double xz);

	vector<vector<int>> renderScreen(vector<Entity*> entities);

	void setRenderDistance(int x);
	int getRenderDistance();

private:

	string name;

	int FovXY; //in degrees from center => double to get actual visual field
	int FovXZ;

	int renderDistance;


	vector<double> position = { 0.0, 0.0, 0.0 };
	vector<double> rotation = { 0.0, 0.0 }; //XY und XZ
};

#endif //CAMERA_H