#ifndef MATERIALH
#define MATERIALH

#include "hittable.h"

class material {
public:
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;
};

vec3 random_in_unit_sphere() {
    vec3 p;
    do {
        p = 2.0*vec3(drand48(), drand48(), drand48()) - vec3(1.0, 1.0, 1.0);
    } while(dot(p,p) >= 1.0);
    return p;
}

class lambertian : public material {
public:
    lambertian(const vec3 &albedo) : albedo(albedo) {}
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
        vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        scattered = ray(rec.p, target-rec.p);
        attenuation = albedo;
        return true;
    }
    vec3 albedo;
};

vec3 reflect(vec3 direction, vec3 normal) {
    return direction - 2*dot(direction, normal)*normal;
}

class metal : public material {
public:
    metal(const vec3& albedo, float fz) : albedo(albedo) { fuzz = fz < 1 ? fz : 1; }
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
        vec3 reflected = reflect(r_in.direction().unit(), rec.normal);
        scattered = ray(rec.p, reflected + fuzz*random_in_unit_sphere());
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }
    vec3 albedo;
    float fuzz;
};

#endif