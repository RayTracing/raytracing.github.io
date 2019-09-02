//==================================================================================================
// Written in 2016 by Peter Shirley <ptrshrl@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related and
// neighboring rights to this software to the public domain worldwide. This software is distributed
// without any warranty.
//
// You should have received a copy (see file COPYING.txt) of the CC0 Public Domain Dedication along
// with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
//==================================================================================================

#include "random.h"
#include "vec3.h"

#include <iostream>
#include <math.h>
#include <stdlib.h>


vec3 random_on_unit_sphere() {
    vec3 p;
    do {
        p = 2.0*vec3(random_double(),random_double(),random_double()) - vec3(1,1,1);
    } while (dot(p,p) >= 1.0);
    return unit_vector(p);
}



inline float pdf(const vec3& p) {
    return  1 / (4*M_PI);
}

int main() {
    int N = 1000000;
    float sum;
    for (int i = 0; i < N; i++) {
            vec3 d = random_on_unit_sphere();
            float cosine_squared = d.z()*d.z();
            sum += cosine_squared / pdf(d);
    }
    std::cout << "I =" << sum/N << "\n";
}

