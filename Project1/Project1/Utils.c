/*
All content © 2021 DigiPen Institute of Technology Singapore, all rights reserved.
*/

#include <cprocessing.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

CP_Vector AngleToVector(float angle)
{
	float rads = CP_Math_Radians(angle);
	CP_Vector ret = { (float) cos(rads),(float) sin(rads) };

	return CP_Vector_Normalize(ret);
}
