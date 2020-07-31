#include "cl_header.h"

real_t abs_p3(t_p3 vect)
{
	return(vect.x * vect.x + vect.y * vect.y + vect.z * vect.z);
}