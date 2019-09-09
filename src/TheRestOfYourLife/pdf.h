#ifndef PDFH
#define PDFH
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

#include "onb.h"
#include "random.h"


inline vec3 random_cosine_direction() {
    float r1 = random_double();
    float r2 = random_double();
    float z = sqrt(1-r2);
    float phi = 2*M_PI*r1;
    float x = cos(phi)*sqrt(r2);
    float y = sin(phi)*sqrt(r2);
    return vec3(x, y, z);
}

inline vec3 random_to_sphere(float radius, float distance_squared) {
    float r1 = random_double();
    float r2 = random_double();
    float z = 1 + r2*(sqrt(1-radius*radius/distance_squared) - 1);
    float phi = 2*M_PI*r1;
    float x = cos(phi)*sqrt(1-z*z);
    float y = sin(phi)*sqrt(1-z*z);
    return vec3(x, y, z);
}


vec3 random_in_unit_sphere() {
    vec3 p;
    do {
        p = 2.0*vec3(random_double(),random_double(),random_double()) - vec3(1,1,1);
    } while (dot(p,p) >= 1.0);
    return p;
}



class pdf  {
    public:
        virtual float value(const vec3& direction) const = 0;
        virtual vec3 generate() const = 0;
        virtual ~pdf() {}
};


class cosine_pdf : public pdf {
    public:
        cosine_pdf(const vec3& w) { uvw.build_from_w(w); }
        virtual float value(const vec3& direction) const {
            float cosine = dot(unit_vector(direction), uvw.w());
            if (cosine > 0)
                return cosine/M_PI;
            else
                return 0;
        }
        virtual vec3 generate() const  {
            return uvw.local(random_cosine_direction());
        }
        onb uvw;
};

class hittable_pdf : public pdf {
    public:
        hittable_pdf(hittable *p, const vec3& origin) : ptr(p), o(origin) {}
        virtual float value(const vec3& direction) const {
            return ptr->pdf_value(o, direction);
        }
        virtual vec3 generate() const {
            return ptr->random(o);
        }
        vec3 o;
        hittable *ptr;
};

class mixture_pdf : public pdf {
    public:
        mixture_pdf(pdf *p0, pdf *p1 ) { p[0] = p0; p[1] = p1; }
        virtual float value(const vec3& direction) const {
            return 0.5 * p[0]->value(direction) + 0.5 *p[1]->value(direction);
        }
        virtual vec3 generate() const {
            if (random_double() < 0.5)
                return p[0]->generate();
            else
                return p[1]->generate();
        }
        pdf *p[2];
};

#endif
