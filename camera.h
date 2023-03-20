#ifndef CAMERA_H
	#define CAMERA_H

#include <vector>
#include <iostream>
#include "entity.h"

using namespace std;

class Camera: public Entity {

public:
	Camera(string name);
	void setFOV(int fov);
	int getFOV();
	void setRotation(vector<double> rotation);
	vector<double> getRotation();
	void updateRotation(double xy, double xz);
	void renderScreen(vector<Entity*> entities);
	double radToDeg(double x);
	void setRenderDistance(int x);
	int getRenderDistance();

private:
	int FOVX; //in degrees from center => double to get actual visual field
	int FOVY;
	int renderDistance;
	string name;
	vector<double> position = { 0.0, 0.0, 0.0 };
	vector<double> rotation = { 0.0, 0.0 }; //XY und XZ
};

#endif //CAMERA_H