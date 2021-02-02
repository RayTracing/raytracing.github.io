#ifndef BVH_H
#define BVH_H
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
#include "hittable_list.h"

#include <algorithm>


class bvh_node : public hittable {
  public:
    bvh_node();

    bvh_node(const hittable_list& list, double time0, double time1)
      : bvh_node(list.objects, 0, list.objects.size(), time0, time1)
    {}

    bvh_node(
        const std::vector<shared_ptr<hittable>>& src_objects,
        size_t start, size_t end, double time0, double time1
    ) {
        auto objects = src_objects; // Create a modifiable array of the source scene objects

        int axis = random_int(0,2);
        auto comparator = (axis == 0) ? box_x_compare
                        : (axis == 1) ? box_y_compare
                                      : box_z_compare;

        size_t object_span = end - start;

        if (object_span == 1) {
            left = right = objects[start];
        } else if (object_span == 2) {
            if (comparator(objects[start], objects[start+1])) {
                left = objects[start];
                right = objects[start+1];
            } else {
                left = objects[start+1];
                right = objects[start];
            }
        } else {
            std::sort(objects.begin() + start, objects.begin() + end, comparator);

            auto mid = start + object_span/2;
            left = make_shared<bvh_node>(objects, start, mid, time0, time1);
            right = make_shared<bvh_node>(objects, mid, end, time0, time1);
        }

        aabb box_left, box_right;

        if (!left->bounding_box(box_left) || !right->bounding_box(box_right))
            std::cerr << "No bounding box in bvh_node constructor.\n";

        box = surrounding_box(box_left, box_right);
    }

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
        if (!box.hit(r, ray_t))
            return false;

        bool hit_left = left->hit(r, ray_t, rec);
        bool hit_right = right->hit(r, interval(ray_tmin, hit_left ? rec.t : ray_tmax), rec);

        return hit_left || hit_right;
    }

    bool bounding_box(aabb& output_box) const override {
        output_box = box;
        return true;
    }

  public:
    shared_ptr<hittable> left;
    shared_ptr<hittable> right;
    aabb box;

  private:
    static bool box_compare(
        const shared_ptr<hittable> a, const shared_ptr<hittable> b, int axis_index
    ) {
        aabb box_a;
        aabb box_b;

        if (!a->bounding_box(box_a) || !b->bounding_box(box_b))
            std::cerr << "No bounding box in bvh_node constructor.\n";

        return box_a.axis(axis_index).min < box_b.axis(axis_index).min;
    }

    static bool box_x_compare (const shared_ptr<hittable> a, const shared_ptr<hittable> b) {
        return box_compare(a, b, 0);
    }

    static bool box_y_compare (const shared_ptr<hittable> a, const shared_ptr<hittable> b) {
        return box_compare(a, b, 1);
    }

    static bool box_z_compare (const shared_ptr<hittable> a, const shared_ptr<hittable> b) {
        return box_compare(a, b, 2);
    }
};


#endif
