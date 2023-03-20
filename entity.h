#ifndef ENTITY_H
	#define ENTITY_H

#include <vector>
#include <string>

using namespace std;

class Entity
{
	public:
		Entity(string name);
		void setPosition(vector<double> myPosition);
		void updatePosition(double x, double y, double z);
		vector<double> getPosition();
		string getName();

	private:
		string name;
		vector<double> position = { 0.0, 0.0, 0.0 };
};
#endif //!ENTITY_H