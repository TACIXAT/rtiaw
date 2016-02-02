#ifndef HITTABLELISTH
#define HITTABLELISTH

#include "hittable.h"

class hittable_list : public hittable {
public:
    hittable_list() {}
    hittable_list(hittable **hittables, int count) : hittables(hittables), count(count) {}
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
    hittable** hittables;
    int count;
};

bool hittable_list::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    hit_record local_rec;
    float closest = t_max;
    bool hit_something = false;
    for(int i=0; i<count; ++i) {
        hittable *h = hittables[i];
        if(h->hit(r, t_min, closest, local_rec)) {
            hit_something = true;
            closest = local_rec.t;
            rec = local_rec;
        }
    }  

    return hit_something;
}

#endif