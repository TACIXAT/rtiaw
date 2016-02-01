#ifndef HITTABLELISTH
#define HITTABLELISTH

#include "hittable.h"
#include <list>

class hittable_list : public hittable {
public:
    hittable_list() {}
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
    std::list<hittable*> hittables;
};

bool hittable_list::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    std::list<hittable*>::const_iterator it;
    hit_record local_rec;
    float closest = t_max;
    bool hit_something = false;
    for(it=hittables.begin(); it!=hittables.end(); it++) {
        hittable *h = *it;
        if(h->hit(r, t_min, closest, local_rec)) {
            hit_something = true;
            closest = local_rec.t;
            rec = local_rec;
        }
    }  

    return hit_something;
}

#endif