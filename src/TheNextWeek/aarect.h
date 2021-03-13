#ifndef AARECT_H
#define AARECT_H
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


class xy_rect : public hittable {
  public:
    xy_rect() {}

    xy_rect(double _x0, double _x1, double _y0, double _y1, double _k, shared_ptr<material> _m)
      : x0(_x0), x1(_x1), y0(_y0), y1(_y1), k(_k), mat(_m),
        bbox(point3(x0, y0, k-0.0001), point3(x1, y1, k+0.0001))
    {}

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
        auto t = (k-r.origin().z()) / r.direction().z();
        if (!ray_t.contains(t))
            return false;

        auto x = r.origin().x() + t*r.direction().x();
        auto y = r.origin().y() + t*r.direction().y();
        if (x < x0 || x1 < x || y < y0 || y1 < y)
            return false;

        rec.u = (x-x0)/(x1-x0);
        rec.v = (y-y0)/(y1-y0);
        rec.t = t;
        auto outward_normal = vec3(0, 0, 1);
        rec.set_face_normal(r, outward_normal);
        rec.mat = mat;
        rec.p = r.at(t);

        return true;
    }

    aabb bounding_box() const override { return bbox; }

  public:
    double x0, x1, y0, y1, k;
    shared_ptr<material> mat;
    aabb bbox;
};


class xz_rect : public hittable {
  public:
    xz_rect() {}

    xz_rect(double _x0, double _x1, double _z0, double _z1, double _k, shared_ptr<material> _m)
      : x0(_x0), x1(_x1), z0(_z0), z1(_z1), k(_k), mat(_m),
        bbox(point3(x0, k-0.0001, z0), point3(x1, k+0.0001, z1))
    {}

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
        auto t = (k-r.origin().y()) / r.direction().y();
        if (!ray_t.contains(t))
            return false;

        auto x = r.origin().x() + t*r.direction().x();
        auto z = r.origin().z() + t*r.direction().z();
        if (x < x0 || x1 < x || z < z0 || z1 < z)
            return false;

        rec.u = (x-x0)/(x1-x0);
        rec.v = (z-z0)/(z1-z0);
        rec.t = t;
        auto outward_normal = vec3(0, 1, 0);
        rec.set_face_normal(r, outward_normal);
        rec.mat = mat;
        rec.p = r.at(t);

        return true;
    }

    aabb bounding_box() const override { return bbox; }

  public:
    double x0, x1, z0, z1, k;
    shared_ptr<material> mat;
    aabb bbox;
};


class yz_rect : public hittable {
  public:
    yz_rect() {}

    yz_rect(double _y0, double _y1, double _z0, double _z1, double _k, shared_ptr<material> _m)
      : y0(_y0), y1(_y1), z0(_z0), z1(_z1), k(_k), mat(_m),
        bbox(point3(k-0.0001, y0, z0), point3(k+0.0001, y1, z1))
    {}

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
        auto t = (k-r.origin().x()) / r.direction().x();
        if (!ray_t.contains(t))
            return false;

        auto y = r.origin().y() + t*r.direction().y();
        auto z = r.origin().z() + t*r.direction().z();
        if (y < y0 || y1 < y || z < z0 || z1 < z)
            return false;

        rec.u = (y-y0)/(y1-y0);
        rec.v = (z-z0)/(z1-z0);
        rec.t = t;
        auto outward_normal = vec3(1, 0, 0);
        rec.set_face_normal(r, outward_normal);
        rec.mat = mat;
        rec.p = r.at(t);

        return true;
    }

    aabb bounding_box() const override { return bbox; }

  public:
    double y0, y1, z0, z1, k;
    shared_ptr<material> mat;
    aabb bbox;
};


#endif
