#ifndef RTWEEKEND_H
#define RTWEEKEND_H
#include "defines.h"

// Constants
const f64 pi = 3.1415926535897932385;
// Utility Functions
inline f64
degrees_to_radians(f64 degrees){
	return degrees * pi / 180.0;
}

#include <stdlib.h>
inline f64
random_f64(void){
	f64 random_number = 0.0;
	random_number = rand()/(RAND_MAX + 1.0);
	return random_number;
}

inline f64
random_in_range_f64(f64 min, f64 max){
	f64 random_number = 0.0;
	random_number = min + (max - min )*random_f64();
	return random_number;
}

// Common Headers
#include "color.h"
#include "interval.h"
#include "ray.h"
#include "vec3.h"

#endif
