#ifndef ENTITY_H
#define ENTITY_H

#include "defines.h"
#include "ray.h"
#include <math.h>
// TODO: use sphere pointer while functions, less data movement
#define MAX_SPHERES 1024

typedef struct{
	point3 p;
	vec3 normal;
	f64 t;
	b32 front_face;
}hit_record;

typedef struct{
	point3 center;
	f64 radius;
}sphere;

typedef struct{ 
	i32 sphere_count;
	sphere spheres[MAX_SPHERES];
}sphere_list;


inline void
set_face_normal(ray r, vec3 outward_normal,hit_record* rec){
	// Sets the hit record normal vector.
	// NOTE: the parameter 'outward_normal' is assumed to have unit length
	rec->front_face = dot_vec3(r.dir,outward_normal) < 0;
	rec->normal = rec->front_face? outward_normal : scale_vec3(outward_normal,-1.0);
}

b32
hit(ray r, interval ray_t,sphere* entity, hit_record* rec){
	vec3 oc = sub_vec3(entity->center,r.orig);
	f64 a = length_squared_vec3(r.dir);
	f64 h = dot_vec3(r.dir,oc);
	f64 c = length_squared_vec3(oc) - entity->radius*entity->radius;

	f64 discriminant = h*h - a*c;
	if(discriminant < 0) return FALSE;

	f64 sqrtd = sqrt(discriminant);
	// Find the nearest root that lies in the acceptable range.
	f64 root = (h - sqrtd) / a;
	if(!interval_contains(ray_t,root)){
		root = (h + sqrtd)/a;
		if(!interval_contains(ray_t,root)) return FALSE;
	}

	rec->t = root;
	rec->p = ray_at(&r,rec->t);
	vec3 outward_normal = scale_vec3(sub_vec3(rec->p,entity->center)
									,1.0/entity->radius);
	set_face_normal(r,outward_normal,rec);

	return TRUE;
}


inline sphere
create_sphere(point3 center, f64 radius){
	sphere sp = {0};
	sp.center = center;
	sp.radius = max_num(radius,0);
	return sp;
}

b32
hit_sphere_list(ray r, 
				interval ray_t,
				sphere_list* sl,hit_record* rec){
	hit_record temp_rec = {0};
	b32 hit_anything = FALSE;
	f64 closest_so_far = ray_t.max;

	for(i32 sphere_index = 0;sphere_index< sl->sphere_count;sphere_index++){
		if(hit(r,create_interval(ray_t.min,closest_so_far),
			   sl->spheres+sphere_index,&temp_rec)){
			hit_anything = TRUE;
			closest_so_far = temp_rec.t;
			*rec = temp_rec;
		}
	}
	return hit_anything;
}

inline void
add_sphere(sphere_list* sl,point3 center,f64 radius){

	if(sl->sphere_count < MAX_SPHERES){
		sl->spheres[sl->sphere_count++] = create_sphere(center,radius);	
	}else log_err("sphere_list is full\n");
}

#endif
