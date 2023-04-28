#ifndef WALL_H
	#define WALL_H
	#include "entity.h"
	#include "vector3.h"
	#include "point.h"

class Wall
{
	public:

		Wall(string name);

		void						setCoordinates(Point lowerLeft, Point lowerRight, Point upperLeft, Point upperRight);
		vector<Point>				getCoordinates();

	private:

		string						name;
		vector<Point>				coordinates; //Four vertices of wall
		
};
#endif // !WALL_H
