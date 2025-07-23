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

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"


using std::make_shared;

int main() {

    hittable_list world;

    // Terreno escuro e levemente variado
    auto ground_material = make_shared<lambertian>(color(0.05, 0.05, 0.1));
    world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

   
}
