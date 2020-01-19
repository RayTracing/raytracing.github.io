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
#include "aarect.h"
#include "box.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
#include <iostream>


vec3 ray_color(const ray& r, hittable& world, hittable& light_shape, int depth) {
    hit_record rec;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return vec3(0,0,0);

    // If the ray hits nothing, return the background color.
    if (!world.hit(r, 0.001, infinity, rec))
        return vec3(0,1,1);

    scatter_record srec;
    vec3 emitted = rec.mat_ptr->emitted(r, rec, rec.u, rec.v, rec.p);

    if (!rec.mat_ptr->scatter(r, rec, srec))
        return emitted;

    if (srec.is_specular) {
        return srec.attenuation * ray_color(srec.specular_ray, world, light_shape, depth-1);
    }

    hittable_pdf plight(&light_shape, rec.p);
    mixture_pdf p(&plight, srec.pdf_ptr);
    ray scattered = ray(rec.p, p.generate(), r.time());
    auto pdf_val = p.value(scattered.direction());
    delete srec.pdf_ptr;

    return emitted
         + srec.attenuation * rec.mat_ptr->scattering_pdf(r, rec, scattered)
                            * ray_color(scattered, world, light_shape, depth-1)
                            / pdf_val;
}


hittable_list cornell_box(camera& cam, double aspect) {
    hittable_list world;

    auto red = new lambertian(new constant_texture(vec3(0.65, 0.05, 0.05)));
    auto white = new lambertian(new constant_texture(vec3(0.73, 0.73, 0.73)));
    auto green = new lambertian(new constant_texture(vec3(0.12, 0.45, 0.15)));
    auto light = new diffuse_light(new constant_texture(vec3(15, 15, 15)));

    world.add(new flip_face(new yz_rect(0, 555, 0, 555, 555, green)));
    world.add(new yz_rect(0, 555, 0, 555, 0, red));
    world.add(new flip_face(new xz_rect(213, 343, 227, 332, 554, light)));
    world.add(new flip_face(new xz_rect(0, 555, 0, 555, 555, white)));
    world.add(new xz_rect(0, 555, 0, 555, 0, white));
    world.add(new flip_face(new xy_rect(0, 555, 0, 555, 555, white)));

    hittable* box1 = new box(vec3(0,0,0), vec3(165,330,165), white);
    box1 = new rotate_y(box1, 15);
    box1 = new translate(box1, vec3(265,0,295));
    world.add(box1);

    material *glass = new dielectric(1.5);
    world.add(new sphere(vec3(190,90,190), 90 , glass));

    vec3 lookfrom(278, 278, -800);
    vec3 lookat(278, 278, 0);
    vec3 up(0, 1, 0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.0;
    auto vfov = 40.0;
    auto t0 = 0.0;
    auto t1 = 1.0;

    cam = camera(lookfrom, lookat, up, vfov, aspect, aperture, dist_to_focus, t0, t1);

    return world;
}


int main() {
    int nx = 600;
    int ny = 600;
    int num_samples = 100;
    int max_depth = 50;

    std::cout << "P3\n" << nx << ' ' << ny << "\n255\n";

    camera cam;
    auto aspect = double(ny) / double(nx);

    auto world = cornell_box(cam, aspect);

    hittable_list lights;
    lights.add(new xz_rect(213, 343, 227, 332, 554, 0));
    lights.add(new sphere(vec3(190, 90, 190), 90, 0));

    for (int j = ny-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < nx; ++i) {
            vec3 color;
            for (int s = 0; s < num_samples; ++s) {
                auto u = (i + random_double()) / nx;
                auto v = (j + random_double()) / ny;
                ray r = cam.get_ray(u, v);
                color += ray_color(r, world, lights, max_depth);
            }
            color.write_color(std::cout, num_samples);
        }
    }

    std::cerr << "\nDone.\n";
}
