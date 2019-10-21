#ifndef COLOR_H
#define COLOR_H
//==================================================================================================
// To the extent possible under law, the author(s) have dedicated all copyright and related and
// neighboring rights to this software to the public domain worldwide. This software is distributed
// without any warranty.
//
// You should have received a copy (see file COPYING.txt) of the CC0 Public Domain Dedication along
// with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
//==================================================================================================

#include "common/rtweekend.h"
#include "common/vec3.h"

#include <iostream>


class color {
    public:
        double r, g, b; // color components

        color() : r(0), g(0), b(0) {}
        color(double red, double green, double blue) : r(red), g(green), b(blue) {}
        color(const vec3& v) : r(v[0]), g(v[1]), b(v[2]) {}

        color& operator+=(const color &c) {
            r += c.r;
            g += c.g;
            b += c.b;
            return *this;
        }

        color& operator*=(double s) {
            r *= s;
            g *= s;
            b *= s;
            return *this;
        }

        color& operator/=(double d) {
            return *this *= 1/d;
        }
};


// Color Utility Functions

inline std::ostream& operator<<(std::ostream &out, const color &c) {
    // Intercept colors with NaN values and emit the NaN-signalling color instead.
    if (c.r != c.r || c.g != c.g || c.b != c.b)
        return out << "255 0 255";

    // Emit the translated [0,255] value of each color component.
    return out
        << static_cast<int>(256.0 * clamp(c.r, 0.0, 0.999999)) << ' '
        << static_cast<int>(256.0 * clamp(c.g, 0.0, 0.999999)) << ' '
        << static_cast<int>(256.0 * clamp(c.b, 0.0, 0.999999));
}

// Color-Vector Operations

color operator+( const color &c, const vec3 &v) {
    return color(c.r + v[0], c.g + v[1], c.b + v[2]);
}

color operator+(const vec3 &v, const color &c) {
    return c + v;
}

color operator*(const vec3 &v, const color &c) {
    return color(v[0] * c.r, v[1] * c.g, v[2] * c.b);
}

// Color-Scalar Operations

color operator*(double s, const color& c) {
    return color(s*c.r, s*c.g, s*c.b);
}

color operator*(const color& c, double s) {
    return s * c;
}

color operator/(const color& c, double d) {
    return (1/d) * c;
}

#endif
