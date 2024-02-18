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

#include "aabb.h"
#include "hittable.h"
#include "hittable_list.h"

#include <algorithm>


class bvh_node : public hittable {
  public:
    bvh_node(const hittable_list& list) : bvh_node(list.objects) {}

    bvh_node(const std::vector<shared_ptr<hittable>>& src_objects) {
        // Build the bounding box of the span of source objects.
        bbox = aabb::empty;

        size_t size = src_objects.size ();

        for (size_t object_index=0; object_index < size; object_index++)
            bbox = aabb(bbox, src_objects[object_index]->bounding_box());

        int axis = bbox.longest_axis();

        auto comparator = (axis == 0) ? box_x_compare
                        : (axis == 1) ? box_y_compare
                                      : box_z_compare;

        auto objects = src_objects; // A modifiable array of the source scene objects

        if (size == 1) {
            left = right = objects[0];
        } else if (size == 2) {
            if (comparator(objects[0], objects[1])) {
                left = objects[0];
                right = objects[1];
            } else {
                left = objects[1];
                right = objects[0];
            }
        } else {
            auto mid = size/2;
            std::nth_element(objects.begin(), objects.begin() + mid, objects.end(), comparator);
            
            auto objects_left = std::vector<std::shared_ptr<hittable>>(objects.begin(), objects.begin()+mid);
            auto objects_right = std::vector<std::shared_ptr<hittable>>(objects.begin()+mid, objects.end());

            left = make_shared<bvh_node>(objects_left);
            right = make_shared<bvh_node>(objects_right);
        }
    }

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
        if (!bbox.hit(r, ray_t))
            return false;

        bool hit_left = left->hit(r, ray_t, rec);
        bool hit_right = right->hit(r, interval(ray_t.min, hit_left ? rec.t : ray_t.max), rec);

        return hit_left || hit_right;
    }

    aabb bounding_box() const override { return bbox; }

  private:
    shared_ptr<hittable> left;
    shared_ptr<hittable> right;
    aabb bbox;

    static bool box_compare(
        const shared_ptr<hittable> a, const shared_ptr<hittable> b, int axis_index
    ) {
        return a->bounding_box().axis(axis_index).min < b->bounding_box().axis(axis_index).min;
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
