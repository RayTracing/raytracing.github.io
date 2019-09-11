#ifndef HITTABLELISTH
#define HITTABLELISTH
//==================================================================================================
// Written in 2016 by Peter Shirley <ptrshrl@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related and
// neighboring rights to this software to the public domain worldwide. This software is distributed
// without any warranty.
//
// You should have received a copy (see file COPYING.txt) of the CC0 Public Domain Dedication along
// with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
//==================================================================================================

#include "hittable.h"
#include "random.h"


class hittable_list: public hittable  {
    public:
        hittable_list() {}
        hittable_list(hittable **l, int n) {list = l; list_size = n; }
        virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
        virtual bool bounding_box(float t0, float t1, aabb& box) const;
        virtual float  pdf_value(const vec3& o, const vec3& v) const;
        virtual vec3 random(const vec3& o) const;

        hittable **list;
        int list_size;
};

float hittable_list::pdf_value(const vec3& o, const vec3& v) const {
    float weight = 1.0/list_size;
    float sum = 0;
    for (int i = 0; i < list_size; i++)
        sum += weight*list[i]->pdf_value(o, v);
    return sum;
}

vec3 hittable_list::random(const vec3& o) const {
        int index = int(random_double() * list_size);
        return list[ index ]->random(o);
}


bool hittable_list::bounding_box(float t0, float t1, aabb& box) const {
    if (list_size < 1) return false;
    aabb temp_box;
    bool first_true = list[0]->bounding_box(t0, t1, temp_box);
    if (!first_true)
        return false;
    else
        box = temp_box;
    for (int i = 1; i < list_size; i++) {
        if(list[0]->bounding_box(t0, t1, temp_box)) {
            box = surrounding_box(box, temp_box);
        }
        else
            return false;
    }
    return true;
}

bool hittable_list::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
        hit_record temp_rec;
        bool hit_anything = false;
        double closest_so_far = t_max;
        for (int i = 0; i < list_size; i++) {
            if (list[i]->hit(r, t_min, closest_so_far, temp_rec)) {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }
        return hit_anything;
}

#endif

