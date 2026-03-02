#include "defines.h"
#include "rtweekend.h"
#include "logger.h"
#include "entity.h"
#include "camera.h"
// tmp
#include "material.h"

int main(void){
	sphere_list world;
	Material material_list[MAX_SPHERES] = {0};
	u32 material_index = 0;
	  
	color ground_color= (color){0.5,0.5,0.5};
	Material material_ground = create_material_lambertian(ground_color);
	add_sphere(&world,(point3){ 0,-1000,0},1000,&material_ground);

	for(i32 a = -11; a < 11; a++){
		for(i32 b = -11; b < 11; b++){
			f64 choose_mat = random_f64();
			point3 center = {a+0.9*random_f64(),0.2,b+0.9*random_f64()};
			if(length_vec3(sub_vec3(center,(point3){4,0.2,0})) > 0.9){
				Material sphere_material = {0};
				if(choose_mat <0.8){
					//diffuse
					color albedo = mul_vec3(random_vec3(),random_vec3());
					sphere_material = create_material_lambertian(albedo);
				}else if(choose_mat < 0.95){
					//metal
					color albedo = random_in_range_vec3(0.5,1);
					f64 fuzz = random_in_range_f64(0,0.5);
					sphere_material = create_material_metal(albedo,fuzz);
				}else{
					sphere_material = create_material_dielectric(1.5);
				}
				material_list[material_index] = sphere_material;
				add_sphere(&world,center,0.2,material_list+material_index);
				material_index++;
			}
		}
	}


	Material material1 = create_material_dielectric(1.5);
	add_sphere(&world,(point3){0,1,0},1.0,&material1);

	color material2_color = {0.4,0.2,0.1};
	Material material2 = create_material_lambertian(material2_color);
	add_sphere(&world,(point3){-4,1,0},1.0,&material2);

	color material3_color = {0.7,0.6,0.5};
	Material material3 = create_material_metal(material3_color,0.0);
	add_sphere(&world,(point3){4,1,0},1.0,&material3);


	camera cam;
	f64 aspect_ratio = 16.0 / 9.0;
	i32 image_width = 1200;
	i32 samples_per_pixel = 500;
	i32 max_depth = 50;

	f64 vfov = 20;
	point3 lookfrom = {13,2,3};
	point3 lookat   = {0,0,0};
	vec3 vup        = {0,1,0};

	f64 defocus_angle = 0.6;
	f64 focus_dist = 10.0;

	create_camera(aspect_ratio,image_width,samples_per_pixel,max_depth,
				  vfov,lookfrom,lookat,vup,defocus_angle,focus_dist,&cam);

	render(&world,&cam);

	log_dev("\nDone.     \n");

	return 0;
}

