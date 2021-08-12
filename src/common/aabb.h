#ifndef AABB_H
#define AABB_H
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


class aabb {
  public:
    aabb() {} // The default AABB is empty, since intervals are empty by default.

    aabb(const interval& ix, const interval& iy, const interval& iz)
      : x(ix), y(iy), z(iz) { }

    aabb(const point3& a, const point3& b) {
        // Treat the two points a and b as extrema for the bounding box, so we don't require a
        // particular minimum/maximum coordinate order.
        x = interval(fmin(a[0],b[0]), fmax(a[0],b[0]));
        y = interval(fmin(a[1],b[1]), fmax(a[1],b[1]));
        z = interval(fmin(a[2],b[2]), fmax(a[2],b[2]));
    }

    aabb(const aabb& box0, const aabb& box1) {
        x = interval(box0.x, box1.x);
        y = interval(box0.y, box1.y);
        z = interval(box0.z, box1.z);
    }

    const interval& axis(int n) const {
        if (n == 1) return y;
        if (n == 2) return z;
        return x;
    }

    aabb pad() {
        // Return an AABB that has no side narrower than some delta, padding if necessary.
        const double delta = 0.0001;
        interval new_x = (x.size() >= delta) ? x : x.expand(delta);
        interval new_y = (y.size() >= delta) ? y : y.expand(delta);
        interval new_z = (z.size() >= delta) ? z : z.expand(delta);

        return aabb(new_x, new_y, new_z);
    }

    #if 1
        // GitHub Issue #817
        // For some reason I haven't figured out yet, this version is 10x faster than the
        // version below. I'll come back and figure out why (and in the process, probably figure
        // out how to configure CMake to create a profile build). Parking this here for now, to
        // be removed before the v4 release.

        bool hit(const ray& r, interval ray_t) const {
            for (int a = 0; a < 3; a++) {
                auto t0 = fmin((axis(a).min - r.origin()[a]) / r.direction()[a],
                               (axis(a).max - r.origin()[a]) / r.direction()[a]);
                auto t1 = fmax((axis(a).min - r.origin()[a]) / r.direction()[a],
                               (axis(a).max - r.origin()[a]) / r.direction()[a]);
                ray_t.min = fmax(t0, ray_t.min);
                ray_t.max = fmin(t1, ray_t.max);
                if (ray_t.max <= ray_t.min)
                    return false;
            }
            return true;
        }
    #else
        bool hit(const ray& r, interval ray_t) const {
            auto r_origin = r.origin();
            auto r_dir = r.direction();
            for (int a = 0; a < 3; a++) {
                auto invD = 1.0f / r_dir[a];
                auto orig = r_origin[a];
                auto t0 = (axis(a).min - orig) * invD;
                auto t1 = (axis(a).max - orig) * invD;
                if (invD < 0)
                    std::swap(t0, t1);
                if (fmin(t1, ray_t.max) <= fmax(t0, ray_t.min))
                    return false;
            }
            return true;
        }
    #endif

  public:
    interval x, y, z;
};

aabb operator+(const aabb& bbox, const vec3& offset) {
    return aabb(bbox.x + offset.x(), bbox.y + offset.y(), bbox.z + offset.z());
}

aabb operator+(const vec3& offset, const aabb& bbox) {
    return bbox + offset;
}


#endif
