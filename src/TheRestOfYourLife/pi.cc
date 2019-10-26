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
#include <stdlib.h>


int main() {
    int inside_circle = 0;
    int inside_circle_stratified = 0;
    int sqrt_N = 30000;
    for (int i = 0; i < sqrt_N; i++) {
        for (int j = 0; j < sqrt_N; j++) {
            float x = 2*random_double() - 1;
            float y = 2*random_double() - 1;
            if (x*x + y*y < 1)
                inside_circle++;
            x = 2*((i + random_double()) / sqrt_N) - 1;
            y = 2*((j + random_double()) / sqrt_N) - 1;
            if (x*x + y*y < 1)
                inside_circle_stratified++;
        }
    }
    std::cout << "Regular    Estimate of Pi = " <<
          4*float(inside_circle) / (sqrt_N*sqrt_N) << "\n";
    std::cout << "Stratified Estimate of Pi = " <<
          4*float(inside_circle_stratified) / (sqrt_N*sqrt_N) << "\n";
}

