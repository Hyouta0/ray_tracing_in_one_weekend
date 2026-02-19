#ifndef RTWEEKEND_H
#define RTWEEKEND_H
#include "defines.h"

// Constants
const f64 infinity = 1.7976931348623157E+308;
const f64 pi = 3.1415926535897932385;
// Utility Functions
inline f64
degrees_to_radians(f64 degrees){
	return degrees * pi / 180.0;
}

// Common Headers
#include "color.h"
#include "ray.h"
#include "vec3.h"

#endif
