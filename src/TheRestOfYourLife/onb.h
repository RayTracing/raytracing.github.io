#ifndef ONBH
#define ONBH
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

#include "vec3.h"


class onb
{
    public:
        onb() {}
        inline vec3 operator[](int i) const { return axis[i]; }
        vec3 u() const       { return axis[0]; }
        vec3 v() const       { return axis[1]; }
        vec3 w() const       { return axis[2]; }
        vec3 local(float a, float b, float c) const { return a*u() + b*v() + c*w(); }
        vec3 local(const vec3& a) const { return a.x()*u() + a.y()*v() + a.z()*w(); }
        void build_from_w(const vec3&);
        vec3 axis[3];
};


void onb::build_from_w(const vec3& n) {
    axis[2] = unit_vector(n);
    vec3 a;
    if (fabs(w().x()) > 0.9)
        a = vec3(0, 1, 0);
    else
        a = vec3(1, 0, 0);
    axis[1] = unit_vector( cross( w(), a ) );
    axis[0] = cross(w(), v());
}


#endif
