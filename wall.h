#ifndef WALL_H
	#define WALL_H
	#include "entity.h"
	#include "vector3.h"

class Wall
{
	public:

		Wall(string name);

		void						setCoordinates(Vector3 start, Vector3 end);
		vector<Vector3>				getCoordinates();
		void						setDimensions(Vector3 x);
		Vector3						getDimensions();

	private:

		string name;

		vector<Vector3> coordinates; //starting point and end point of wall
		Vector3 dimensions;
};
#endif // !WALL_H
