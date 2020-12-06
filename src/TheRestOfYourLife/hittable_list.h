#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H
//==============================================================================================
// Originally written in 2016 by Peter Shirley <ptrshrl@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related and
// neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy (see file COPYING.txt) of the CC0 Public Domain Dedication
// along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
//==============================================================================================

#include "rtweekend.h"

#include "hittable.h"

#include <memory>
#include <vector>


class hittable_list : public hittable {
  public:
    hittable_list() {}
    hittable_list(shared_ptr<hittable> object) { add(object); }

    void clear() { objects.clear(); }
    void add(shared_ptr<hittable> object) { objects.push_back(object); }

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
        hit_record temp_rec;
        auto hit_anything = false;
        auto closest_so_far = ray_t.max;

        for (const auto& object : objects) {
            if (object->hit(r, interval(ray_t.min, closest_so_far), temp_rec)) {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }

        return hit_anything;
    }

    bool bounding_box(double time_start, double time_end, aabb& output_box) const override {
        if (objects.empty()) return false;

        aabb temp_box;
        bool first_box = true;

        for (const auto& object : objects) {
            if (!object->bounding_box(time_start, time_end, temp_box)) return false;
            output_box = first_box ? temp_box : surrounding_box(output_box, temp_box);
            first_box = false;
        }

        return true;
    }

    double pdf_value(const point3 &o, const vec3 &v) const override {
        auto weight = 1.0/objects.size();
        auto sum = 0.0;

        for (const auto& object : objects)
            sum += weight * object->pdf_value(o, v);

        return sum;
    }

    vec3 random(const vec3 &o) const override {
        auto int_size = static_cast<int>(objects.size());
        return objects[random_int(0, int_size-1)]->random(o);
    }

  public:
    std::vector<shared_ptr<hittable>> objects;
};


#endif
