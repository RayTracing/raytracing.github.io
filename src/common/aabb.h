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
    aabb() {}

    aabb(const point3& a, const point3& b) {
        // Treat the two points a and b as extrema for the bounding box, so we don't require a
        // particular minimum/maximum coordinate order.
        minimum = point3(fmin(a[0],b[0]), fmin(a[1],b[1]), fmin(a[2],b[2]));
        maximum = point3(fmax(a[0],b[0]), fmax(a[1],b[1]), fmax(a[2],b[2]));
    }

    aabb(aabb box0, aabb box1) {
        minimum = {
            fmin(box0.min().x(), box1.min().x()),
            fmin(box0.min().y(), box1.min().y()),
            fmin(box0.min().z(), box1.min().z())
        };

        maximum = {
            fmax(box0.max().x(), box1.max().x()),
            fmax(box0.max().y(), box1.max().y()),
            fmax(box0.max().z(), box1.max().z())
        };
    }

    point3 min() const { return minimum; }
    point3 max() const { return maximum; }

    bool hit(const ray& r, interval ray_t) const {
        for (int a = 0; a < 3; a++) {
            auto t0 = fmin((minimum[a] - r.origin()[a]) / r.direction()[a],
                           (maximum[a] - r.origin()[a]) / r.direction()[a]);
            auto t1 = fmax((minimum[a] - r.origin()[a]) / r.direction()[a],
                           (maximum[a] - r.origin()[a]) / r.direction()[a]);
            ray_t.min = fmax(t0, ray_t.min);
            ray_t.max = fmin(t1, ray_t.max);
            if (ray_t.max <= ray_t.min)
                return false;
        }
        return true;
    }

  public:
    point3 minimum;
    point3 maximum;
};


#endif
