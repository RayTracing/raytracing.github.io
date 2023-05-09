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
    void render(int resolution_x, int samples_per_pixel) {
        const int resolution_y = static_cast<int>(resolution_x / aspect_ratio);

        cam.initialize(aspect_ratio);

        std::cout << "P3\n" << resolution_x << ' ' << resolution_y << "\n255\n";

        for (int j = 0; j < resolution_y; ++j) {
            std::clog << "\rScanlines remaining: " << (resolution_y - j) << ' ' << std::flush;
            for (int i = 0; i < resolution_x; ++i) {
                color pixel_color(0,0,0);
                for (int sample = 0; sample < samples_per_pixel; ++sample) {
                    auto s = (i + random_double()) / (resolution_x - 1);
                    auto t = (j + random_double()) / (resolution_y - 1);
                    ray r = cam.get_ray(s, t);
                    pixel_color += ray_color(r, max_depth);
                }
                write_color(std::cout, pixel_color, samples_per_pixel);
            }
        }

        std::clog << "\rDone.                 \n";
    }

  public:
    camera cam;
    hittable_list world;

    double aspect_ratio = 1.0;
    int max_depth = 20;
    color background = color(0,0,0);

  private:
    color ray_color(const ray& r, int depth) {
        hit_record rec;

        // If we've exceeded the ray bounce limit, no more light is gathered.
        if (depth <= 0)
            return color(0,0,0);

        // If the ray hits nothing, return the background color.
        if (!world.hit(r, interval(0.001, infinity), rec))
            return background;

        ray scattered;
        color attenuation;
        color color_from_emission = rec.mat->emitted(rec.u, rec.v, rec.p);

        if (!rec.mat->scatter(r, rec, attenuation, scattered))
            return color_from_emission;

        color color_from_scatter = attenuation * ray_color(scattered, depth-1);

        return color_from_emission + color_from_scatter;
    }
};


#endif
