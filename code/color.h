#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <stdio.h>
#include  "interval.h"

typedef vec3 color;

internal void
write_color(FILE* output, color* in_color){

	// Translate the [0,1] component values to the byte range [0,255]
	interval itvl = create_interval(0.000,0.999);

	i32 rbyte = (i32)(255.999 * interval_clamp(itvl,in_color->r));
	i32 gbyte = (i32)(255.999 * interval_clamp(itvl,in_color->g));
	i32 bbyte = (i32)(255.999 * interval_clamp(itvl,in_color->b));

	// Write out the pixel color components
	fprintf(output,"%d %d %d\n",rbyte,gbyte,bbyte);
}
#endif
