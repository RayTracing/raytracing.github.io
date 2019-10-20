#ifndef RAY_H
#define RAY_H
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

#include "common/vec3.h"


class ray
{
    public:
        ray() {}
        ray(const vec3& a, const vec3& b, double ti = 0.0) { A = a; B = b; _time = ti;}
        vec3 origin() const    { return A; }
        vec3 direction() const { return B; }
        double time() const    { return _time; }
        vec3 point_at_parameter(double t) const { return A + t*B; }

        vec3 A;
        vec3 B;
        double _time;
};

#endif
