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
        float tmp = (-b - sqrt(discriminant))/a;
        if(tmp < t_max && tmp > t_min) {
            rec.t = tmp;
            rec.p = r.point_at_parameter(rec.t);
            // if(rec.p.x() > (v_center.x() + radius) || rec.p.x() < (v_center.x() - radius))
            //     return false;
            // if(rec.p.y() > (v_center.y() + radius) || rec.p.y() < (v_center.y() - radius))
            //     return false;
            rec.normal = ((rec.p - v_center) / radius).unit();
            // std::cout << rec.p.x() << "\t" << rec.p.y() << "\t" << rec.p.z() << std::endl;
            // std::cout << rec.normal.x() << "\t" << rec.normal.y() << "\t" << rec.normal.z() << std::endl << std::endl;
            // std::cout << v_center.x() << "\t" << v_center.y() << "\t" << v_center.z() << std::endl;
            // std::cout << radius << std::endl << std::endl;
            return true;
        }
        tmp = (-b + sqrt(discriminant))/a;
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
