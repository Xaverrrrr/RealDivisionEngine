#ifndef ENTITY_H
	#define ENTITY_H

#include <vector>
#include <string>
#include "vector3.h"

using namespace std;

class Entity
{
	public:

		Entity(string name);

		void			setPosition(Vector3 myPosition);
		Vector3			getPosition();
		void			updatePosition();

		void			setVelocity(Vector3 vel);
		Vector3			getVelocity();

		void			setName(string name);
		string			getName();
		
		void			setDimensions(Vector3 dimensions);
		Vector3			getDimensions();
		

	private:

		string name;

		Vector3 position;	//X,Y,Z

		Vector3 velocity;	//velX, velY, velZ

		Vector3 dimensions; //length, width, height
};
#endif //!ENTITY_H