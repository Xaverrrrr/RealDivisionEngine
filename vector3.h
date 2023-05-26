#ifndef VECTOR3_H
	#define VECTOR3_H
#include <iostream>
class Vector3 {

public:
	Vector3(double x, double y, double z);
	Vector3();
	
	double length();
	void add(Vector3 vec);
	void subtract(Vector3 vec);

	static Vector3 cross(const Vector3& a, const Vector3& b);
	static double dot(const Vector3& a, const Vector3& b);
	static Vector3 normalize(const Vector3& a);

	double x;
	double y;
	double z;
};

#endif // !VECTOR3_H
