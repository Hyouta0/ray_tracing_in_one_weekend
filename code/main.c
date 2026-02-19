
#include "defines.h"
#include "rtweekend.h"
#include "logger.h"
#include "entity.h"


/*
 * NOTE: (always check order of compution of math)
 * when normaly using -,/  C used right to left
 * if you copy same directly while using sub_vec() & scale_vec() 
 * it will be wrong as order for compution of funcions is left to right
 * !! Was err that was hard to find.
 */



inline color
ray_color(ray r,sphere_list* sl){
	hit_record rec;

	if(hit_sphere_list(r,0,infinity,sl,&rec)){
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


int main(void){
	// Image
	f64 aspect_ratio = 16.0 / 9.0;
	i32 image_width = 400;

	// Calculate the image height, and ensure that it's at least 1
	i32 image_height = (i32) (image_width/aspect_ratio);
	image_height = (image_height < 1)? 1 : image_height;
	// World
	sphere_list world;
	add_sphere(&world,(point3){0,0,-1},0.5);
	add_sphere(&world,(point3){0,-100.5,-1},100);
    
	// Camera
	f64 focal_length = 1.0;
	f64 viewport_height = 2.0;
	f64 viewport_width = viewport_height * ((f64)image_width/image_height);
	point3 camera_center = (point3){0,0,0};

	// Calculate the vectors across the horizontal and down the vertical viewport edges.
	vec3 viewport_u = (vec3) {viewport_width, 0, 0};
	vec3 viewport_v = (vec3) {0, -viewport_height, 0};


	// Calculate the horizontal and vertical delta vectors from pixel to pixel.
	vec3 pixel_delta_u = scale_vec3(viewport_u, 1.0/image_width);
	vec3 pixel_delta_v = scale_vec3(viewport_v,1.0/image_height);


	// Calculate the location of the upper left pixel.
	vec3 viewport_upper_left = sub_vec3(
									sub_vec3(
										 sub_vec3(camera_center,(vec3){0,0,focal_length})
												 ,scale_vec3(viewport_u,0.5))
									,scale_vec3(viewport_v,0.5));
	//log_vec3(viewport_upper_left);
	vec3 pixel00_loc = add_vec3(viewport_upper_left,
								scale_vec3(add_vec3(pixel_delta_u, 
													pixel_delta_v), 
											0.5));

	// Render
	fprintf(stdout,"P3\n%d %d\n255\n",image_width,image_height);
	log_del("\n\n");

	for(i32 row = 0; row < image_height; row++){
		log_del("\033[1A \rScanlines remaining: %d\n",image_height-row-1);
		for(i32 col = 0; col < image_width; col++){
			point3 pixel_center = add_vec3(pixel00_loc,
										 add_vec3(scale_vec3(pixel_delta_u,col),
											 	  scale_vec3(pixel_delta_v,row)));
			vec3 ray_direction = sub_vec3(pixel_center,camera_center);
			ray r = (ray){camera_center,ray_direction};

			color pixel_color = ray_color(r,&world);
			write_color(stdout,&pixel_color);
		}
	}
	log_dev("\nDone.     \n");

	return 0;
}

