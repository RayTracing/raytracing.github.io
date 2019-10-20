#ifndef MATERIALH
#define MATERIALH
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

#include "common/rtweekend.h"
#include "hittable.h"
#include "onb.h"
#include "pdf.h"
#include "random.h"
#include "ray.h"
#include "texture.h"


double schlick(double cosine, double ref_idx) {
    auto r0 = (1-ref_idx) / (1+ref_idx);
    r0 = r0*r0;
    return r0 + (1-r0)*pow((1 - cosine),5);
}

bool refract(const vec3& v, const vec3& n, double ni_over_nt, vec3& refracted) {
    vec3 uv = unit_vector(v);
    auto dt = dot(uv, n);
    auto discriminant = 1.0 - ni_over_nt*ni_over_nt*(1-dt*dt);
    if (discriminant > 0) {
        refracted = ni_over_nt*(uv - n*dt) - n*sqrt(discriminant);
        return true;
    }
    else
        return false;
}


vec3 reflect(const vec3& v, const vec3& n) {
     return v - 2*dot(v,n)*n;
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
        virtual bool scatter(const ray& r_in, const hit_record& hrec, scatter_record& srec) const {
            return false;
        }
        virtual double scattering_pdf(const ray& r_in, const hit_record& rec, const ray& scattered) const {
            return 0;
        }
        virtual vec3 emitted(const ray& r_in, const hit_record& rec, double u, double v, const vec3& p) const {
            return vec3(0,0,0);
        }
};

class dielectric : public material {
    public:
        dielectric(double ri) : ref_idx(ri) {}
        virtual bool scatter(const ray& r_in, const hit_record& hrec, scatter_record& srec) const {
            srec.is_specular = true;
            srec.pdf_ptr = 0;
            srec.attenuation = vec3(1.0, 1.0, 1.0);
            vec3 outward_normal;
             vec3 reflected = reflect(r_in.direction(), hrec.normal);
             vec3 refracted;
             double ni_over_nt;
             double reflect_prob;
             double cosine;
             if (dot(r_in.direction(), hrec.normal) > 0) {
                  outward_normal = -hrec.normal;
                  ni_over_nt = ref_idx;
                  cosine = ref_idx * dot(r_in.direction(), hrec.normal) / r_in.direction().length();
             }
             else {
                  outward_normal = hrec.normal;
                  ni_over_nt = 1.0 / ref_idx;
                  cosine = -dot(r_in.direction(), hrec.normal) / r_in.direction().length();
             }
             if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted)) {
                reflect_prob = schlick(cosine, ref_idx);
             }
             else {
                reflect_prob = 1.0;
             }
             if (random_double() < reflect_prob) {
                srec.specular_ray = ray(hrec.p, reflected);
             }
             else {
                srec.specular_ray = ray(hrec.p, refracted);
             }
             return true;
        }

        double ref_idx;
};


class metal : public material {
    public:
        metal(const vec3& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

        virtual bool scatter(const ray& r_in, const hit_record& hrec, scatter_record& srec) const {
            vec3 reflected = reflect(unit_vector(r_in.direction()), hrec.normal);
            srec.specular_ray = ray(hrec.p, reflected + fuzz*random_in_unit_sphere());
            srec.attenuation = albedo;
            srec.is_specular = true;
            srec.pdf_ptr = 0;
            return true;
        }
        vec3 albedo;
        double fuzz;
};



class lambertian : public material {
    public:
        lambertian(texture *a) : albedo(a) {}
        double scattering_pdf(const ray& r_in, const hit_record& rec, const ray& scattered) const {
            auto cosine = dot(rec.normal, unit_vector(scattered.direction()));
            if (cosine < 0)
                return 0;
            return cosine / pi;
        }
        bool scatter(const ray& r_in, const hit_record& hrec, scatter_record& srec) const {
            srec.is_specular = false;
            srec.attenuation = albedo->value(hrec.u, hrec.v, hrec.p);
            srec.pdf_ptr = new cosine_pdf(hrec.normal);
            return true;
        }
        texture *albedo;
};


class diffuse_light : public material  {
    public:
        diffuse_light(texture *a) : emit(a) {}
        virtual vec3 emitted(const ray& r_in, const hit_record& rec, double u, double v, const vec3& p) const {
            if (dot(rec.normal, r_in.direction()) < 0.0)
                return emit->value(u, v, p);
            else
                return vec3(0,0,0);
        }
        texture *emit;
};


/*
class isotropic : public material {
    public:
        isotropic(texture *a) : albedo(a) {}
        virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const  {
             scattered = ray(rec.p, random_in_unit_sphere());
             attenuation = albedo->value(rec.u, rec.v, rec.p);
             return true;
        }

        texture *albedo;
};
*/


/*
class metal : public material {
    public:
        metal(const vec3& a, double f) : albedo(a) { if (f < 1) fuzz = f; else fuzz = 1; }
        virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const  {
            vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
            scattered = ray(rec.p, reflected + fuzz*random_in_unit_sphere());
            attenuation = albedo;
            return (dot(scattered.direction(), rec.normal) > 0);
        }
        vec3 albedo;
        double fuzz;
};

class dielectric : public material {
    public:
        dielectric(double ri) : ref_idx(ri) {}
        virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const  {
             vec3 outward_normal;
             vec3 reflected = reflect(r_in.direction(), rec.normal);
             double ni_over_nt;
             attenuation = vec3(1.0, 1.0, 1.0);
             vec3 refracted;
             double reflect_prob;
             double cosine;
             if (dot(r_in.direction(), rec.normal) > 0) {
                  outward_normal = -rec.normal;
                  ni_over_nt = ref_idx;
                  cosine = ref_idx * dot(r_in.direction(), rec.normal) / r_in.direction().length();
             }
             else {
                  outward_normal = rec.normal;
                  ni_over_nt = 1.0 / ref_idx;
                  cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().length();
             }
             if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted)) {
                reflect_prob = schlick(cosine, ref_idx);
             }
             else {
                scattered = ray(rec.p, reflected);
                reflect_prob = 1.0;
             }
             if (random_double() < reflect_prob) {
                scattered = ray(rec.p, reflected);
             }
             else {
                scattered = ray(rec.p, refracted);
             }
             return true;
        }

        double ref_idx;
};

*/

#endif

