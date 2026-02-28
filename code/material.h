#ifndef MATERIAL_H
#define MATERIAL_H

#include "defines.h"

typedef enum{
	MATERIAL_TYPE_LAMBERTIAN,
	MATERIAL_TYPE_METAL,
	MATERIAL_TYPE_NONE
}Material_type;

typedef struct{
	Material_type material_type;
	color albedo;
	f64 fuzz;
}Material;

inline Material
create_material(Material_type mat_type, color mat_color,f64 fuzz){
	Material mat;
	mat.material_type = mat_type;
	mat.albedo = mat_color;
	mat.fuzz = fuzz;
	return mat; 
}
#define create_material_lambertian(color)\
	create_material(MATERIAL_TYPE_LAMBERTIAN,color,0.0)
#define create_material_metal(color,fuzz)\
	create_material(MATERIAL_TYPE_METAL,color,fuzz)

#endif
