#ifndef CAMERA_H
#define CAMERA_H
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


class camera {
  public:
    void initialize(double image_width, double image_height) {
        auto aspect_ratio = image_width / image_height;
        auto theta = degrees_to_radians(vfov);
        auto h = tan(theta/2);
        auto viewport_height = 2.0 * h;
        auto viewport_width = aspect_ratio * viewport_height;

        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup, w));
        v = cross(w, u);

        origin = lookfrom;
        horizontal = focus_dist * viewport_width * u;
        vertical = focus_dist * viewport_height * v;
        lower_left_corner = origin - horizontal/2 - vertical/2 - focus_dist*w;

        lens_radius = aperture / 2;

        jitter_x = 0.0 / image_width;
        jitter_y = 0.0 / image_height;
    }

    ray get_ray(double s, double t) const {
        // Return the ray from the projection point to the indicated pixel. Coordinates s,t are
        // the normalized image-based coordinates of the pixel. Image left is s=0, image right
        // is s=1, image top is t=0, image bottom is t=1.

        // Jitter the sample location of the pixel.
        s += random_double(-1.0, 1.0) * jitter_x;
        t += random_double(-1.0, 1.0) * jitter_y;

        vec3 rd = lens_radius * random_in_unit_disk();
        vec3 offset = u * rd.x() + v * rd.y();

        const auto ray_time = random_double(0.0, 1.0);

        return ray(
            origin + offset,
            lower_left_corner + s*horizontal + (1-t)*vertical - origin - offset,
            ray_time
        );
    }

  public:
    double vfov       = 40;
    double aperture   = 0;
    double focus_dist = 10;

    point3 lookfrom = point3(0,0,-1);
    point3 lookat   = point3(0,0,0);
    vec3   vup      = vec3(0,1,0);

  private:
    point3 origin;
    point3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 u, v, w;
    double lens_radius;
    double jitter_x, jitter_y; // Max extent of pixel jitter
};

#endif
