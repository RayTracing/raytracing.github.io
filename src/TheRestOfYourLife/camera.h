#ifndef CAMERA_H
#define CAMERA_H
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

#include "color.h"
#include "hittable.h"
#include "material.h"

#include <iostream>


class camera {
  public:
    double aspect_ratio      = 1.0;
    int    image_width       = 100;
    int    samples_per_pixel = 10;
    int    max_depth         = 20;
    color  background        = color(0,0,0);

    double vfov     = 40;
    point3 lookfrom = point3(0,0,-1);
    point3 lookat   = point3(0,0,0);
    vec3   vup      = vec3(0,1,0);

    double aperture   = 0;
    double focus_dist = 10;

    void render(const hittable& world, const hittable& lights) {
        initialize();

        int image_height = static_cast<int>(image_width / aspect_ratio);

        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        int sqrt_spp = int(sqrt(samples_per_pixel));
        for (int j = 0; j < image_height; ++j) {
            std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
            for (int i = 0; i < image_width; ++i) {
                color pixel_color(0,0,0);
                for (int s_j = 0; s_j < sqrt_spp; ++s_j) {
                    for (int s_i = 0; s_i < sqrt_spp; ++s_i) {
                        auto s = (i + (s_i + random_double()) / sqrt_spp) / (image_width-1);
                        auto t = (j + (s_j + random_double()) / sqrt_spp) / (image_height-1);
                        ray r = get_ray(s, t);
                        pixel_color += ray_color(r, max_depth, world, lights);
                    }
                }
                write_color(std::cout, pixel_color, samples_per_pixel);
            }
        }

        std::clog << "\rDone.                 \n";
    }

  private:
    point3 origin;
    point3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 u, v, w;
    double lens_radius;

    void initialize() {
        auto theta = degrees_to_radians(vfov);
        auto h = tan(theta/2);
        auto viewport_height = 2.0 * h;
        auto viewport_width = aspect_ratio * viewport_height;

        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup, w));
        v = cross(w, u);

        origin = lookfrom;
        horizontal = focus_dist * viewport_width * u;
        vertical = focus_dist * viewport_height * v;
        lower_left_corner = origin - horizontal/2 - vertical/2 - focus_dist*w;

        lens_radius = aperture / 2;
    }

    ray get_ray(double s, double t) const {
        // Return the ray from the projection point to the indicated pixel. Coordinates s,t are
        // the normalized image-based coordinates of the pixel. Image left is s=0, image right
        // is s=1, image top is t=0, image bottom is t=1.

        vec3 rd = lens_radius * random_in_unit_disk();
        vec3 offset = u * rd.x() + v * rd.y();
        auto ray_time = random_double(0.0, 1.0);

        return ray(
            origin + offset,
            lower_left_corner + s*horizontal + (1-t)*vertical - origin - offset,
            ray_time
        );
    }

    color ray_color(const ray& r, int depth, const hittable& world, const hittable& lights)
    const {
        hit_record rec;

        // If we've exceeded the ray bounce limit, no more light is gathered.
        if (depth <= 0)
            return color(0,0,0);

        // If the ray hits nothing, return the background color.
        if (!world.hit(r, interval(0.001, infinity), rec))
            return background;

        scatter_record srec;
        color color_from_emission = rec.mat->emitted(r, rec, rec.u, rec.v, rec.p);

        if (!rec.mat->scatter(r, rec, srec))
            return color_from_emission;

        if (srec.skip_pdf) {
            return srec.attenuation * ray_color(srec.skip_pdf_ray, depth-1, world, lights);
        }

        auto light_ptr = make_shared<hittable_pdf>(lights, rec.p);
        mixture_pdf p(light_ptr, srec.pdf_ptr);

        ray scattered = ray(rec.p, p.generate(), r.time());
        auto pdf_val = p.value(scattered.direction());

        double scattering_pdf = rec.mat->scattering_pdf(r, rec, scattered);

        color sample_color = ray_color(scattered, depth-1, world, lights);
        color color_from_scatter = (srec.attenuation * scattering_pdf * sample_color) / pdf_val;

        return color_from_emission + color_from_scatter;
    }
};


#endif
