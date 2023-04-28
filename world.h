#ifndef WORLD_H
	#define WORLD_H

#include <string>
#include <vector>

#include "entity.h"
#include "wall.h"

using namespace std;

class World
{
	public:
		World(string name);

		void addEntity(Entity entity);
		vector<Entity> getEntities();
		void deleteEtity(Entity entity);

		void addWall(Wall wall);
		vector<Wall> getWalls();
		void deleteWall(Wall wall);


		void setMeasurements(vector<double>);
		vector<double> getMeasurements();


	private:
		string name;
		vector<double> measurements = { 0.0, 0.0, 0.0 };
		vector<Entity> entityList;
		vector<Wall> wallList;

};


#endif //!WORLD_H
