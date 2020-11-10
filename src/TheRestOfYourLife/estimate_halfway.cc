//==============================================================================================
// Originally written in 2020 by Peter Shirley <ptrshrl@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related and
// neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy (see file COPYING.txt) of the CC0 Public Domain Dedication
// along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
//==============================================================================================

#include "rtweekend.h"

#include <algorithm>
#include <vector>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <cmath>
#include <stdlib.h>

int main() {
    int N = 10000;
    double sum = 0.0;
    // Get all of our samples
    // Get the area under the curve
    std::vector<std::pair<double, double>> samples;
    for (int i = 0; i < N; i++) {
        auto x = random_double(0,2 * pi);
        auto p_x = exp(-x/ (2 * pi)) * sin(x) * sin(x);
        sum += p_x;
        for(int s = 0; s < samples.size(); s++)
        {
            // sort by x
            if(x > samples[s].first) {
                samples.insert(samples.begin() + s, std::pair<double, double>(x, p_x));
                break;
            }
        }
        samples.push_back(std::pair<double, double>(x, p_x));
    }

    // Find out the sample at which we have half of our area
    double half_sum = sum / 2.0;
    double halfway_point;
    double accum = 0.0;
    for (int i = 0; i < N; i++){
        accum += samples[i].second;
        if (accum >= half_sum){
            halfway_point = samples[i].first;
            break;
        }
    }

    std::cout << std::fixed << std::setprecision(12);
    std::cout << "Average = " << sum / N << '\n';
    std::cout << "Area under curve = " << 2 * pi * sum / N << '\n';
    std::cout << "Halfway = " << halfway_point << '\n';
}
