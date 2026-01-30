#ifndef VEC3_H
#define VEC3_H

typedef union{
	struct{
		f64 x;
		f64 y;
		f64 z;
	};
	f64 e[3];
}Vec3;

inline Vec3
vec3_add(Vec3 v1, Vec3 v2){
	Vec3 result = {0};

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;

	return result;
}


inline Vec3
vec3_sub(Vec3 v1, Vec3 v2){
	Vec3 result = {0};

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	
	return result;
}


inline Vec3
vec3_scale(Vec3 v1,u32 num){
	Vec3 result = {0};

	result.x = v1.x * num;
	result.y = v1.y * num;
	result.z = v1.z * num;

	return result;
}

inline f64
vec3_inner_product(Vec3 v1, Vec3 v2){
	f64 result = 0.0;
	result = v1.x*v2.x + v1.y*v2.y + v1.z*v2.z ;
	return result;
}


inline Vec3
vec3_hadamarn_product(Vec3 v1, Vec3 v2){
	Vec3 result = {0};
	result.x = v1.x * v2.x;
	result.y = v1.y * v2.y;
	result.z = v1.z * v2.z;
	return result;
}

inline Vec3
vec3_cross_product(Vec3 u, Vec3 v){
	Vec3 result = {
		u.e[1] * v.e[2] - u.e[2] * v.e[1],
		u.e[2] * v.e[0] - u.e[0] * v.e[2],
		u.e[0] * v.e[1] - u.e[1] * v.e[0]
	};
	return result;
}

inline f64
vec3_length_squared(Vec3 v1){
	f64 result = 0.0;
	result = v1.x*v1.x + v1.y*v1.y + v1.z*v1.z;
	return result;
}

#include <math.h>

inline f64
vec3_length(Vec3 v1){
	f64 result = 0.0;
	result = sqrt(vec3_length_squared(v1));
	return result;
}



#endif
