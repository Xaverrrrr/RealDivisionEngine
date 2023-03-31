#ifndef WORLD_H
	#define WORLD_H

#include <string>
#include <vector>

#include "entity.h"

using namespace std;

class World
{
	public:
		World(string name);
		void addEntity(Entity* entity);
		vector<Entity*> getEntities();
		void deleteEtity(Entity* entity);
		void setMeasurements(vector<double>);
		vector<double> getMeasurements();


	private:
		string name;
		vector<double> measurements = { 0.0, 0.0, 0.0 };
		vector<Entity*> entityList;
		//vecor<Wall> wallList;

};


#endif //!WORLD_H
