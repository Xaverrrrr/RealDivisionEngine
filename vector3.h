#ifndef VECTOR3_H
	#define VECTOR3_H

class Vector3 {

public:
	Vector3(double x, double y, double z);
	Vector3();
	Vector3 normalise();
	double length();
	void add(Vector3 vec);
	void subtract(Vector3 vec);

	double x = 0.0;
	double y = 0.0;
	double z = 0.0;
};

#endif // !VECTOR3_H
