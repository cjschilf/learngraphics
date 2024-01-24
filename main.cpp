#include "color.h"
#include "vec3.h"

#include <iostream>

int main() {
  // img dimensions
  int img_width = 256;
  int img_height = 256;

  // render
  std::cout << "P3\n" << img_width << ' ' << img_height << "\n255\n";

  for (int i = 0; i < img_height; i++) {
    // progress indicator
    std::clog << "\rScanlines remaining: " << img_height - i << ' ' << std::flush;
    for (int j = 0; j < img_width; j++) {
      auto pixel_color = color(double(j)/(img_width-1), double(i)/(img_height-1), 0.25);
      write_color(std::cout, pixel_color);
    }

    std::clog << "\nDone.\n";
  }
}