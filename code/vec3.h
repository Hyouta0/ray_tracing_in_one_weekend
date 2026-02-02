#ifndef VEC3_H
#define VEC3_H

#include "defines.h"

typedef union vec3_u{
	f64 e[3];
	struct{
		union{
			f64 x,r,s,u;
		};
		union{
			f64 y,g,t,v;
		};
		union{
			f64 z,b,p,w;
		};
	};
}vec3;

typedef vec3 point3;

inline vec3
add_vec3(vec3 vector_0, vec3 vector_1){
	vec3 result = {0};
	result.x = vector_0.x + vector_1.x;
	result.y = vector_0.y + vector_1.y;
	result.z = vector_0.z + vector_1.z;
	return result;
}

inline vec3
sub_vec3(vec3 vector_0, vec3 vector_1){
	vec3 result = {0};
	result.x = vector_0.x - vector_1.x;
	result.y = vector_0.y - vector_1.y;
	result.z = vector_0.z - vector_1.z;
	return result;
}

inline vec3
scale_vec3(vec3 vector_0,f64 value){
	vec3 result = {0};
	result.x = vector_0.x * value;
	result.y = vector_0.y * value;
	result.z = vector_0.z * value;
	return result;
}

inline vec3
dot_vec3(vec3 vector_0, vec3 vector_1){
	vec3 result = {0};
	result.x = vector_0.x * vector_1.x;
	result.y = vector_0.y * vector_1.y;
	result.z = vector_0.z * vector_1.z;
}

inline vec3
cross_vec3(vec3 vector_0, vec3 vector_1){
	vec3 result = {0};
	result.x = vector_0.e[1] * vector_1.e[2] - vector_0.e[2] * vector_1.e[1];
	result.y = vector_0.e[2] * vector_1.e[0] - vector_0.e[0] * vector_1.e[2];
	result.y = vector_0.e[0] * vector_1.e[1] - vector_0.e[1] * vector_1.e[0];
	return result;
}

inline f64 
length_squared_vec3(vec3 vector_0){
	f64 result = 0.0;
	result += vector_0.x * vector_0.x;
	result += vector_0.y * vector_0.y;
	result += vector_0.z * vector_0.z;
	return result;
}


#include <math.h>

inline f64 
lenght_vec3(vec3 vector_0){
	f64 result = 0.0;
	result = sqrt(length_squared_vec3(vector_0));
	return result;
}

inline vec3
unit_vector_vec3(vec3 vector_0){
	vec3 result = {0};
	result = scale_vec3(vector_0,
						1.0/lenght_vec3(vector_0));
	return result;
}
#endif
