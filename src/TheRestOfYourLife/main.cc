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
#include "color.h"
#include "constant_medium.h"
#include "hittable_list.h"
#include "material.h"
#include "scene.h"
#include "sphere.h"


void cornell_box(scene& scene_desc) {
    scene_desc.image_width       = 600;
    scene_desc.aspect_ratio      = 1.0;
    scene_desc.samples_per_pixel = 100;
    scene_desc.max_depth         = 50;
    scene_desc.background        = color(0,0,0);

    scene_desc.cam.lookfrom     = point3(278, 278, -800);
    scene_desc.cam.lookat       = point3(278, 278, 0);
    scene_desc.cam.vup          = vec3(0, 1, 0);
    scene_desc.cam.vfov         = 40.0;
    scene_desc.cam.aperture     = 0.0;
    scene_desc.cam.focus_dist   = 10.0;

    hittable_list& world = scene_desc.world;

    auto red   = make_shared<lambertian>(color(.65, .05, .05));
    auto white = make_shared<lambertian>(color(.73, .73, .73));
    auto green = make_shared<lambertian>(color(.12, .45, .15));
    auto light = make_shared<diffuse_light>(color(15, 15, 15));

    world.add(make_shared<yz_rect>(0, 555, 0, 555, 555, green));
    world.add(make_shared<yz_rect>(0, 555, 0, 555, 0, red));
    world.add(make_shared<flip_face>(make_shared<xz_rect>(213, 343, 227, 332, 554, light)));
    world.add(make_shared<xz_rect>(0, 555, 0, 555, 555, white));
    world.add(make_shared<xz_rect>(0, 555, 0, 555, 0, white));
    world.add(make_shared<xy_rect>(0, 555, 0, 555, 555, white));

    shared_ptr<material> aluminum = make_shared<metal>(color(0.8, 0.85, 0.88), 0.0);
    shared_ptr<hittable> box1 = make_shared<box>(point3(0,0,0), point3(165,330,165), aluminum);
    box1 = make_shared<rotate_y>(box1, 15);
    box1 = make_shared<translate>(box1, vec3(265,0,295));
    world.add(box1);

    auto glass = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(190,90,190), 90 , glass));

    hittable_list& lights = scene_desc.lights;
    lights.add(make_shared<xz_rect>(213, 343, 227, 332, 554, shared_ptr<material>()));
    lights.add(make_shared<sphere>(point3(190, 90, 190), 90, shared_ptr<material>()));
}

void cornell_smoke(scene& scene_desc) {
    scene_desc.image_width       = 600;
    scene_desc.aspect_ratio      = 1.0;
    scene_desc.samples_per_pixel = 100;
    scene_desc.max_depth         = 50;
    scene_desc.background        = color(0,0,0);

    scene_desc.cam.lookfrom     = point3(278, 278, -800);
    scene_desc.cam.lookat       = point3(278, 278, 0);
    scene_desc.cam.vup          = vec3(0, 1, 0);
    scene_desc.cam.vfov         = 40.0;
    scene_desc.cam.aperture     = 0.0;
    scene_desc.cam.focus_dist   = 10.0;

    hittable_list& world = scene_desc.world;

    auto red   = make_shared<lambertian>(color(.65, .05, .05));
    auto white = make_shared<lambertian>(color(.73, .73, .73));
    auto green = make_shared<lambertian>(color(.12, .45, .15));
    auto light = make_shared<diffuse_light>(color(15, 15, 15));

    world.add(make_shared<yz_rect>(0, 555, 0, 555, 555, green));
    world.add(make_shared<yz_rect>(0, 555, 0, 555, 0, red));
    world.add(make_shared<flip_face>(make_shared<xz_rect>(213, 343, 227, 332, 554, light)));
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

    hittable_list& lights = scene_desc.lights;
    lights.add(make_shared<xz_rect>(213, 343, 227, 332, 554, shared_ptr<material>()));
}

int main() {
    scene scene_desc;
    cornell_box(scene_desc);
    scene_desc.render();
}
