#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <limits>


// Constants

const double pi = 3.1415926535897932385;
const double infinity = std::numeric_limits<double>::infinity();

// Utility Functions

inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

#endif
