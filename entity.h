#ifndef ENTITY_H
	#define ENTITY_H

#include <vector>
#include <string>

using namespace std;

class Entity
{
	public:

		Entity(string name);

		void			setPosition(vector<double> myPosition);
		vector<double>	getPosition();
		void			updatePosition();

		void			setVelocity(vector<double> vel);
		vector<double>	getVelocity();

		void			setName(string name);
		string			getName();
		
		void			setDimensions(vector<double> dimensions);
		vector<double>	getDimensions();
		

	private:

		string name;

		vector<double> position		= { 0.0, 0.0, 0.0 }; //X,Y,Z

		vector<double> velocity		= { 0.0, 0.0, 0.0 }; //velX, velY, velZ

		vector<double> dimensions	= { 0.0, 0.0, 0.0 }; //length, width, height
};
#endif //!ENTITY_H