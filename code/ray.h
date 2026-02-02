#ifndef RAY_H
#define RAY_H

#include "vec3.h"
typedef struct{
	point3 orig;
	vec3 dir;
}ray;

inline point3
ray_at(ray* curr_ray,f64 t){
	point3 result = {0};
	result = add_vec3(curr_ray->orig, scale_vec3(curr_ray->dir, t));
	return result;
}

#endif
