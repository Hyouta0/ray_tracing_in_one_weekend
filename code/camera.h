#ifndef CAMERA_H
#define CAMERA_H
#include "entity.h"

typedef struct{
	f64 aspect_ratio;// ratio of image width over height
	i32 image_width;// Rendered image width in pixel count 
	i32 samples_per_pixel;// Count of random samples for each pixel;
	i32 max_depth;

	i32 image_height;        // Rendered image height
	f64 pixel_samples_scale; // Color scale factor for a sum of pixel samples
	point3 center;           // Camera center
	point3 pixel00_loc;      // Location of pixel 0,0
	vec3   pixel_delta_u;    // Offset to pixel to the right
	vec3   pixel_delta_v;    // offset to pixel below
}camera;

/*
 * NOTE: (always check order of compution of math)
 * when normaly using -,/  C used right to left
 * if you copy same directly while using sub_vec() & scale_vec() 
 * it will be wrong as order for compution of funcions is left to right
 * !! Was err that was hard to find.
 */
internal void 
create_camera(f64 aspect_ratio, i32 image_width,
			  i32 samples_per_pixel, i32 max_depth, camera* kodak){
	kodak->aspect_ratio = aspect_ratio;
	kodak->image_width = image_width;
	kodak->samples_per_pixel = samples_per_pixel;
	kodak->max_depth = max_depth;

	kodak->image_height = (i32) (image_width/aspect_ratio);
	kodak->image_height = (kodak->image_height < 1)? 1: kodak->image_height;

	kodak->pixel_samples_scale = 1.0 / kodak->samples_per_pixel;

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

#define quick_camera(cam) create_camera(1.0,100,10,10,#cam)

inline vec3
sample_square(void){
	vec3 random_point_vec = {random_f64() - 0.5, // make range [-0.5 to 0.5]
							 random_f64() - 0.5,
							 0};

	return random_point_vec;
}

internal ray
get_ray(i32 i, i32 j,camera* cam){
	vec3 offset = sample_square();
	point3 pixel_sample = add_vec3(cam->pixel00_loc,
								   add_vec3(
									   scale_vec3(cam->pixel_delta_u,(i + offset.x)),
									   scale_vec3(cam->pixel_delta_v,(j + offset.y))
									   ));
	point3 ray_origin = cam->center;
	vec3 ray_direction = sub_vec3(pixel_sample, ray_origin);
	return (ray){ray_origin,ray_direction};

}

inline color
ray_color(ray r, i32 depth, sphere_list* sl){
	if(depth <= 0) return (color){0,0,0};
	hit_record rec;

	if(hit_sphere_list(r,create_interval(0.001,INFINITY),sl,&rec)){
		vec3 direction = random_on_hemisphere(rec.normal);
		return scale_vec3(
				ray_color((ray){rec.p,direction},depth-1,sl),
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
		log_del("\rScanlines remaining: %d",kodak->image_height-row-1);
		for(i32 col = 0; col < kodak->image_width; col++){
			color pixel_color = {0,0,0};
			/* in one pixel making 100 rays which are little offset from 
			 * center of pixel, but are inside pixel
			 */
			for(i32 sample = 0; sample < kodak->samples_per_pixel;sample++){
				ray r = get_ray(col,row,kodak);
				pixel_color = add_vec3(pixel_color,ray_color(r,kodak->max_depth,world));
			}
			pixel_color = scale_vec3(pixel_color,kodak->pixel_samples_scale);
			write_color(stdout,&pixel_color);
		}
	}

}

#endif
