#ifndef SPHEREH
#define SPHEREH

#include "hittable.h"

class sphere : public hittable {
public: 
    sphere() {}
    sphere(vec3 v_center, float radius) : v_center(v_center), radius(radius) {}
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
    vec3 v_center;
    float radius;
};

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    vec3 oc = r.origin() - v_center;
    float a = dot(r.direction(), r.direction());
    float b = dot(oc, r.direction());
    float c = dot(oc, oc) - radius*radius;
    float discriminant = b*b - a*c;
    if(discriminant > 0) {
        float tmp = (-b - sqrt(discriminant)/(a));
        if(tmp < t_max && tmp > t_min) {
            rec.t = tmp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - v_center) / radius;
            return true;
        }
        tmp = (-b + sqrt(discriminant)/(a));
        if(tmp < t_max && tmp > t_min) {
            rec.t = tmp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - v_center) / radius;
            return true;   
        }
    }

    return false;
}

#endif
