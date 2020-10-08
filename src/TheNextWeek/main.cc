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

#include "box.h"
#include "bvh.h"
#include "camera.h"
#include "color.h"
#include "constant_medium.h"
#include "hittable_list.h"
#include "material.h"
#include "moving_sphere.h"
#include "sphere.h"
#include "texture.h"

#include <iostream>


color ray_color(const ray& r, const color& background, const hittable& world, int depth) {
    hit_record rec;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return color(0,0,0);

    // If the ray hits nothing, return the background color.
    if (!world.hit(r, 0.001, infinity, rec))
        return background;

    ray scattered;
    color attenuation;
    color emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);

    if (!rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        return emitted;

    return emitted + attenuation * ray_color(scattered, background, world, depth-1);
}


struct scene_description {
    color         background;
    int           image_width;
    double        aspect_ratio;
    int           sample_count;
    camera        cam;
    hittable_list world;
};


scene_description random_scene() {
    scene_description scene;
    scene.background   = color(0.70, 0.80, 1.00);
    scene.image_width  = 400;
    scene.aspect_ratio = 16.0 / 9.0;
    scene.sample_count = 100;
    scene.cam.aperture = 0.1;
    scene.cam.vfov     = 20.0;
    scene.cam.lookfrom = point3(13,2,3);
    scene.cam.lookat   = point3(0,0,0);

    hittable_list world;

    auto checker = make_shared<checker_texture>(color(0.2, 0.3, 0.1), color(0.9, 0.9, 0.9));

    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, make_shared<lambertian>(checker)));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - vec3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = make_shared<lambertian>(albedo);
                    auto center2 = center + vec3(0, random_double(0,.5), 0);
                    world.add(make_shared<moving_sphere>(
                        center, center2, 0.0, 1.0, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

    scene.world = hittable_list(make_shared<bvh_node>(world, 0.0, 1.0));

    return scene;
}


scene_description two_spheres() {
    scene_description scene;
    scene.background   = color(0.70, 0.80, 1.00);
    scene.image_width  = 400;
    scene.aspect_ratio = 16.0 / 9.0;
    scene.sample_count = 100;
    scene.cam.aperture = 0.0;
    scene.cam.vfov     = 20.0;
    scene.cam.lookfrom = point3(13,2,3);
    scene.cam.lookat   = point3(0,0,0);

    hittable_list& world = scene.world;

    auto checker = make_shared<checker_texture>(color(0.2, 0.3, 0.1), color(0.9, 0.9, 0.9));

    world.add(make_shared<sphere>(point3(0,-10, 0), 10, make_shared<lambertian>(checker)));
    world.add(make_shared<sphere>(point3(0, 10, 0), 10, make_shared<lambertian>(checker)));

    return scene;
}


scene_description two_perlin_spheres() {
    scene_description scene;
    scene.background   = color(0.70, 0.80, 1.00);
    scene.image_width  = 400;
    scene.aspect_ratio = 16.0 / 9.0;
    scene.sample_count = 100;
    scene.cam.aperture = 0.0;
    scene.cam.vfov     = 20.0;
    scene.cam.lookfrom = point3(13,2,3);
    scene.cam.lookat   = point3(0,0,0);

    hittable_list& world = scene.world;

    auto pertext = make_shared<noise_texture>(4);
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, make_shared<lambertian>(pertext)));
    world.add(make_shared<sphere>(point3(0,2,0), 2, make_shared<lambertian>(pertext)));

    return scene;
}


scene_description earth() {
    scene_description scene;
    scene.background   = color(0.70, 0.80, 1.00);
    scene.image_width  = 400;
    scene.aspect_ratio = 16.0 / 9.0;
    scene.sample_count = 100;
    scene.cam.aperture = 0.0;
    scene.cam.vfov     = 20.0;
    scene.cam.lookfrom = point3(0,0,12);
    scene.cam.lookat   = point3(0,0,0);

    auto earth_texture = make_shared<image_texture>("earthmap.jpg");
    auto earth_surface = make_shared<lambertian>(earth_texture);
    auto globe = make_shared<sphere>(point3(0,0,0), 2, earth_surface);

    scene.world = hittable_list(globe);

    return scene;
}


scene_description simple_light() {
    scene_description scene;
    scene.background   = color(0,0,0);
    scene.image_width  = 400;
    scene.aspect_ratio = 16.0 / 9.0;
    scene.sample_count = 100;
    scene.cam.aperture = 0.0;
    scene.cam.vfov     = 20.0;
    scene.cam.lookfrom = point3(26,3,6);
    scene.cam.lookat   = point3(0,2,0);

    hittable_list& world = scene.world;

    auto pertext = make_shared<noise_texture>(4);
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, make_shared<lambertian>(pertext)));
    world.add(make_shared<sphere>(point3(0,2,0), 2, make_shared<lambertian>(pertext)));

    auto difflight = make_shared<diffuse_light>(color(4,4,4));
    world.add(make_shared<sphere>(point3(0,7,0), 2, difflight));
    world.add(make_shared<xy_rect>(3, 5, 1, 3, -2, difflight));

    return scene;
}


scene_description cornell_box() {
    scene_description scene;
    scene.background   = color(0,0,0);
    scene.image_width  = 600;
    scene.aspect_ratio = 1.0;
    scene.sample_count = 200;
    scene.cam.aperture = 0.0;
    scene.cam.vfov     = 40.0;
    scene.cam.lookfrom = point3(278, 278, -800);
    scene.cam.lookat   = point3(278, 278, 0);

    hittable_list& world = scene.world;

    auto red   = make_shared<lambertian>(color(.65, .05, .05));
    auto white = make_shared<lambertian>(color(.73, .73, .73));
    auto green = make_shared<lambertian>(color(.12, .45, .15));
    auto light = make_shared<diffuse_light>(color(15,15,15));

    world.add(make_shared<yz_rect>(0, 555, 0, 555, 555, green));
    world.add(make_shared<yz_rect>(0, 555, 0, 555, 0, red));
    world.add(make_shared<xz_rect>(213, 343, 227, 332, 554, light));
    world.add(make_shared<xz_rect>(0, 555, 0, 555, 555, white));
    world.add(make_shared<xz_rect>(0, 555, 0, 555, 0, white));
    world.add(make_shared<xy_rect>(0, 555, 0, 555, 555, white));

    shared_ptr<hittable> box1 = make_shared<box>(point3(0,0,0), point3(165,330,165), white);
    box1 = make_shared<rotate_y>(box1, 15);
    box1 = make_shared<translate>(box1, vec3(265,0,295));
    world.add(box1);

    shared_ptr<hittable> box2 = make_shared<box>(point3(0,0,0), point3(165,165,165), white);
    box2 = make_shared<rotate_y>(box2, -18);
    box2 = make_shared<translate>(box2, vec3(130,0,65));
    world.add(box2);

    return scene;
}


scene_description cornell_smoke() {
    scene_description scene;
    scene.background   = color(0,0,0);
    scene.image_width  = 600;
    scene.aspect_ratio = 1.0;
    scene.sample_count = 200;
    scene.cam.aperture = 0.0;
    scene.cam.vfov     = 40.0;
    scene.cam.lookfrom = point3(278, 278, -800);
    scene.cam.lookat   = point3(278, 278, 0);

    hittable_list& world = scene.world;

    auto red   = make_shared<lambertian>(color(.65, .05, .05));
    auto white = make_shared<lambertian>(color(.73, .73, .73));
    auto green = make_shared<lambertian>(color(.12, .45, .15));
    auto light = make_shared<diffuse_light>(color(7, 7, 7));

    world.add(make_shared<yz_rect>(0, 555, 0, 555, 555, green));
    world.add(make_shared<yz_rect>(0, 555, 0, 555, 0, red));
    world.add(make_shared<xz_rect>(113, 443, 127, 432, 554, light));
    world.add(make_shared<xz_rect>(0, 555, 0, 555, 555, white));
    world.add(make_shared<xz_rect>(0, 555, 0, 555, 0, white));
    world.add(make_shared<xy_rect>(0, 555, 0, 555, 555, white));

    shared_ptr<hittable> box1 = make_shared<box>(point3(0,0,0), point3(165,330,165), white);
    box1 = make_shared<rotate_y>(box1, 15);
    box1 = make_shared<translate>(box1, vec3(265,0,295));

    shared_ptr<hittable> box2 = make_shared<box>(point3(0,0,0), point3(165,165,165), white);
    box2 = make_shared<rotate_y>(box2, -18);
    box2 = make_shared<translate>(box2, vec3(130,0,65));

    world.add(make_shared<constant_medium>(box1, 0.01, color(0,0,0)));
    world.add(make_shared<constant_medium>(box2, 0.01, color(1,1,1)));

    return scene;
}


scene_description final_scene() {
    scene_description scene;
    scene.background   = color(0,0,0);
    scene.image_width  = 800;
    scene.aspect_ratio = 1.0;
    scene.sample_count = 10000;
    scene.cam.aperture = 0.0;
    scene.cam.vfov     = 40.0;
    scene.cam.lookfrom = point3(478, 278, -600);
    scene.cam.lookat   = point3(278, 278, 0);

    hittable_list boxes1;
    auto ground = make_shared<lambertian>(color(0.48, 0.83, 0.53));

    const int boxes_per_side = 20;
    for (int i = 0; i < boxes_per_side; i++) {
        for (int j = 0; j < boxes_per_side; j++) {
            auto w = 100.0;
            auto x0 = -1000.0 + i*w;
            auto z0 = -1000.0 + j*w;
            auto y0 = 0.0;
            auto x1 = x0 + w;
            auto y1 = random_double(1,101);
            auto z1 = z0 + w;

            boxes1.add(make_shared<box>(point3(x0,y0,z0), point3(x1,y1,z1), ground));
        }
    }

    hittable_list& world = scene.world;

    world.add(make_shared<bvh_node>(boxes1, 0, 1));

    auto light = make_shared<diffuse_light>(color(7, 7, 7));
    world.add(make_shared<xz_rect>(123, 423, 147, 412, 554, light));

    auto center1 = point3(400, 400, 200);
    auto center2 = center1 + vec3(30,0,0);
    auto moving_sphere_material = make_shared<lambertian>(color(0.7, 0.3, 0.1));
    world.add(make_shared<moving_sphere>(center1, center2, 0, 1, 50, moving_sphere_material));

    world.add(make_shared<sphere>(point3(260, 150, 45), 50, make_shared<dielectric>(1.5)));
    world.add(make_shared<sphere>(
        point3(0, 150, 145), 50, make_shared<metal>(color(0.8, 0.8, 0.9), 1.0)
    ));

    auto boundary = make_shared<sphere>(point3(360,150,145), 70, make_shared<dielectric>(1.5));
    world.add(boundary);
    world.add(make_shared<constant_medium>(boundary, 0.2, color(0.2, 0.4, 0.9)));
    boundary = make_shared<sphere>(point3(0,0,0), 5000, make_shared<dielectric>(1.5));
    world.add(make_shared<constant_medium>(boundary, .0001, color(1,1,1)));

    auto emat = make_shared<lambertian>(make_shared<image_texture>("earthmap.jpg"));
    world.add(make_shared<sphere>(point3(400,200,400), 100, emat));
    auto pertext = make_shared<noise_texture>(0.1);
    world.add(make_shared<sphere>(point3(220,280,300), 80, make_shared<lambertian>(pertext)));

    hittable_list boxes2;
    auto white = make_shared<lambertian>(color(.73, .73, .73));
    int ns = 1000;
    for (int j = 0; j < ns; j++) {
        boxes2.add(make_shared<sphere>(point3::random(0,165), 10, white));
    }

    world.add(make_shared<translate>(
        make_shared<rotate_y>(
            make_shared<bvh_node>(boxes2, 0.0, 1.0), 15),
            vec3(-100,270,395)
        )
    );

    return scene;
}


scene_description default_scene() {
    auto scene = final_scene();
    scene.image_width  = 400;
    scene.sample_count = 100;

    return scene;
}


int main() {

    // World

    scene_description scene;
    scene.cam.vup = vec3(0,1,0);
    scene.cam.focus_dist = 10.0;
    scene.cam.time0 = 0;
    scene.cam.time1 = 1;

    switch (0) {
        case 1:  scene = random_scene();       break;
        case 2:  scene = two_spheres();        break;
        case 3:  scene = two_perlin_spheres(); break;
        case 4:  scene = earth();              break;
        case 5:  scene = simple_light();       break;
        case 6:  scene = cornell_box();        break;
        case 7:  scene = cornell_smoke();      break;
        case 8:  scene = final_scene();        break;
        default: scene = default_scene();      break;
    }

    // Camera

    scene.cam.initialize();
    const int image_width  = scene.image_width;
    const int image_height = static_cast<int>(image_width / scene.aspect_ratio);

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    const int max_depth = 50;

    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            color pixel_color(0,0,0);
            for (int s = 0; s < scene.sample_count; ++s) {
                auto u = (i + random_double()) / (image_width-1);
                auto v = (j + random_double()) / (image_height-1);
                ray r = scene.cam.get_ray(u, v);
                pixel_color += ray_color(r, scene.background, scene.world, max_depth);
            }
            write_color(std::cout, pixel_color, scene.sample_count);
        }
    }

    std::cerr << "\nDone.\n";
}
