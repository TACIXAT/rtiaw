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

vec3 random_in_unit_sphere() {
	vec3 p;
	do {
		p = 2.0*vec3(drand48(), drand48(), drand48()) - vec3(1.0, 1.0, 1.0);
	} while(dot(p,p) >= 1.0);
	return p;
}

vec3 color(const ray& r, hittable *world) {
	hit_record rec;
	if(world->hit(r, 0.0, FLT_MAX, rec)) {
		vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		return 0.5*color(ray(rec.p,  target-rec.p), world);
	}

	vec3 unit = r.direction().unit();
	// normalize -1 to 1 -> 0 to 2 -> 0 to 1 
	float t = 0.5*(unit.y() + 1.0);
	vec3 color_a = (1.0-t)*vec3(1.0, 1.0, 1.0);
	vec3 color_b = t*vec3(0.5, 0.7, 1.0);
	return color_a+color_b;
}

int main() {
	int h = 200;
	int w = 400;
	int ns = 30;
	uint8_t data[w*h*3];

	hittable *list[2];
	list[0] = new sphere(vec3(0, 0, -1), 0.5);
	list[1] = new sphere(vec3(0, -100.5, -1), 100);
	hittable *world = new hittable_list(list, 2);
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
				
				v_color = v_color + color(r, world);
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
