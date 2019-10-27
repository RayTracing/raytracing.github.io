//==================================================================================================
// Originally written in 2016 by Peter Shirley <ptrshrl@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related and
// neighboring rights to this software to the public domain worldwide. This software is distributed
// without any warranty.
//
// You should have received a copy (see file COPYING.txt) of the CC0 Public Domain Dedication along
// with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
//==================================================================================================

#include "common/rtweekend.h"
#include "common/rtw_stb_image.h"
#include "aarect.h"
#include "box.h"
#include "bvh.h"
#include "camera.h"
#include "hittable_list.h"
#include "material.h"
#include "moving_sphere.h"
#include "pdf.h"
#include "sphere.h"
#include "surface_texture.h"
#include "texture.h"

#include <iostream>


vec3 ray_color(const ray& r, hittable *world, hittable *light_shape, int depth) {
    hit_record hrec;
    if (world->hit(r, 0.001, infinity, hrec)) {
        scatter_record srec;
        vec3 emitted = hrec.mat_ptr->emitted(r, hrec, hrec.u, hrec.v, hrec.p);
        if (depth < 50 && hrec.mat_ptr->scatter(r, hrec, srec)) {
            if (srec.is_specular) {
                return srec.attenuation * ray_color(srec.specular_ray, world, light_shape, depth+1);
            }
            else {
                hittable_pdf plight(light_shape, hrec.p);
                mixture_pdf p(&plight, srec.pdf_ptr);
                ray scattered = ray(hrec.p, p.generate(), r.time());
                auto pdf_val = p.value(scattered.direction());
                delete srec.pdf_ptr;
                return emitted
                     + srec.attenuation * hrec.mat_ptr->scattering_pdf(r, hrec, scattered)
                                        * ray_color(scattered, world, light_shape, depth+1)
                                        / pdf_val;
            }
        }
        else
            return emitted;
    }
    else
        return vec3(0,0,0);
}

void cornell_box(hittable **scene, camera **cam, double aspect) {
    material *red = new lambertian( new constant_texture(vec3(0.65, 0.05, 0.05)) );
    material *white = new lambertian( new constant_texture(vec3(0.73, 0.73, 0.73)) );
    material *green = new lambertian( new constant_texture(vec3(0.12, 0.45, 0.15)) );
    material *light = new diffuse_light( new constant_texture(vec3(15, 15, 15)) );

    hittable **list = new hittable*[8];
    int i = 0;
    list[i++] = new flip_normals(new yz_rect(0, 555, 0, 555, 555, green));
    list[i++] = new yz_rect(0, 555, 0, 555, 0, red);
    list[i++] = new flip_normals(new xz_rect(213, 343, 227, 332, 554, light));
    list[i++] = new flip_normals(new xz_rect(0, 555, 0, 555, 555, white));
    list[i++] = new xz_rect(0, 555, 0, 555, 0, white);
    list[i++] = new flip_normals(new xy_rect(0, 555, 0, 555, 555, white));
    material *glass = new dielectric(1.5);
    list[i++] = new sphere(vec3(190, 90, 190),90 , glass);
    list[i++] = new translate(new rotate_y(
                    new box(vec3(0, 0, 0), vec3(165, 330, 165), white),  15), vec3(265,0,295));
    *scene = new hittable_list(list,i);

    vec3 lookfrom(278, 278, -800);
    vec3 lookat(278, 278, 0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.0;
    auto vfov = 40.0;
    *cam = new camera(lookfrom, lookat, vec3(0,1,0),
                      vfov, aspect, aperture, dist_to_focus, 0.0, 1.0);
}

int main() {
    int nx = 600;
    int ny = 600;
    int num_samples = 100;

    std::cout << "P3\n" << nx << ' ' << ny << "\n255\n";

    hittable *world;
    camera *cam;
    auto aspect = double(ny) / double(nx);
    cornell_box(&world, &cam, aspect);
    hittable *light_shape = new xz_rect(213, 343, 227, 332, 554, 0);
    hittable *glass_sphere = new sphere(vec3(190, 90, 190), 90, 0);
    hittable *a[2];
    a[0] = light_shape;
    a[1] = glass_sphere;
    hittable_list hlist(a,2);

    for (int j = ny-1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            vec3 color;
            for (int s = 0; s < num_samples; s++) {
                auto u = (i + random_double()) / nx;
                auto v = (j + random_double()) / ny;
                ray r = cam->get_ray(u, v);
                vec3 p = r.point_at_parameter(2.0);
                color += ray_color(r, world, &hlist, 0);
            }
            color.write_color(std::cout, num_samples);
        }
    }
}
