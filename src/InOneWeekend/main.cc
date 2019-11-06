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
#include "camera.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"

#include <iostream>

using std::shared_ptr;
using std::make_shared;


vec3 ray_color(const ray& r, const hittable_list &world, int depth) {
    hit_record rec;
    if (world.hit(r, 0.001, infinity, rec)) {
        if (depth <= 0)
            return vec3(0,0,0);
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


void create_random_scene(hittable_list& scene) {
    int n = 500;

    auto floor_sphere_center = vec3(0, -1000, 0);
    auto floor_sphere_material = make_shared<lambertian>(vec3(0.5, 0.5, 0.5));
    scene.add(make_shared<sphere>(floor_sphere_center, 1000, floor_sphere_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {

            auto choose_mat = random_double();
            vec3 center(a+0.9*random_double(),0.2,b+0.9*random_double());

            if ((center-vec3(4,0.2,0)).length() > 0.9) {
                auto radius = 0.2;
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = vec3(random_double() * random_double(),
                                       random_double() * random_double(),
                                       random_double() * random_double());
                    sphere_material = make_shared<lambertian>(albedo);
                }
                else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = vec3(0.5 + 0.5*random_double(),
                                       0.5 + 0.5*random_double(),
                                       0.5 + 0.5*random_double());
                    auto fuzz = 0.5 * random_double();
                    sphere_material = make_shared<metal>(albedo, fuzz);
                }
                else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                }
                scene.add(make_shared<sphere>(center, radius, sphere_material));
            }
        }
    }

    scene.add(make_shared<sphere>(vec3( 0,1,0), 1., make_shared<dielectric>(1.5)));
    scene.add(make_shared<sphere>(vec3(-4,1,0), 1., make_shared<lambertian>(vec3(.4,.2,.1))));
    scene.add(make_shared<sphere>(vec3( 4,1,0), 1., make_shared<metal>(vec3(.7,.6,.5), 0.)));
}


int main() {
    int nx = 1200;
    int ny = 800;
    int num_samples = 10;
    int max_depth = 50;

    std::cout << "P3\n" << nx << ' ' << ny << "\n255\n";

    hittable_list scene;
    create_random_scene(scene);

    vec3 lookfrom(13,2,3);
    vec3 lookat(0,0,0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.1;

    camera cam(lookfrom, lookat, vec3(0,1,0), 20, double(nx)/ny, aperture, dist_to_focus);

    for (int j = ny-1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            vec3 color;
            for (int s = 0; s < num_samples; s++) {
                auto u = double(i + random_double()) / double(nx);
                auto v = double(j + random_double()) / double(ny);
                ray r = cam.get_ray(u, v);
                color += ray_color(r, scene, max_depth);
            }
            color.write_color(std::cout, num_samples);
        }
    }
}
