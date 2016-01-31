#include <iostream>
#include <stdint.h>
#include "vec3.h"
#include "ray.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int main() {
	int h = 200;
	int w = 400;
	uint8_t data[w*h*3] = {0};

	for(int i=0; i<h; ++i) {
		for(int j=0; j<w; ++j) {
			int pos = 3*(i*w+j);
			data[pos+0] = 255;
			data[pos+1] = (uint8_t)(i*255/h);
			data[pos+2] = (uint8_t)(j*255/w);
		}
	}

	stbi_write_png("out.png", w, h, 3, data, 3*w);
}