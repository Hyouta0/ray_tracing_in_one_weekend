#include "defines.h"
#include "rtweekend.h"
#include "logger.h"
#include "entity.h"
#include "camera.h"
// tmp
#include "material.h"

int main(void){
	sphere_list world;

	Material material_ground = create_material(MATERIAL_TYPE_LAMBERTIAN,
											   (color){0.8,0.8,0.0});
	Material material_center = create_material(MATERIAL_TYPE_LAMBERTIAN,
											   (color){0.1,0.2,0.5});
	Material material_left = create_material(MATERIAL_TYPE_METAL,
											   (color){0.8,0.8,0.0});
	Material material_right = create_material(MATERIAL_TYPE_METAL,
											   (color){0.8,0.8,0.0});



	add_sphere(&world,(point3){ 0.0,-100.5,-1.0},100,&material_ground);
	add_sphere(&world,(point3){ 0.0, 0.0  ,-1.2},0.5,&material_center);
	add_sphere(&world,(point3){-1.0, 0.0  ,-1.0},0.5,&material_left);
	add_sphere(&world,(point3){ 1.0, 0.0  ,-1.0},0.5,&material_right);

	camera cam;
	f64 aspect_ratio = 16.0 / 9.0;
	i32 image_width = 400;
	i32 samples_per_pixel = 100;
	i32 max_depth = 50;

	create_camera(aspect_ratio,image_width
				  ,samples_per_pixel,max_depth,&cam);

	render(&world,&cam);

	log_dev("\nDone.     \n");

	return 0;
}

