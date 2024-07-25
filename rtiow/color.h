#ifndef COLOR_H
#define COLOR_H

#include "rtweekend.h"
#include "vec3.h"

using color = vec3;

void write_color(std::ostream &out, color pixel_color) {
  // write value of each component, assuming input is a vec3 of 0-1 vals
  out << static_cast<int>(255.999 * pixel_color.x()) << ' '
      << static_cast<int>(255.999 * pixel_color.y()) << ' '
      << static_cast<int>(255.999 * pixel_color.z()) << '\n';
}

#endif 