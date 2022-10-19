#include <cprocessing.h>
#include <math.h>

CP_Vector AngleToVector(float angle)
{
	float rads = CP_Math_Radians(angle);
	CP_Vector ret = { cos(rads),sin(rads) };

	return CP_Vector_Normalize(ret);
}
