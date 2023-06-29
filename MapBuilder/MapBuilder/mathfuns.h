#ifndef MATHFUNS_H
#define MATHFUNS_H

class MathFuns
{
public:

	static double PI;

	static double mapLinear(double x, double in_min, double in_max, double out_min, double out_max);

	static double radToDeg(double x);

	static double degToRad(double x);

	static double roundToDigit(double x, int nthDigit);
};
#endif