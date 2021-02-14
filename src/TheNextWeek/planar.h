#ifndef PLANAR_H
#define PLANAR_H
//==============================================================================================
// To the extent possible under law, the author(s) have dedicated all copyright and related and
// neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy (see file COPYING.txt) of the CC0 Public Domain Dedication
// along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
//==============================================================================================

#include "rtweekend.h"

#include "hittable.h"

#include <cmath>

class quad : public hittable {
  public:
    quad(const point3& o, const vec3& side_A, const vec3& side_B, shared_ptr<material> m)
      : plane_origin(o), a(side_A), b(side_B), mat(m)
    {
        normal = unit_vector(cross(a, b));
        D = -dot(normal, plane_origin);
        a /= dot(a,a);
        b /= dot(b,b);

/////// By default, bounded to the world coordinates of UV<0,0> to UV<1,1>.
/////// Might make this invariant.

        interval u_bounds, v_bounds;
        get_uv_bounds(u_bounds, v_bounds);
        bbox = aabb(
            plane_origin + (u_bounds.min * side_A) + (v_bounds.min * side_B),
            plane_origin + (u_bounds.max * side_A) + (v_bounds.max * side_B)
        );
    }

    virtual void get_uv_bounds(interval& u_bounds, interval& v_bounds) {
        u_bounds = interval(0,1);
        v_bounds = interval(0,1);
    }

    virtual bool hit_uv(double u, double v) const {
        return (0 <= u) && (u <= 1) && (0 <= v) && (v <= 1);
    }

/// This method calls `hit_uv()` to filter on UV coordinates.

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
        auto denom = dot(normal, r.direction());

        // No hit if the ray is parallel to the plane.
        if (fabs(denom) < 1e-8)
            return false;

        auto t = (-D - dot(normal, r.origin())) / denom;
        if (!ray_t.contains(t))
            return false;

        auto intersection = r.at(t);

        vec3 planar_hitpt_vector = intersection - plane_origin;

        auto u = dot(planar_hitpt_vector, a);
        auto v = dot(planar_hitpt_vector, b);
        if (!hit_uv(u,v))
            return false;

        rec.t = t;
        rec.p = intersection;
        rec.u = u;
        rec.v = v;
        rec.mat = mat;
        rec.set_face_normal(r, normal);

        return true;
    }

    aabb bounding_box() const override { return bbox; }

  protected:
    point3 plane_origin;
    vec3 normal;
    double D;
    vec3 a, b;
    shared_ptr<material> mat;
    aabb bbox;
};


class tri : public quad {
  public:
    tri(const point3& o, const vec3& side_A, const vec3& side_B, shared_ptr<material> m)
      : quad(o, side_A, side_B, m)
    {}

    bool hit_uv(double u, double v) const override {
        return u > 0
            && v > 0
            && u + v <= 1;
    }
};


class ellipse : public quad {
  public:
    ellipse(
        const point3& center, const vec3& radius_A, const vec3& radius_B,
        shared_ptr<material> m)
      : quad(center - radius_A - radius_B, 2 * radius_A, 2 * radius_B, m)
    { }

    bool hit_uv(double u, double v) const override {
        auto px = 2 * (u - 0.5);
        auto py = 2 * (v - 0.5);
        return (px*px + py*py) <= 1;
    }
};


class annulus : public quad {
  public:
    annulus(
        const point3& center, const vec3& side_A, const vec3& side_B,
        double radius_inner, double radius_outer, shared_ptr<material> m)
      : quad(
            center - radius_outer*unit_vector(side_A) - radius_outer*unit_vector(side_B),
            2 * radius_outer * unit_vector(side_A),
            2 * radius_outer * unit_vector(side_B),
            m
        ),
        inner(radius_inner/radius_outer)
    {}

    bool hit_uv(double u, double v) const override {
        auto px = 2 * (u - 0.5);
        auto py = 2 * (v - 0.5);
        auto radius = px*px + py*py;
        return interval(inner*inner, 1.0).contains(radius);
    }

  private:
    double inner;
};


#endif
