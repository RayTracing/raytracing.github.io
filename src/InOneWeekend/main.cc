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

#include "common/rtweekend.h"
#include "common/camera.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
#include <iostream>


vec3 ray_color(const ray& r, hittable& world, int depth) {
    hit_record rec;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return vec3(0,0,0);

    if (world.hit(r, 0.001, infinity, rec)) {
        ray scattered;
        vec3 attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth-1);
        return vec3(0,0,0);
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
}


hittable_list random_scene() {
    hittable_list objects;

    objects.add(
        make_shared<sphere>(vec3(0,-1000,0), 1000, make_shared<lambertian>(vec3(0.5, 0.5, 0.5)))
    );

    int i = 1;
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            vec3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());
            if ((center - vec3(4, 0.2, 0)).length() > 0.9) {
                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = vec3::random() * vec3::random();
                    objects.add(
                        make_shared<sphere>(center, 0.2, make_shared<lambertian>(albedo)));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = vec3::random(.5, 1);
                    auto fuzz = random_double(0, .5);
                    objects.add(
                        make_shared<sphere>(center, 0.2, make_shared<metal>(albedo, fuzz)));
                } else {
                    // glass
                    objects.add(make_shared<sphere>(center, 0.2, make_shared<dielectric>(1.5)));
                }
            }
        }
    }

    objects.add(
        make_shared<sphere>(vec3(0, 1, 0), 1.0, make_shared<dielectric>(1.5)));
    objects.add(
        make_shared<sphere>(vec3(-4, 1, 0), 1.0, make_shared<lambertian>(vec3(0.4, 0.2, 0.1))));
    objects.add(
        make_shared<sphere>(vec3(4, 1, 0), 1.0, make_shared<metal>(vec3(0.7, 0.6, 0.5), 0.0)));

    return objects;
}


int main() {
    int nx = 1200;
    int ny = 800;
    int num_samples = 10;
    int max_depth = 50;

    std::cout << "P3\n" << nx << ' ' << ny << "\n255\n";

    auto world = random_scene();

    vec3 lookfrom(13,2,3);
    vec3 lookat(0,0,0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.1;

    camera cam(lookfrom, lookat, vec3(0,1,0), 20, double(nx)/ny, aperture, dist_to_focus);

    for (int j = ny-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < nx; ++i) {
            vec3 color;
            for (int s = 0; s < num_samples; ++s) {
                auto u = double(i + random_double()) / double(nx);
                auto v = double(j + random_double()) / double(ny);
                ray r = cam.get_ray(u, v);
                color += ray_color(r, world, max_depth);
            }
            color.write_color(std::cout, num_samples);
        }
    }

    std::cerr << "\nDone.\n";
}
