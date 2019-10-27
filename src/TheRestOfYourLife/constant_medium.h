#ifndef CONSTANT_MEDIUM_H
#define CONSTANT_MEDIUM_H
//==================================================================================================
// Originally written in 2016 by Peter Shirley <ptrshrl@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related and
// neighboring rights to this software to the public domain worldwide. This software is distributed
// without any warranty.
//
// You should have received a copy (see file COPYING.txt) of the CC0 Public Domain Dedication along
// with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
//==================================================================================================

#include "common/rtweekend.h"
#include "hittable.h"
#include "material.h"
#include "texture.h"

#include <float.h>


class constant_medium : public hittable  {
    public:
        constant_medium(hittable *b, double d, texture *a) : boundary(b), density(d) {
            phase_function = new isotropic(a);
        }
        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const;
        virtual bool bounding_box(double t0, double t1, aabb& output_box) const {
            return boundary->bounding_box(t0, t1, output_box);
        }
        hittable *boundary;
        double density;
        material *phase_function;
};


bool constant_medium::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {

    // Print occasional samples when debugging. To enable, set enableDebug true.
    const bool enableDebug = false;
    bool debugging = enableDebug && random_double() < 0.00001;

    hit_record rec1, rec2;

    if (boundary->hit(r, -infinity, infinity, rec1)) {
        if (boundary->hit(r, rec1.t+0.0001, infinity, rec2)) {

            if (debugging) std::cerr << "\nt0 t1 " << rec1.t << " " << rec2.t << '\n';

            if (rec1.t < t_min) rec1.t = t_min;
            if (rec2.t > t_max) rec2.t = t_max;

            if (rec1.t >= rec2.t)
                return false;
            if (rec1.t < 0)
                rec1.t = 0;

            auto distance_inside_boundary = (rec2.t - rec1.t) * r.direction().length();
            auto hit_distance = -(1/density) * log(random_double());

            if (hit_distance < distance_inside_boundary) {

                rec.t = rec1.t + hit_distance / r.direction().length();
                rec.p = r.point_at_parameter(rec.t);

                if (debugging) {
                    std::cerr << "hit_distance = " <<  hit_distance << '\n'
                              << "rec.t = " <<  rec.t << '\n'
                              << "rec.p = " <<  rec.p << '\n';
                }

                rec.normal = vec3(1,0,0);  // arbitrary
                rec.mat_ptr = phase_function;
                return true;
            }
        }
    }
    return false;
}

#endif
