#ifndef ENTITY_H
	#define ENTITY_H

#include <vector>
#include <string>
#include "vector3.h"
#include "point.h"

using namespace std;

class Entity
{
	public:

		Entity(string name);
		Entity(string name, Vector3 position, vector<Vector3> verteces);

		void			setPosition(Vector3 myPosition);
		Vector3			getPosition();
		void			updatePosition();

		void			setVelocity(Vector3 vel);
		Vector3			getVelocity();

		void			setName(string name);
		string			getName();
		
		void			setVerteces(vector<Vector3> v);
		vector<Vector3> getVerteces();

	private:

		string name;

		Vector3 position;	//X,Y,Z

		Vector3 velocity;	//velX, velY, velZ

		vector<Vector3> verteces;

};
#endif //!ENTITY_H