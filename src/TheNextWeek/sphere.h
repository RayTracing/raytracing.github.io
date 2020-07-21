#ifndef SPHERE_H
#define SPHERE_H
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


class sphere : public hittable  {
    public:
        sphere() {}
        sphere(point3 ctr, double r, shared_ptr<material> m)
            : center(ctr), radius(r), mat_ptr(m) {};

        virtual bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec)
            const override;

        virtual bool bounding_box(double time_start, double time_end, aabb& output_box)
            const override;

    public:
        point3 center;
        double radius;
        shared_ptr<material> mat_ptr;
};


bool sphere::bounding_box(double time_start, double time_end, aabb& output_box) const {
    output_box = aabb(
        center - vec3(radius, radius, radius),
        center + vec3(radius, radius, radius));
    return true;
}


void get_sphere_uv(const point3& p, double& u, double& v) {
    auto phi = atan2(p.z(), p.x());
    auto theta = asin(p.y());
    u = 1-(phi + pi) / (2*pi);
    v = (theta + pi/2) / pi;
}


bool sphere::hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const {
    vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius*radius;

    auto discriminant = half_b*half_b - a*c;

    if (discriminant > 0) {
        auto root = sqrt(discriminant);

        auto temp = (-half_b - root) / a;
        if (ray_tmin < temp && temp < ray_tmax) {
            rec.t = temp;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            get_sphere_uv((rec.p-center)/radius, rec.u, rec.v);
            rec.mat_ptr = mat_ptr;
            return true;
        }

        temp = (-half_b + root) / a;
        if (ray_tmin < temp && temp < ray_tmax) {
            rec.t = temp;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            get_sphere_uv((rec.p-center)/radius, rec.u, rec.v);
            rec.mat_ptr = mat_ptr;
            return true;
        }
    }

    return false;
}


#endif
