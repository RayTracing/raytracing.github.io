#ifndef QUAD_H
#define QUAD_H
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
#include "hittable_list.h"

#include <cmath>

class quad : public hittable {
  public:
    quad(const point3& _corner, const vec3& _sideA, const vec3& _sideB, shared_ptr<material> m)
      : corner(_corner), side_A(_sideA), side_B(_sideB), mat(m)
    {
        auto n = cross(side_A, side_B);
        normal = unit_vector(n);
        D = -dot(normal, corner);
        w = n / dot(n,n);

        area = n.length();

        set_bounding_box();
    }

    virtual void set_bounding_box() {
        bbox = aabb(corner, corner + side_A + side_B).pad();
    }

    aabb bounding_box() const override { return bbox; }

    virtual bool hit_ab(double a, double b, hit_record& rec) const {
        // Given the hit point in plane coordinates, return false if it is outside the
        // primitive, otherwise set the hit record UV coordinates and return true.

        if ((a < 0) || (1 < a) || (b < 0) || (1 < b))
            return false;

        rec.u = a;
        rec.v = b;
        return true;
    }

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
        auto denom = dot(normal, r.direction());

        // No hit if the ray is parallel to the plane.
        if (fabs(denom) < 1e-8)
            return false;

        // Return false if the hit point parameter t is outside the ray interval.
        auto t = (-D - dot(normal, r.origin())) / denom;
        if (!ray_t.contains(t))
            return false;

        // Determine the hit point lies within the planar shape using its plane coordinates.
        auto intersection = r.at(t);
        vec3 planar_hitpt_vector = intersection - corner;
        auto a = dot(w, cross(planar_hitpt_vector, side_B));
        auto b = dot(w, cross(side_A, planar_hitpt_vector));

        if (!hit_ab(a, b, rec))
            return false;

        // Ray hits the 2D shape; set the rest of the hit record and return true.
        rec.t = t;
        rec.p = intersection;
        rec.mat = mat;
        rec.set_face_normal(r, normal);

        return true;
    }

    double pdf_value(const point3& origin, const vec3& v) const override {
        hit_record rec;
        if (!this->hit(ray(origin, v), interval(0.001, infinity), rec))
            return 0;

        auto distance_squared = rec.t * rec.t * v.length_squared();
        auto cosine = fabs(dot(v, rec.normal) / v.length());

        return distance_squared / (cosine * area);
    }

    vec3 random(const point3& origin) const override {
        auto p = plane_origin + (random_double() * axis_A) + (random_double() * axis_B);
        return p - origin;
    }

  protected:
    point3 corner;
    vec3 side_A, side_B;
    shared_ptr<material> mat;
    vec3 normal;
    double D;
    vec3 w;
    double area;
    aabb bbox;
};


#endif
