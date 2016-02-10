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
#include "camera.h"

vec3 color(const ray& r, hittable *world, int depth) {
	hit_record rec;
	if(world->hit(r, 0.001, FLT_MAX, rec)) {
		vec3 attenuation;
		ray scattered;
		if(depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
			return attenuation*color(scattered, world, depth+1);
		} else {
			return vec3(0.0, 0.0, 0.0);
		}
	}

	vec3 unit = r.direction().unit();
	// normalize -1 to 1 -> 0 to 2 -> 0 to 1 
	float t = 0.5*(unit.y() + 1.0);
	vec3 color_a = (1.0-t)*vec3(1.0, 1.0, 1.0);
	vec3 color_b = t*vec3(0.1, 0.3, 0.7);
	return color_a+color_b;
}

#define NUM_HITTABLE 4

int main() {
	int h = 200;
	int w = 400;
	int ns = 100;
	uint8_t data[w*h*3];

	hittable *list[NUM_HITTABLE];
	list[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.5, 0.8, 0.3)));
	list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.2, 0.3)));
	list[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.7, 0.9, 0.4), 0.1));
	list[3] = new sphere(vec3(-1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.3), 0.7));
	hittable *world = new hittable_list(list, NUM_HITTABLE);
	camera cam;

	for(int i=(h-1); i>-1; --i) {
		for(int j=0; j<w; ++j) {
			// we start in the lower left, so (h-i-1)
			int hflip = (h-i-1);
			int buf_pos = 3*(hflip*w+j);

			vec3 v_color = vec3(0.0, 0.0, 0.0);
			for(int s=0; s<ns; ++s) {
				float u = float(j+drand48()) / (w-1);
				float v = float(i+drand48()) / (h-1);
				ray r = cam.get_ray(u, v);
				
				v_color = v_color + color(r, world, 0);
			}

			v_color = v_color / ns;
			v_color = v_color.get_sqrt();
			data[buf_pos+0] = (uint8_t)(v_color.r()*255.99);
			data[buf_pos+1] = (uint8_t)(v_color.g()*255.99);
			data[buf_pos+2] = (uint8_t)(v_color.b()*255.99);
		}
	}

	stbi_write_png("out.png", w, h, 3, data, 3*w);
}
