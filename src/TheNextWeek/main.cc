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

#include "bvh.h"
#include "camera.h"
#include "color.h"
#include "constant_medium.h"
#include "hittable_list.h"
#include "material.h"
#include "moving_sphere.h"
#include "quad.h"
#include "scene.h"
#include "sphere.h"
#include "texture.h"


void random_spheres(scene& scene_desc) {
    scene_desc.aspect_ratio      = 16.0 / 9.0;
    scene_desc.image_width       = 400;
    scene_desc.samples_per_pixel = 100;

    scene_desc.cam.lookfrom   = point3(13,2,3);
    scene_desc.cam.lookat     = point3(0,0,0);
    scene_desc.cam.vup        = vec3(0,1,0);
    scene_desc.cam.vfov       = 20.0;
    scene_desc.cam.aperture   = 0.1;
    scene_desc.cam.focus_dist = 10.0;

    hittable_list& world = scene_desc.world;

    auto checker = make_shared<checker_texture>(0.32, color(.2, .3, .1), color(.9, .9, .9));
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
                        center, center2, 0.2, sphere_material));
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

    scene_desc.world = hittable_list(make_shared<bvh_node>(world));
}


void two_spheres(scene& scene_desc) {
    scene_desc.image_width       = 400;
    scene_desc.aspect_ratio      = 16.0 / 9.0;
    scene_desc.samples_per_pixel = 100;

    scene_desc.cam.aperture = 0.0;
    scene_desc.cam.vfov     = 20.0;
    scene_desc.cam.lookfrom = point3(13,2,3);
    scene_desc.cam.lookat   = point3(0,0,0);

    hittable_list& world = scene_desc.world;

    auto checker = make_shared<checker_texture>(0.8, color(.2, .3, .1), color(.9, .9, .9));

    world.add(make_shared<sphere>(point3(0,-10, 0), 10, make_shared<lambertian>(checker)));
    world.add(make_shared<sphere>(point3(0, 10, 0), 10, make_shared<lambertian>(checker)));
}


void two_perlin_spheres(scene& scene_desc) {
    scene_desc.image_width       = 400;
    scene_desc.aspect_ratio      = 16.0 / 9.0;
    scene_desc.samples_per_pixel = 100;

    scene_desc.cam.aperture = 0.0;
    scene_desc.cam.vfov     = 20.0;
    scene_desc.cam.lookfrom = point3(13,2,3);
    scene_desc.cam.lookat   = point3(0,0,0);

    hittable_list& world = scene_desc.world;

    auto pertext = make_shared<noise_texture>(4);
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, make_shared<lambertian>(pertext)));
    world.add(make_shared<sphere>(point3(0,2,0), 2, make_shared<lambertian>(pertext)));
}


void earth(scene& scene_desc) {
    scene_desc.image_width       = 400;
    scene_desc.aspect_ratio      = 16.0 / 9.0;
    scene_desc.samples_per_pixel = 100;

    scene_desc.cam.aperture = 0.0;
    scene_desc.cam.vfov     = 20.0;
    scene_desc.cam.lookfrom = point3(0,0,12);
    scene_desc.cam.lookat   = point3(0,0,0);

    auto earth_texture = make_shared<image_texture>("earthmap.jpg");
    auto earth_surface = make_shared<lambertian>(earth_texture);
    auto globe = make_shared<sphere>(point3(0,0,0), 2, earth_surface);

    scene_desc.world = hittable_list(globe);
}


void simple_light(scene& scene_desc) {
    scene_desc.image_width       = 400;
    scene_desc.aspect_ratio      = 16.0 / 9.0;
    scene_desc.samples_per_pixel = 100;
    scene_desc.background        = color(0,0,0);

    scene_desc.cam.aperture = 0.0;
    scene_desc.cam.vfov     = 20.0;
    scene_desc.cam.lookfrom = point3(26,3,6);
    scene_desc.cam.lookat   = point3(0,2,0);

    hittable_list& world = scene_desc.world;

    auto pertext = make_shared<noise_texture>(4);
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, make_shared<lambertian>(pertext)));
    world.add(make_shared<sphere>(point3(0,2,0), 2, make_shared<lambertian>(pertext)));

    auto difflight = make_shared<diffuse_light>(color(4,4,4));
    world.add(make_shared<sphere>(point3(0,7,0), 2, difflight));
    world.add(make_shared<quad>(point3(3,1,-2), vec3(2,0,0), vec3(0,2,0), difflight));
}


void cornell_box(scene& scene_desc) {
    scene_desc.image_width       = 600;
    scene_desc.aspect_ratio      = 1.0;
    scene_desc.samples_per_pixel = 200;
    scene_desc.background        = color(0,0,0);

    scene_desc.cam.lookfrom = point3(278, 278, -800);
    scene_desc.cam.lookat   = point3(278, 278, 0);
    scene_desc.cam.vfov     = 40.0;
    scene_desc.cam.aperture = 0.0;

    hittable_list& world = scene_desc.world;

    auto red   = make_shared<lambertian>(color(.65, .05, .05));
    auto white = make_shared<lambertian>(color(.73, .73, .73));
    auto green = make_shared<lambertian>(color(.12, .45, .15));
    auto light = make_shared<diffuse_light>(color(15, 15, 15));

    world.add(make_shared<quad>(point3(555,0,0), vec3(0,555,0), vec3(0,0,555), green));
    world.add(make_shared<quad>(point3(0,0,0), vec3(0,555,0), vec3(0,0,555), red));
    world.add(make_shared<quad>(point3(343, 554, 332), vec3(-130,0,0), vec3(0,0,-105), light));
    world.add(make_shared<quad>(point3(0,0,0), vec3(555,0,0), vec3(0,0,555), white));
    world.add(make_shared<quad>(point3(555,555,555), vec3(-555,0,0), vec3(0,0,-555), white));
    world.add(make_shared<quad>(point3(0,0,555), vec3(555,0,0), vec3(0,555,0), white));

    shared_ptr<hittable> box1 = box(point3(0,0,0), point3(165,330,165), white);
    box1 = make_shared<rotate_y>(box1, 15);
    box1 = make_shared<translate>(box1, vec3(265,0,295));
    world.add(box1);

    shared_ptr<hittable> box2 = box(point3(0,0,0), point3(165,165,165), white);
    box2 = make_shared<rotate_y>(box2, -18);
    box2 = make_shared<translate>(box2, vec3(130,0,65));
    world.add(box2);
}


void cornell_smoke(scene& scene_desc) {
    scene_desc.image_width       = 600;
    scene_desc.aspect_ratio      = 1.0;
    scene_desc.samples_per_pixel = 200;
    scene_desc.background        = color(0,0,0);

    scene_desc.cam.aperture = 0.0;
    scene_desc.cam.vfov     = 40.0;
    scene_desc.cam.lookfrom = point3(278, 278, -800);
    scene_desc.cam.lookat   = point3(278, 278, 0);

    hittable_list& world = scene_desc.world;

    auto red   = make_shared<lambertian>(color(.65, .05, .05));
    auto white = make_shared<lambertian>(color(.73, .73, .73));
    auto green = make_shared<lambertian>(color(.12, .45, .15));
    auto light = make_shared<diffuse_light>(color(7, 7, 7));

    world.add(make_shared<quad>(point3(555,0,0), vec3(0,555,0), vec3(0,0,555), green));
    world.add(make_shared<quad>(point3(0,0,0), vec3(0,555,0), vec3(0,0,555), red));
    world.add(make_shared<quad>(point3(113,554,127), vec3(330,0,0), vec3(0,0,305), light));
    world.add(make_shared<quad>(point3(0,555,0), vec3(555,0,0), vec3(0,0,555), white));
    world.add(make_shared<quad>(point3(0,0,0), vec3(555,0,0), vec3(0,0,555), white));
    world.add(make_shared<quad>(point3(0,0,555), vec3(555,0,0), vec3(0,555,0), white));

    shared_ptr<hittable> box1 = box(point3(0,0,0), point3(165,330,165), white);
    box1 = make_shared<rotate_y>(box1, 15);
    box1 = make_shared<translate>(box1, vec3(265,0,295));

    shared_ptr<hittable> box2 = box(point3(0,0,0), point3(165,165,165), white);
    box2 = make_shared<rotate_y>(box2, -18);
    box2 = make_shared<translate>(box2, vec3(130,0,65));

    world.add(make_shared<constant_medium>(box1, 0.01, color(0,0,0)));
    world.add(make_shared<constant_medium>(box2, 0.01, color(1,1,1)));
}


void final_scene(scene& scene_desc) {
    scene_desc.image_width       = 800;
    scene_desc.aspect_ratio      = 1.0;
    scene_desc.samples_per_pixel = 10000;
    scene_desc.background        = color(0,0,0);

    scene_desc.cam.aperture = 0.0;
    scene_desc.cam.vfov     = 40.0;
    scene_desc.cam.lookfrom = point3(478, 278, -600);
    scene_desc.cam.lookat   = point3(278, 278, 0);

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

            boxes1.add(box(point3(x0,y0,z0), point3(x1,y1,z1), ground));
        }
    }

    hittable_list& world = scene_desc.world;

    world.add(make_shared<bvh_node>(boxes1));

    auto light = make_shared<diffuse_light>(color(7, 7, 7));
    world.add(make_shared<quad>(point3(123,554,147), vec3(300,0,0), vec3(0,0,265), light));

    auto center1 = point3(400, 400, 200);
    auto center2 = center1 + vec3(30,0,0);
    auto moving_sphere_material = make_shared<lambertian>(color(0.7, 0.3, 0.1));
    world.add(make_shared<moving_sphere>(center1, center2, 50, moving_sphere_material));

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
            make_shared<bvh_node>(boxes2), 15),
            vec3(-100,270,395)
        )
    );
}


void default_scene(scene& scene_desc) {
    final_scene(scene_desc);
    scene_desc.image_width       = 400;
    scene_desc.samples_per_pixel = 250;
    scene_desc.max_depth         = 4;
}


void quad_test(scene& scene_desc) {
    scene_desc.image_width       = 400;
    scene_desc.aspect_ratio      = 1.0;
    scene_desc.samples_per_pixel = 4;
    scene_desc.max_depth         = 4;

    scene_desc.cam.aperture = 0.0;
    scene_desc.cam.vfov     = 30.0;
    scene_desc.cam.lookfrom = point3(0,0,12);
    scene_desc.cam.lookat   = point3(0,0,0);

    scene_desc.background   = color(0.80, 0.80, 0.80);

    auto earth_texture = make_shared<image_texture>("earthmap.jpg");
    auto mat = make_shared<lambertian>(earth_texture);

    scene_desc.world.add(make_shared<quad>(point3(-2,-1,0), vec3(4,0,0), vec3(0,2,0), mat));
}


int main() {
    scene scene_desc;

    scene_desc.background = color(0.70, 0.80, 1.00);
    scene_desc.cam.vup = vec3(0,1,0);
    scene_desc.cam.focus_dist = 10.0;

    switch (100) {
        case 1:  random_spheres(scene_desc);     break;
        case 2:  two_spheres(scene_desc);        break;
        case 3:  earth(scene_desc);              break;
        case 4:  two_perlin_spheres(scene_desc); break;
        case 5:  simple_light(scene_desc);       break;
        case 6:  cornell_box(scene_desc);        break;
        case 7:  cornell_smoke(scene_desc);      break;
        case 8:  final_scene(scene_desc);        break;
        default:
        case 9:  default_scene(scene_desc);      break;

        case 100: quad_test(scene_desc); break;
    }

    scene_desc.render();
}
