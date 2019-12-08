#ifndef MATERIAL_H
#define MATERIAL_H
//==============================================================================================
// Originally written in 2016 by Peter Shirley <ptrshrl@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related and
// neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy (see file COPYING.txt) of the CC0 Public Domain Dedication
// along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
//==============================================================================================

#include "common/rtweekend.h"
#include "common/texture.h"
#include "pdf.h"


double schlick(double cosine, double ref_idx) {
    double r0 = (1-ref_idx) / (1+ref_idx);
    r0 = r0*r0;
    return r0 + (1-r0)*pow((1 - cosine),5);
}


struct scatter_record
{
    ray specular_ray;
    bool is_specular;
    vec3 attenuation;
    pdf *pdf_ptr;
};


class material  {
    public:
        virtual vec3 emitted(
            const ray& r_in, const hit_record& rec, double u, double v, const vec3& p
        ) const {
            return vec3(0,0,0);
        }

        virtual bool scatter(
            const ray& r_in, const hit_record& rec, scatter_record& srec
        ) const {
            return false;
        }

        virtual double scattering_pdf(
            const ray& r_in, const hit_record& rec, const ray& scattered
        ) const {
            return 0;
        }
};


class dielectric : public material {
    public:
        dielectric(double ri) : ref_idx(ri) {}

        virtual bool scatter(
            const ray& r_in, const hit_record& rec, scatter_record& srec
        ) const {
            srec.is_specular = true;
            srec.pdf_ptr = 0;
            srec.attenuation = vec3(1.0, 1.0, 1.0);
            vec3 outward_normal;
            vec3 reflected = reflect(r_in.direction(), rec.normal);
            vec3 refracted;
            double ni_over_nt;
            double reflect_prob;
            double cosine;

            if (dot(r_in.direction(), rec.normal) > 0) {
                outward_normal = -rec.normal;
                ni_over_nt = ref_idx;
                cosine = ref_idx * dot(r_in.direction(), rec.normal)
                       / r_in.direction().length();
            } else {
                outward_normal = rec.normal;
                ni_over_nt = 1.0 / ref_idx;
                cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().length();
            }

            if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted)) {
                reflect_prob = schlick(cosine, ref_idx);
            } else {
                reflect_prob = 1.0;
            }

            if (random_double() < reflect_prob) {
               srec.specular_ray = ray(rec.p, reflected, r_in.time());
            } else {
               srec.specular_ray = ray(rec.p, refracted, r_in.time());
            }

            return true;
        }

        double ref_idx;
};


class diffuse_light : public material {
    public:
        diffuse_light(texture *a) : emit(a) {}

        virtual vec3 emitted(
            const ray& r_in, const hit_record& rec, double u, double v, const vec3& p
        ) const {
            if (dot(rec.normal, r_in.direction()) >= 0.0)
                return vec3(0,0,0);
            return emit->value(u, v, p);
        }

        texture *emit;
};


class isotropic : public material {
    public:
        isotropic(texture *a) : albedo(a) {}

        virtual bool scatter(
            const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered
        ) const  {
            scattered = ray(rec.p, random_in_unit_sphere(), r_in.time());
            attenuation = albedo->value(rec.u, rec.v, rec.p);
            return true;
        }

        texture *albedo;
};


class lambertian : public material {
    public:
        lambertian(texture *a) : albedo(a) {}

        bool scatter(const ray& r_in, const hit_record& rec, scatter_record& srec) const {
            srec.is_specular = false;
            srec.attenuation = albedo->value(rec.u, rec.v, rec.p);
            srec.pdf_ptr = new cosine_pdf(rec.normal);
            return true;
        }

        double scattering_pdf(
            const ray& r_in, const hit_record& rec, const ray& scattered
        ) const {
            auto cosine = dot(rec.normal, unit_vector(scattered.direction()));
            return cosine < 0 ? 0 : cosine/pi;
        }

        texture *albedo;
};


class metal : public material {
    public:
        metal(const vec3& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

        virtual bool scatter(
            const ray& r_in, const hit_record& rec, scatter_record& srec
        ) const {
            vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
            srec.specular_ray = ray(rec.p, reflected + fuzz*random_in_unit_sphere(), r_in.time());
            srec.attenuation = albedo;
            srec.is_specular = true;
            srec.pdf_ptr = 0;
            return true;
        }

        vec3 albedo;
        double fuzz;
};


#endif
