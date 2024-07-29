#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <limits>
#include <iostream>
#include <memory>

// file for random utilities

using std::make_shared;
using std::shared_ptr;
using std::sqrt;

const double pi = 3.1415926535897932385;

inline double degrees_to_rad(double degrees) {
    return degrees * pi / 180.0;
}

inline double random_double() {
    // random real in [0,1)
    return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
    // random real in [min,max)
    return min + (max-min)*random_double();
}

#include "color.h"
#include "interval.h"
#include "ray.h"
#include "vec3.h"

#endif