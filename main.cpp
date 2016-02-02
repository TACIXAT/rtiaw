#include <iostream>
#include <stdint.h>
#include <stdlib.h>
#include <cfloat>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "vec3.h"
#include "ray.h"
#include "hittable_list.h"
#include "sphere.h"

vec3 color(const ray& r, hittable *world) {
	hit_record rec;
	if(world->hit(r, 0.0, FLT_MAX, rec)) {
		return 0.5*(rec.normal.unit()+1.0);
	}

	vec3 unit = r.direction().unit();
	// normalize -1 to 1 -> 0 to 2 -> 0 to 1 
	float t = 0.5*(unit.y() + 1.0);
	vec3 white = (1.0-t)*vec3(1.0, 1.0, 1.0);
	vec3 blue = t*vec3(0.3, 0.4, 1.0);
	return white+blue;
}

int main() {
	int h = 200;
	int w = 400;
	int ns = 100;
	uint8_t data[w*h*3];

	vec3 v_origin(0.0, 0.0, 0.0);
	vec3 v_lower_left(-2.0, -1.0, -1.0);
	vec3 v_height(0.0, 2.0, 0.0);
	vec3 v_width(4.0, 0.0, 0.0);

	hittable *s_center = new sphere(vec3(0, 0, -1), 0.5);
	hittable *s_big = new sphere(vec3(0, -100.5, -1), 100);
	hittable *world = new hittable_list();
	((hittable_list*)world)->hittables.push_back(s_center);
	((hittable_list*)world)->hittables.push_back(s_big);

	for(int i=(h-1); i>-1; --i) {
		for(int j=0; j<w; ++j) {
			// we start in the lower left, so (h-i-1)
			int hflip = (h-i-1);
			int buf_pos = 3*(hflip*w+j);

			vec3 v_color = vec3(0.0, 0.0, 0.0);
			for(int s=0; s<ns; ++s) {
				float u = float(j+drand48()) / (w-1);
				float v = float(i+drand48()) / (h-1);

				vec3 v_dir = v_lower_left + u*v_width + v*v_height;
				ray r_curr(v_origin, v_dir);
				v_color = v_color + color(r_curr, world);
			}

			v_color = v_color / ns;

			data[buf_pos+0] = (uint8_t)(v_color.r()*255.99);
			data[buf_pos+1] = (uint8_t)(v_color.g()*255.99);
			data[buf_pos+2] = (uint8_t)(v_color.b()*255.99);
		}
	}

	stbi_write_png("out.png", w, h, 3, data, 3*w);
}