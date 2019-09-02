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

#include <iostream>
#include <math.h>


int main() {
    int N = 1000000;
    float sum = 0.0;
    for (int i = 0; i < N; i++) {
        float r1 = random_double();
        float r2 = random_double();
        float x = cos(2*M_PI*r1)*2*sqrt(r2*(1-r2));
        float y = sin(2*M_PI*r1)*2*sqrt(r2*(1-r2));
        float z = 1 - r2;
        sum += z*z*z / (1.0/(2.0*M_PI));
    }
    std::cout << "PI/2 = " << M_PI/2 << "\n";
    std::cout << "Estimate = " << sum/N << "\n";
}

