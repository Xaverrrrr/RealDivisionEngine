#ifndef WALL_H
	#define WALL_H
	#include "entity.h"

class Wall : public Entity
{
	public:

		Wall(string name);

	private:

		string name;

		vector<vector<double>> coordinates = { {0.0, 0.0}, {0.0, 0.0} }; //starting point and end point of wall
};
#endif // !WALL_H
