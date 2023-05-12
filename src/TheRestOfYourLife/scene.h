#ifndef SCENE_H
#define SCENE_H
//==============================================================================================
// To the extent possible under law, the author(s) have dedicated all copyright and related and
// neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy (see file COPYING.txt) of the CC0 Public Domain Dedication
// along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
//==============================================================================================

#include "rtweekend.h"

#include "camera.h"
#include "hittable_list.h"

#include <iostream>


class scene {
  public:
    void render() {
        cam.initialize();

        auto image_width = cam.image_width;
        auto image_height = cam.get_image_height();

        int sqrt_spp = int(sqrt(samples_per_pixel));

        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        for (int j = 0; j < image_height; ++j) {
            std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
            for (int i = 0; i < image_width; ++i) {
                color pixel_color(0,0,0);
                for (int s_j = 0; s_j < sqrt_spp; ++s_j) {
                    for (int s_i = 0; s_i < sqrt_spp; ++s_i) {
                        auto s = (i + (s_i + random_double()) / sqrt_spp) / (image_width-1);
                        auto t = (j + (s_j + random_double()) / sqrt_spp) / (image_height-1);
                        ray r = cam.get_ray(s, t);
                        pixel_color += ray_color(r, max_depth);
                    }
                }
                write_color(std::cout, pixel_color, samples_per_pixel);
            }
        }

        std::clog << "\rDone.                 \n";
    }

  public:
    hittable_list world;
    hittable_list lights;
    camera cam;

    // Scene sampling parameters
    int    samples_per_pixel = 10;
    int    max_depth         = 20;
    color  background        = color(0,0,0);

  private:
    color ray_color(const ray& r, int depth) {
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
            return srec.attenuation * ray_color(srec.skip_pdf_ray, depth-1);
        }

        auto light_ptr = make_shared<hittable_pdf>(lights, rec.p);
        mixture_pdf p(light_ptr, srec.pdf_ptr);

        ray scattered = ray(rec.p, p.generate(), r.time());
        auto pdf_val = p.value(scattered.direction());

        double scattering_pdf = rec.mat->scattering_pdf(r, rec, scattered);

        color color_from_scatter =
            (srec.attenuation * scattering_pdf * ray_color(scattered, depth-1)) / pdf_val;

        return color_from_emission + color_from_scatter;
    }
};


#endif
