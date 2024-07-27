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

#include "color.h"
#include "interval.h"
#include "ray.h"
#include "vec3.h"

#endif