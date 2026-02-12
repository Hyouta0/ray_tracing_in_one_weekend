#include "color.h"
#include "ray.h"
#include "vec3.h"

#include "defines.h"
#include "logger.h"

#include <math.h>

inline b8
hit_sphere(point3 center,f64 radius, ray r){
	b8 result = FALSE;
	vec3 oc = sub_vec3(center,r.orig);
	f64 a = dot_vec3(r.dir,r.dir);
	f64 b = -2.0 * dot_vec3(r.dir,oc);
	f64 c = dot_vec3(oc,oc) - radius*radius;
	f64 discriminant = b*b - 4*a*c;
	
	result = (discriminant >= 0);
	return result;
}

inline color
ray_color(ray r){
	color result = {0};

	point3 sphere = (point3) { 0.0,0.0,-1.0}; // sphere is center of screen.. on viewport
	if(hit_sphere(sphere,0.5,r)){
		result = (color) {1,0,0};
		log_del("\rHit the circle\n");
		assert(0);
	}else{
		log_dev("\rMiss Circle");
		vec3 unit_direction = unit_vector_vec3(r.dir);
		f64 a = 0.5 * (unit_direction.y + 1.0);

		result = add_vec3(scale_vec3((color){1.0,1.0,1.0}, (1.0 - a)),
						  scale_vec3((color){0.5, 0.7, 1.0},a));
	}
	return result;
}


int main(void){
	// Image
	f64 aspect_ratio = 16.0 / 9.0;
	i32 image_width = 400;

	// Calculate the image height, and ensure that it's at least 1
	i32 image_height = (i32) (image_width/aspect_ratio);
	image_height = (image_height < 1)? 1 : image_height;
    
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
	vec3 viewport_upper_left = sub_vec3(camera_center,
										sub_vec3((vec3){0,0,focal_length},
												 sub_vec3(scale_vec3(viewport_u,0.5),
													 	  scale_vec3(viewport_v,0.5))));
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

			color pixel_color = ray_color(r);
			write_color(stdout,&pixel_color);
		}
	}
	log_dev("\nDone.     \n");

	return 0;
}

