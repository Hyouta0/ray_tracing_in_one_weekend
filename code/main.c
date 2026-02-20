#include "defines.h"
#include "rtweekend.h"
#include "logger.h"
#include "entity.h"
#include "camera.h"

int main(void){
	sphere_list world;

	add_sphere(&world,(point3){0,0,-1},0.5);
	add_sphere(&world,(point3){0,-100.5,-1},100);
    
	camera cam;
	f64 aspect_ratio = 16.0 / 9.0;
	i32 image_width = 400;

	create_camera(aspect_ratio,image_width,&cam);

	render(&world,&cam);

	log_dev("\nDone.     \n");

	return 0;
}

