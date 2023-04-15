#ifndef WALL_H
	#define WALL_H
	#include "entity.h"

class Wall
{
	public:

		Wall(string name);

		void setCoordinates(vector<vector<double>> cords);
		vector<vector<double>> getCoordinates();
		void setDimensions(vector<double> x);
		vector<double> getDimensions();

	private:

		string name;

		vector<vector<double>> coordinates = { {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0} }; //starting point and end point of wall
		vector<double> dimensions = { 0.0, 0.0, 0.0 };
};
#endif // !WALL_H
