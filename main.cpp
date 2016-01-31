#include <iostream>
#include <stdint.h>
#include "vec3.h"
#include "ray.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

vec3 color(const ray& r) {
	vec3 unit = r.direction().unit();
	// normalize -1 to 1 -> 0 to 2 -> 0 to 1 
	float t = 0.5*(unit.y() + 1.0);
	vec3 white = (1.0-t)*vec3(1.0, 1.0, 1.0);
	vec3 blue = t*vec3(1.0, 0.2, 0.3);
	return white+blue;
}

int main() {
	int h = 200;
	int w = 400;
	uint8_t data[w*h*3];

	vec3 v_origin(0.0, 0.0, 0.0);
	vec3 v_lower_left(-2.0, -1.0, -1.0);
	vec3 v_height(0.0, 2.0, 0.0);
	vec3 v_width(4.0, 0.0, 0.0);

	for(int i=(h-1); i>-1; --i) {
		for(int j=0; j<w; ++j) {
			// we start in the lower left, so (h-i-1)
			int hflip = (h-i-1);
			int buf_pos = 3*(hflip*w+j);
			float u = float(j) / (w-1);
			float v = float(i) / (h-1);

			vec3 v_dir = v_lower_left + u*v_width + v*v_height;
			ray r_curr(v_origin, v_dir);
			vec3 v_color = color(r_curr);

			data[buf_pos+0] = (uint8_t)(v_color.r()*255.99);
			data[buf_pos+1] = (uint8_t)(v_color.g()*255.99);
			data[buf_pos+2] = (uint8_t)(v_color.b()*255.99);
		}
	}

	stbi_write_png("out.png", w, h, 3, data, 3*w);
}