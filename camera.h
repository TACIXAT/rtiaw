#ifndef CAMERAH
#define CAMERAH

#include "ray.h"

class camera {
public:
	camera() {
		v_origin = vec3(0.0, 0.0, 0.0);
		v_lower_left = vec3(-2.0, -1.0, -1.0);
		v_height = vec3(0.0, 2.0, 0.0);
		v_width = vec3(4.0, 0.0, 0.0);
	}

	ray get_ray(float u, float v) {
		vec3 v_dir = v_lower_left + u*v_width + v*v_height - v_origin;
		return ray(v_origin, v_dir);
	}

	vec3 v_origin;
	vec3 v_lower_left;
	vec3 v_height;
	vec3 v_width;
};

#endif