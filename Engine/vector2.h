#ifndef VECTOR2_H
	#define VECTOR2_H

class Vector2
{

public:
	Vector2(double x, double y);
	Vector2();
	Vector2 normalise();
	double length();
	void add(Vector2 vector);
	void subtract(Vector2 vector);

	double x = 0.0;
	double y = 0.0;
};

#endif
