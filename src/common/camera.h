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
    void initialize() {
        auto theta = degrees_to_radians(vfov);
        auto h = tan(theta/2);
        auto viewport_height = 2.0 * h;

        // Calculate the actual aspect ratio of the integer image width and height.
        auto actual_aspect_ratio = static_cast<double>(image_width) / get_image_height();
        auto viewport_width = actual_aspect_ratio * viewport_height;

        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup, w));
        v = cross(w, u);

        origin = lookfrom;
        horizontal = focus_dist * viewport_width * u;
        vertical = focus_dist * viewport_height * v;
        lower_left_corner = origin - horizontal/2 - vertical/2 - focus_dist*w;

        defocus_radius = defocus_diameter / 2;
    }

    ray get_ray(double s, double t) const {
        // Return the ray from the projection point to the indicated pixel. Coordinates s,t are
        // the normalized image-based coordinates of the pixel. Image left is s=0, image right
        // is s=1, image top is t=0, image bottom is t=1.

        vec3 rd = defocus_radius * random_in_unit_disk();
        vec3 offset = u * rd.x() + v * rd.y();
        const auto ray_time = random_double(0.0, 1.0);

        return ray(
            origin + offset,
            lower_left_corner + s*horizontal + (1-t)*vertical - origin - offset,
            ray_time
        );
    }

    int get_image_height() const {
        return static_cast<int>(image_width / aspect_ratio);
    }

  public:
    point3 lookfrom = point3(0,0,-1);
    point3 lookat   = point3(0,0,0);
    vec3   vup      = vec3(0,1,0);
    double vfov     = 40;  // Vertical field of view

    double aspect_ratio = 1.0;  // Ideal real-valued aspect ratio
    int    image_width  = 100;

    double defocus_diameter = 0;  // Diameter of defocus disk around projection point
    double focus_dist = 10;       // Distance at which objects are in perfect focus

  private:
    point3 origin;
    point3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 u, v, w;            // Camera unit basis vectors
    double defocus_radius;   // Radius of defocus disk around projection point
};

#endif
