#ifndef CAMERAH
#define CAMERAH
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

#include "ray.h"


class camera {
    public:
        camera() {
            lower_left_corner = vec3(-2.0, -1.0, -1.0);
            horizontal = vec3(4.0, 0.0, 0.0);
            vertical = vec3(0.0, 2.0, 0.0);
            /*
            lower_left_corner = vec3(-.1, -0.05, -1.0);
            horizontal = vec3(0.2, 0.0, 0.0);
            vertical = vec3(0.0, 0.1, 0.0);
            */
            origin = vec3(0.0, 0.0, 0.0);
        }

        camera(vec3 lookfrom,  vec3 lookat, vec3 view_up,  float aspect,  float vfov,  float aperture, float distance_to_focus) {
            origin = lookfrom;
            w = unit_vector(lookfrom - lookat;
            u = unit_vector(cross(vup, w));
            v = cross(w, u);
            ZZ
        }
        ray get_ray(float s, float t) { return ray(origin, lower_left_corner + s*horizontal + t*vertical - origin); }

        vec3 origin;
        vec3 lower_left_corner;
        vec3 horizontal;
        vec3 vertical;
        vec3 u, v, w;
        float radius;
};

#endif

