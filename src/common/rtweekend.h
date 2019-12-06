#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cstdlib>
#include <limits>
#include <cmath>


// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double ffmin(double a, double b) { return a <= b ? a : b; }
inline double ffmax(double a, double b) { return a >= b ? a : b; }

inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

inline double random_double() {
    return rand() / (RAND_MAX + 1.0);
}

// Common Headers

#include "common/ray.h"
#include "common/vec3.h"

#endif
