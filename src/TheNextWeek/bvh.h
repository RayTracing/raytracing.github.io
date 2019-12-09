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

#include "common/rtweekend.h"
#include "hittable.h"


class bvh_node : public hittable  {
    public:
        bvh_node() {}
        bvh_node(hittable **l, int n, double time0, double time1);

        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const;
        virtual bool bounding_box(double t0, double t1, aabb& output_box) const;

        hittable *left;
        hittable *right;
        aabb box;
};

bool bvh_node::bounding_box(double t0, double t1, aabb& output_box) const {
    output_box = box;
    return true;
}

bool bvh_node::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    if (!box.hit(r, t_min, t_max))
        return false;

    bool hit_left = left->hit(r, t_min, t_max, rec);
    bool hit_right = right->hit(r, t_min, hit_left ? rec.t : t_max, rec);

    return hit_left || hit_right;
}

int box_x_compare (const void * a, const void * b) {
    aabb box_left, box_right;
    hittable *ah = *(hittable**)a;
    hittable *bh = *(hittable**)b;

    if (!ah->bounding_box(0,0, box_left) || !bh->bounding_box(0,0, box_right))
        std::cerr << "no bounding box in bvh_node constructor\n";

    if (box_left.min().x() - box_right.min().x() < 0.0)
        return -1;
    else
        return 1;
}

int box_y_compare (const void * a, const void * b)
{
    aabb box_left, box_right;
    hittable *ah = *(hittable**)a;
    hittable *bh = *(hittable**)b;

    if (!ah->bounding_box(0,0, box_left) || !bh->bounding_box(0,0, box_right))
        std::cerr << "no bounding box in bvh_node constructor\n";

    if (box_left.min().y() - box_right.min().y() < 0.0)
        return -1;
    else
        return 1;
}

int box_z_compare (const void * a, const void * b)
{
    aabb box_left, box_right;
    hittable *ah = *(hittable**)a;
    hittable *bh = *(hittable**)b;

    if (!ah->bounding_box(0,0, box_left) || !bh->bounding_box(0,0, box_right))
        std::cerr << "no bounding box in bvh_node constructor\n";

    if (box_left.min().z() - box_right.min().z() < 0.0)
        return -1;
    else
        return 1;
}

bvh_node::bvh_node(hittable **l, int n, double time0, double time1) {
    int axis = random_int(0,2);

    if (axis == 0)
        qsort(l, n, sizeof(hittable *), box_x_compare);
    else if (axis == 1)
        qsort(l, n, sizeof(hittable *), box_y_compare);
    else
        qsort(l, n, sizeof(hittable *), box_z_compare);

    if (n == 1) {
        left = right = l[0];
    }
    else if (n == 2) {
        left = l[0];
        right = l[1];
    }
    else {
        left = new bvh_node(l, n/2, time0, time1);
        right = new bvh_node(l + n/2, n - n/2, time0, time1);
    }

    aabb box_left, box_right;

    if (  !left->bounding_box (time0, time1, box_left)
       || !right->bounding_box(time0, time1, box_right)
    )
        std::cerr << "no bounding box in bvh_node constructor\n";

    box = surrounding_box(box_left, box_right);
}

#endif
