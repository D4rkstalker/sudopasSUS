#include <cprocessing.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

//Utils.c -cargame.c

CP_Vector AngleToVector(float angle)
{
	float rads = CP_Math_Radians(angle);
	CP_Vector ret = { (float) cos(rads),(float) sin(rads) };

	return CP_Vector_Normalize(ret);
}
