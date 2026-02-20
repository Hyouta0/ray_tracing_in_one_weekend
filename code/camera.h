#ifndef CAMERA_H
#define CAMERA_H
#include "entity.h"

typedef struct{
	f64 aspect_ratio;// ratio of image width over height
	i32 image_width;// Rendered image width in pixel count 
	i32 image_height;
	point3 center;
	point3 pixel00_loc;
	vec3   pixel_delta_u;
	vec3   pixel_delta_v;
}camera;

/*
 * NOTE: (always check order of compution of math)
 * when normaly using -,/  C used right to left
 * if you copy same directly while using sub_vec() & scale_vec() 
 * it will be wrong as order for compution of funcions is left to right
 * !! Was err that was hard to find.
 */
internal void 
create_camera(f64 aspect_ratio,i32 image_width,camera* kodak){
	kodak->aspect_ratio = aspect_ratio;
	kodak->image_width = image_width;

	kodak->image_height = (i32) (image_width/aspect_ratio);
	kodak->image_height = (kodak->image_height < 1)? 1: kodak->image_height;

	kodak->center = (point3){0,0,0}; 

	//Determine viewport dimensions.
	f64 focal_length = 1.0;
	f64 viewport_height = 2.0;
	f64 viewport_width = viewport_height * ((f64)image_width/kodak->image_height);

	// Calculate the vectors across the horizontal and down the vertical viewport edges.
	vec3 viewport_u = (vec3) {viewport_width,0,0};
	vec3 viewport_v = (vec3) {0,-viewport_height,0};

	// Calculate the horizonatl and vertical delta vectors from pixel to pixel
	kodak->pixel_delta_u = scale_vec3(viewport_u,1.0/image_width);
	kodak->pixel_delta_v = scale_vec3(viewport_v,1.0/kodak->image_height);

	point3 viewport_upper_left = 
		sub_vec3(sub_vec3(
					sub_vec3(kodak->center,(vec3){0,0,focal_length})
					,scale_vec3(viewport_u,0.5))
				,scale_vec3(viewport_v,0.5));
	kodak->pixel00_loc = add_vec3(viewport_upper_left,
			scale_vec3(add_vec3(kodak->pixel_delta_u,
								kodak->pixel_delta_v),
						0.5));


}

#define quick_camera(cam) create_camera(cam,1.0,100)

inline color
ray_color(ray r,sphere_list* sl){
	hit_record rec;

	if(hit_sphere_list(r,create_interval(0,INFINITY),sl,&rec)){
		return scale_vec3(
					add_vec3(rec.normal,
							 (color){1,1,1}),
					0.5);	
	}

	vec3 unit_direction = unit_vector_vec3(r.dir);
	f64 a = 0.5*(unit_direction.y + 1.0);
	return add_vec3(
					scale_vec3((color){1.0,1.0,1.0},(1.0 -a)),
					scale_vec3((color){0.5,0.7,1.0},a)
					);
	
}

internal void 
render(sphere_list *world,camera* kodak){	
	// Render
	fprintf(stdout,"P3\n%d %d\n255\n",kodak->image_width,kodak->image_height);
	log_del("\n\n");

	for(i32 row = 0; row < kodak->image_height; row++){
		log_del("\033[1A \rScanlines remaining: %d\n",kodak->image_height-row-1);
		for(i32 col = 0; col < kodak->image_width; col++){
			point3 pixel_center = add_vec3(kodak->pixel00_loc,
										 add_vec3(scale_vec3(kodak->pixel_delta_u,col),
											 	  scale_vec3(kodak->pixel_delta_v,row)));
			vec3 ray_direction = sub_vec3(pixel_center,kodak->center);
			ray r = (ray){kodak->center,ray_direction};

			color pixel_color = ray_color(r,world);
			write_color(stdout,&pixel_color);
		}
	}

}

#endif
