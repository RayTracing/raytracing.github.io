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

#include "aarect.h"
#include "box.h"
#include "camera.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"

#include <iostream>


vec3 ray_color(
    const ray& r,
    const vec3& background,
    const hittable& world,
    shared_ptr<hittable> lights,
    int depth
) {
    hit_record rec;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return vec3(0,0,0);

    // If the ray hits nothing, return the background color.
    if (!world.hit(r, 0.001, infinity, rec))
        return background;

    scatter_record srec;
    vec3 emitted = rec.mat_ptr->emitted(r, rec, rec.u, rec.v, rec.p);

    if (!rec.mat_ptr->scatter(r, rec, srec))
        return emitted;

    if (srec.is_specular) {
        return srec.attenuation
             * ray_color(srec.specular_ray, background, world, lights, depth-1);
    }

    auto light_ptr = make_shared<hittable_pdf>(lights, rec.p);
    mixture_pdf p(light_ptr, srec.pdf_ptr);
    ray scattered = ray(rec.p, p.generate(), r.time());
    auto pdf_val = p.value(scattered.direction());

    return emitted
         + srec.attenuation * rec.mat_ptr->scattering_pdf(r, rec, scattered)
                            * ray_color(scattered, background, world, lights, depth-1)
                            / pdf_val;
}


hittable_list cornell_box(camera& cam, double aspect) {
    hittable_list world;

    auto red = make_shared<lambertian>(make_shared<constant_texture>(vec3(0.65, 0.05, 0.05)));
    auto white = make_shared<lambertian>(make_shared<constant_texture>(vec3(0.73, 0.73, 0.73)));
    auto green = make_shared<lambertian>(make_shared<constant_texture>(vec3(0.12, 0.45, 0.15)));
    auto light = make_shared<diffuse_light>(make_shared<constant_texture>(vec3(15, 15, 15)));

    world.add(make_shared<flip_face>(make_shared<yz_rect>(0, 555, 0, 555, 555, green)));
    world.add(make_shared<yz_rect>(0, 555, 0, 555, 0, red));
    world.add(make_shared<flip_face>(make_shared<xz_rect>(213, 343, 227, 332, 554, light)));
    world.add(make_shared<flip_face>(make_shared<xz_rect>(0, 555, 0, 555, 555, white)));
    world.add(make_shared<xz_rect>(0, 555, 0, 555, 0, white));
    world.add(make_shared<flip_face>(make_shared<xy_rect>(0, 555, 0, 555, 555, white)));

    shared_ptr<hittable> box1 = make_shared<box>(vec3(0,0,0), vec3(165,330,165), white);
    box1 = make_shared<rotate_y>(box1, 15);
    box1 = make_shared<translate>(box1, vec3(265,0,295));
    world.add(box1);

    auto glass = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(vec3(190,90,190), 90 , glass));

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
    const int image_width = 600;
    const int image_height = 600;
    const int samples_per_pixel = 100;
    const int max_depth = 50;
    const auto aspect_ratio = double(image_width) / image_height;

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    vec3 background(0,0,0);

    camera cam;
    auto world = cornell_box(cam, aspect_ratio);

    auto lights = make_shared<hittable_list>();
    lights->add(make_shared<xz_rect>(213, 343, 227, 332, 554, shared_ptr<material>()));
    lights->add(make_shared<sphere>(vec3(190, 90, 190), 90, shared_ptr<material>()));

    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            vec3 color;
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (i + random_double()) / image_width;
                auto v = (j + random_double()) / image_height;
                ray r = cam.get_ray(u, v);
                color += ray_color(r, background, world, lights, max_depth);
            }
            color.write_color(std::cout, samples_per_pixel);
        }
    }

    std::cerr << "\nDone.\n";
}
