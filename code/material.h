#ifndef MATERIAL_H
#define MATERIAL_H

#include "defines.h"

typedef enum{
	MATERIAL_TYPE_LAMBERTIAN,
	/* paper, cloth, unsine materials, unpolished wood etc */
	MATERIAL_TYPE_METAL,
	/* fucking reflectative matertial, like metals and mirror
	 * etc based of fuzze propertive more_reflective is near 0
	 * 								 less_reflective is near 1
	 *  froste metal reflect less even mirror
	 */
	MATERIAL_TYPE_DIELECTRIC,
	/* glass, water etc where ray is not reflected but refracted
	 * means ray go through them but are bent little bit due to 
	 * material
	 * NOTE: here some rays are reflected while some are refracted
	 */
	MATERIAL_TYPE_NONE
}Material_type;

typedef struct{
	Material_type material_type;
	color albedo;
	f64 fuzz;
	f64 refraction_index;
}Material;

inline Material
create_material(Material_type mat_type, color mat_color,
				f64 fuzz, f64 refraction_index){
	Material mat;
	mat.material_type = mat_type;
	mat.albedo = mat_color;
	mat.fuzz = fuzz;
	mat.refraction_index = refraction_index;
	return mat; 
}
#define create_material_lambertian(color)\
	create_material(MATERIAL_TYPE_LAMBERTIAN,color,0.0,0.0)
#define create_material_metal(color,fuzz)\
	create_material(MATERIAL_TYPE_METAL,color,fuzz,0.0)
#define create_material_dielectric(r_idx)\
	create_material(MATERIAL_TYPE_DIELECTRIC,(color){1,1,1},0.0,r_idx)

#endif
