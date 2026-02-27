#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <stdio.h>
#include  "interval.h"

typedef vec3 color;

inline f64
linear_to_gamma(f64 linear_component){
	if(linear_component > 0)
		return sqrt(linear_component);
	return 0;
}

internal void
write_color(FILE* output, color* in_color){
	// Apply a linear to gamma transform for gamma 2
	f64 r = linear_to_gamma(in_color->r);
	f64 g = linear_to_gamma(in_color->g);
	f64 b = linear_to_gamma(in_color->b);

	// Translate the [0,1] component values to the byte range [0,255]
	interval itvl = create_interval(0.000,0.999);

	i32 rbyte = (i32)(255.999 * interval_clamp(itvl,r));
	i32 gbyte = (i32)(255.999 * interval_clamp(itvl,g));
	i32 bbyte = (i32)(255.999 * interval_clamp(itvl,b));

	// Write out the pixel color components
	fprintf(output,"%d %d %d\n",rbyte,gbyte,bbyte);
}
#endif
