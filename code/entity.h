#ifndef ENTITY_H
#define ENTITY_H

#include "defines.h"
#include <math.h>

typedef struct{
	// sphere properties
	point3 center; // center of circle
	f64 radius;

	// hittable properties
	point3 p; // point where ray hit circle
	vec3 normal;
	f64 t;
	b32 front_face;
}entity;

/*
 * This function does
 * 1. calculates if ray has hit the circle
 * 2. if ray hit circle, find 
 * 		a)point where it hit, 
 * 		b) normal aka dir (from center to p) 
 * 		c)'t' scaler value tells how far ray whent to hit circle.
 */

void
set_face_normal(ray r, vec3 outward_normal,entity* rec){
	// Set the hit record normal vector.
	// NOTE: the parameter 'outward_normal' is assumed to be unit lenght.
	
	rec->front_face = dot_vec3(r.dir,outward_normal) < 0;
	rec->normal = rec->front_face? outward_normal : scale_vec3(outward_normal,-1.0);
}

b32
hit(ray r, f64 ray_tmin, f64 ray_tmax, entity* rec){

	vec3 oc = sub_vec3(rec->center,r.orig);
	f64 a = length_squared_vec3(r.dir);
	f64 h = dot_vec3(r.dir,oc);
	f64 c = length_squared_vec3(oc) - rec->radius*rec->radius;

	f64 discriminat = h*h - a*c;
	if(discriminat < 0) return FALSE;

	f64 sqrtd = sqrt(discriminat);
	// Find the nearest root that lies in the acceptable range.
	f64 root = (h - sqrtd) / a;
	if(root <= ray_tmin || ray_tmax <= root){
		root = (h + sqrtd) / a;
		if(root <= ray_tmin || ray_tmax <= root) return FALSE;
	}

	rec->t = root;
	rec->p = ray_at(&r,rec->t);
	vec3 outward_normal = scale_vec3(
							sub_vec3(rec->p, rec->center), 
							rec->radius);
	set_face_normal(r,outward_normal,rec);

	return TRUE;
}


#endif
