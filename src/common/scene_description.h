#ifndef SCENE_DESCRIPTION_H
#define SCENE_DESCRIPTION_H
//==============================================================================================
// To the extent possible under law, the author(s) have dedicated all copyright and related and
// neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy (see file COPYING.txt) of the CC0 Public Domain Dedication
// along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
//==============================================================================================

#include "rtweekend.h"

#include "hittable_list.h"
#include "camera.h"


class scene_description {
    public:
        scene_description()
          : image_width(1000),
            sample_count(100),
            background(color(0,0,0))
        {}

        int get_image_height() const {
            return static_cast<int>(image_width / cam.aspect_ratio);
        }

    public:
        int           image_width;
        int           sample_count;
        color         background;
        camera        cam;
        hittable_list world;
};


#endif
