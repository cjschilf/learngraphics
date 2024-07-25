#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class sphere : public hittable {
    private:
        point3 center;
        double radius;

    public:
        sphere(const point3& center, double radius) : center(center), radius(fmax(0.0,radius)) {}

        bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const override {
            vec3 oc = center - r.origin();
            auto a = r.direction().length_squared();
            auto h = dot(r.direction(), oc);
            auto c = oc.length_squared() - radius*radius;

            auto discriminant = h*h - a*c;
            if (discriminant < 0) {
                return false;
            }

            auto sqrt_d = sqrt(discriminant);

            // find nearest root in acceptable range
            auto root = (h - sqrt_d) / a;
            if (root <= ray_tmin || ray_tmax <= root) {
                root = (h + sqrt_d) / a;
                if (root <= ray_tmin || ray_tmax <= root) {
                    return false;
                }
            } 

            // update hit record
            rec.t = root;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);

            return true;
        }
};

#endif