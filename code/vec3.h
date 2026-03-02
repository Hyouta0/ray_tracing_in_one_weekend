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
mul_vec3(vec3 vector_0, vec3 vector_1){
	vec3 result = {0};
	result.x = vector_0.x * vector_1.x;
	result.y = vector_0.y * vector_1.y;
	result.z = vector_0.z * vector_1.z;
	return result;
}

inline vec3
cross_vec3(vec3 vector_0, vec3 vector_1){
	vec3 result = {0};
	result.x = vector_0.e[1] * vector_1.e[2] - vector_0.e[2] * vector_1.e[1];
	result.y = vector_0.e[2] * vector_1.e[0] - vector_0.e[0] * vector_1.e[2];
	result.z = vector_0.e[0] * vector_1.e[1] - vector_0.e[1] * vector_1.e[0];
	return result;
}

inline f64
dot_vec3(vec3 vector_0, vec3 vector_1){
	f64 result = 0.0;
	result = vector_0.x * vector_1.x +
			 vector_0.y * vector_1.y +
			 vector_0.z * vector_1.z;
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

inline b32
near_zero(vec3 vector_0){
	f64 s = 1e-8;
	return (fabs(vector_0.x) < s) 
			&& (fabs(vector_0.y) < s) 
			&& (fabs(vector_0.z) < s);
}

inline f64 
length_vec3(vec3 vector_0){
	f64 result = 0.0;
	result = sqrt(length_squared_vec3(vector_0));
	return result;
}

inline vec3
unit_vector_vec3(vec3 vector_0){
	vec3 result = {0};
	result = scale_vec3(vector_0,
						1.0/length_vec3(vector_0));
	return result;
}

#include "rtweekend.h"

inline vec3
random_vec3(void){
	return (vec3){random_f64(),random_f64(),random_f64()};
}

inline vec3
random_in_range_vec3(f64 min, f64 max){
	return (vec3)
	{ random_in_range_f64(min,max),
	  random_in_range_f64(min,max),
	  random_in_range_f64(min,max) };
		
}

// Diffuse Materials 
inline vec3
random_unit_vector_vec3(void){
	while(TRUE){
		vec3 p = random_in_range_vec3(-1,1);
		f64 lensq = length_squared_vec3(p); // radius sqed
		if(1e-160 < lensq && lensq <= 1){ // f64 can support 10^-160 values
			return scale_vec3(p,1/sqrt(lensq));
		}
	}
}

inline vec3
random_on_hemisphere(vec3 normal){
	vec3 on_unit_sphere = random_unit_vector_vec3();
	if(dot_vec3(on_unit_sphere,normal) > 0.0) // In the same hemisphere as the normal
		return on_unit_sphere;
	else
		return scale_vec3(on_unit_sphere,-1);
}

inline vec3
reflect_vec3(vec3 v, vec3 n){
	return sub_vec3(v,
			scale_vec3(n,2.0*dot_vec3(v,n)));
}

inline vec3 
refract_vec3(vec3 uv, vec3 n,f64 etai_over_etat){
	f64 cos_theta = min_num(dot_vec3(scale_vec3(uv,-1),n),1.0);
	vec3 r_out_perp = scale_vec3(
							add_vec3(uv,scale_vec3(n,cos_theta))
							,etai_over_etat);
	vec3 r_out_parallel = scale_vec3(n
			,-sqrt(fabs(1.0 - length_squared_vec3(r_out_perp))));
	return add_vec3(r_out_perp,r_out_parallel);
}

// Defocuse
inline vec3
random_in_unit_disk(void){
	while(TRUE){
		vec3 p = (vec3){random_in_range_f64(-1,1)
						,random_in_range_f64(-1,1)
						,0};
		if(length_squared_vec3(p) < 1) return p;
	}
}

#endif
