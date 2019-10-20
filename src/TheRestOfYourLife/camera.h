#ifndef CAMERA_H
#define CAMERA_H
//==================================================================================================
// Written in 2016 by Peter Shirley <ptrshrl@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related and
// neighboring rights to this software to the public domain worldwide. This software is distributed
// without any warranty.
//
// You should have received a copy (see file COPYING.txt) of the CC0 Public Domain Dedication along
// with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
//==================================================================================================

#include "common/rtweekend.h"
#include "random.h"
#include "ray.h"


vec3 random_in_unit_disk() {
    vec3 p;
    do {
        p = 2.0*vec3(random_double(),random_double(),0) - vec3(1,1,0);
    } while (dot(p,p) >= 1.0);
    return p;
}

class camera {
    public:
        // new:  add t0 and t1
        camera(vec3 lookfrom, vec3 lookat, vec3 vup, double vfov, double aspect, double aperture, double focus_dist, double t0, double t1) { // vfov is top to bottom in degrees
            time0 = t0;
            time1 = t1;
            lens_radius = aperture / 2;
            auto theta = vfov*pi/180;
            auto half_height = tan(theta/2);
            auto half_width = aspect * half_height;
            origin = lookfrom;
            w = unit_vector(lookfrom - lookat);
            u = unit_vector(cross(vup, w));
            v = cross(w, u);
            lower_left_corner = origin  - half_width*focus_dist*u -half_height*focus_dist*v - focus_dist*w;
            horizontal = 2*half_width*focus_dist*u;
            vertical = 2*half_height*focus_dist*v;
        }

        // new: add time to construct ray
        ray get_ray(double s, double t) {
            vec3 rd = lens_radius*random_in_unit_disk();
            vec3 offset = u * rd.x() + v * rd.y();
            auto time = time0 + random_double()*(time1-time0);
            return ray(origin + offset, lower_left_corner + s*horizontal + t*vertical - origin - offset, time);
        }

        vec3 origin;
        vec3 lower_left_corner;
        vec3 horizontal;
        vec3 vertical;
        vec3 u, v, w;
        double time0, time1;  // new variables for shutter open/close times
        double lens_radius;
};

#endif
