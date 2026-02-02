#include "color.h"
#include "ray.h"
#include "vec3.h"

#include "defines.h"
#include <stdio.h>

inline color
ray_color(ray* r){
	color result = {0};
	vec3 unit_direction = unit_vector_vec3(r->dir);
	f64 a = 0.5 * (unit_direction.y + 1.0);

	result = add_vec3(scale_vec3((color){1.0,1.0,1.0}, (1.0 - a)),
					  scale_vec3((color){0.5, 0.7, 1.0},a));
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
												 sub_vec3(scale_vec3(viewport_u,1.0/2.0),
													 	  scale_vec3(viewport_v,1.0/2.0))));
	vec3 pixel00_loc = add_vec3(viewport_upper_left,
								scale_vec3(add_vec3(pixel_delta_u, 
													pixel_delta_v), 
											0.5));

	// Render

	fprintf(stdout,"P3\n%d %d\n255\n",image_width,image_height);

	for(i32 col = 0; col < image_height; col++){
		fprintf(stderr,"\rScanlines remaining: %d",image_height - col);
		fflush(stderr);
		for(i32 row = 0; row < image_width; row++){
			point3 pixel_center = add_vec3(pixel00_loc,
										 add_vec3(scale_vec3(pixel_delta_u,row),
											 	  scale_vec3(pixel_delta_v,col)));
			vec3 ray_direction = sub_vec3(pixel_center,camera_center);
			ray r = (ray){camera_center,ray_direction};

			color pixel_color = ray_color(&r);
			write_color(stdout,&pixel_color);
		}
	}
	fprintf(stderr,"\rDone.    \n");
	return 0;
}
