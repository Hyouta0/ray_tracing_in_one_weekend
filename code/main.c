#include <stdio.h>
#include "defines.h"

int main(void){

	i32 image_width = 256;
	i32 image_height = 256;

	fprintf(stdout,"P3\n%d %d\n255\n",image_width,image_height);

	for(i32 col = 0; col < image_height; col++){
		fprintf(stderr,"\rScanlines remaining: %d",image_height - col);
		fflush(stderr);
		for(i32 row = 0; row < image_width; row++){
			f64 r = (f64) row / (image_width - 1);
			f64 g = (f64) col / (image_height - 1);
			f64 b = 0.0;

			i32 ir = (i32)( 255.999 * r);
			i32 ig = (i32)( 255.999 * g);
			i32 ib = (i32)( 255.999 * b);

			fprintf(stdout,"%d %d %d\n",ir,ig,ib);
		}
	}
	return 0;
}
