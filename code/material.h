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
}Material;

inline Material
create_material(Material_type mat_type, color mat_color){
	Material mat;
	mat.material_type = mat_type;
	mat.albedo = mat_color;
	return mat; 
}

#endif
