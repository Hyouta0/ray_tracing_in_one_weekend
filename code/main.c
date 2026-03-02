#include "defines.h"
#include "rtweekend.h"
#include "logger.h"
#include "entity.h"
#include "camera.h"
// tmp
#include "material.h"

int main(void){
	sphere_list world;
	  
	color ground_color= (color){0.8,0.8,0.0};
	color center_color = (color){0.1,0.2,0.5};
	color right_color = (color){0.8,0.6,0.2};
	Material material_ground = create_material_lambertian(ground_color);
	Material material_center = create_material_lambertian(center_color);
	Material material_left = create_material_dielectric(1.50);
	Material material_bubble = create_material_dielectric(1.00/1.50);
	Material material_right = create_material_metal(right_color,1.0);


	add_sphere(&world,(point3){ 0.0,-100.5,-1.0},100,&material_ground);
	add_sphere(&world,(point3){ 0.0, 0.0  ,-1.2},0.5,&material_center);
	add_sphere(&world,(point3){-1.0, 0.0  ,-1.0},0.5,&material_left);
	add_sphere(&world,(point3){-1.0, 0.0  ,-1.0},0.4,&material_bubble);
	add_sphere(&world,(point3){ 1.0, 0.0  ,-1.0},0.5,&material_right);

	/*
	f64 r = cos(pi/4.0);

	color color_left = (color){0,0,1.0};
	color color_right = (color){1.0,0,0};
	Material material_left = create_material_lambertian(color_left);
	Material material_right = create_material_lambertian(color_right);

	add_sphere(&world,(point3){-r,0,-1},r,&material_left);
	add_sphere(&world,(point3){r,0,-1},r,&material_right);
	*/


	camera cam;
	f64 aspect_ratio = 16.0 / 9.0;
	i32 image_width = 400;
	i32 samples_per_pixel = 100;
	i32 max_depth = 50;

	f64 vfov = 20;
	point3 lookfrom = {-2,2,1};
	point3 lookat   = {0,0,-1};
	vec3 vup        = {0,1,0};

	create_camera(aspect_ratio,image_width,samples_per_pixel,max_depth,
				  vfov,lookfrom,lookat,vup,&cam);

	render(&world,&cam);

	log_dev("\nDone.     \n");

	return 0;
}

