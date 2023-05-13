#include "mathFuns.h"
#include <math.h>

double MathFuns::PI = 3.141592653589793;

double MathFuns::radToDeg(double x) {
	return (x * (180 / MathFuns::PI));
}

double MathFuns::degToRad(double x) {
	return (x * (MathFuns::PI / 180));
}

double MathFuns::roundToDigit(double x, int nthDigit)
{
	return round((x * pow(10, nthDigit) / pow(10, nthDigit)));
}


double MathFuns::mapLinear(double x, double in_min, double in_max, double out_min, double out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
