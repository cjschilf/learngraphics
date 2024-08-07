#ifndef MATERIAL_H
#define MATERIAL_H

#include "rtweekend.h"
#include "hittable.h"

class hit_record;

class material {
  public:
    virtual ~material() = default;

    virtual bool scatter(
        const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
    ) const {
        return false;
    }
};

class lambertian : public material {
    public:
        lambertian(const color& albedo) : albedo(albedo) {}

        bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
            auto scatter_dir = rec.normal + random_unit_vector();

            // catch degenerate scattering
            if (scatter_dir.near_zero()) {
                scatter_dir = rec.normal;
            }

            scattered = ray(rec.p, scatter_dir);
            attenuation = albedo;
            return true;
        }
    
    private:
        color albedo;
};

class metal : public material {
    public:
        metal(const color& albedo, double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1){}

        bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
            vec3 reflected = reflect(r_in.direction(), rec.normal);
            // use fuzz for slight randomization, blurs reflection
            reflected = unit_vector(reflected) + (fuzz * random_unit_vector());
            scattered = ray(rec.p, reflected);
            attenuation = albedo;
            // avoid returning true in case fuzz randomized it into the object
            return (dot(scattered.direction(), rec.normal) > 0);
        }
    
    private:
        color albedo;
        double fuzz;
};

class dielectric : public material {
    public:
        dielectric(double refract_index) : refract_index(refract_index) {}

        bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
            attenuation = color(1.0,1.0,1.0);
            
            double ri = rec.front_face ? (1.0 / refract_index) : refract_index;

            vec3 unit_dir = unit_vector(r_in.direction());
            
            double cos_theta = fmin(dot(-unit_dir, rec.normal), 1.0);
            double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

            // check for total internal reflection
            vec3 dir;
            if (ri * sin_theta > 1.0 || reflectance(cos_theta, ri) > random_double()) {
                // total internal reflection
                dir = reflect(unit_dir, rec.normal);
            } else {
                // else refract
                dir = refract(unit_dir, rec.normal, ri);
            }
            
            scattered = ray(rec.p, dir);
            return true;
        }

    private:
        double refract_index;

        // Shlick's approximation for reflectance
        // idk how this works but RTIOW says it's good
        static double reflectance(double cos, double refract_index) {
            auto r0 = (1 - refract_index) / (1 + refract_index);
            r0 = r0 * r0;
            return r0 + (1 - r0) * pow((1 - cos), 5);
        }
};

#endif