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
    int N = 1000000;
    float sum;
    for (int i = 0; i < N; i++) {
            float x = 2*random_double();
            sum += x*x;
    }
    std::cout << "I =" << 2*sum/N << "\n";
}

