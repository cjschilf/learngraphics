#include "rtweekend.h"

#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

color ray_color(const ray& r, const hittable& world) {
  hit_record rec;
  if (world.hit(r, 0, infinity, rec)) {
    return 0.5 * (rec.normal + color(1,1,1));
  }

  // lerp between blue and white based on ray direction
  // looks like sky gradient
  vec3 unit_dir = unit_vector(r.direction());
  auto a = 0.5 * (unit_dir.y() + 1.0);
  return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}

int main() {

  // img dimensions
  auto aspect_ratio = 16.0 / 9.0;
  int img_width = 400;

  // calculate img height from aspect ratio + width
  int img_height = int(img_width / aspect_ratio);
  img_height = (img_height < 1) ? 1 : img_height; // height must be 1 or greater

  // 'world' of hittable objects
  hittable_list world;
  world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
  world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

  // camera stuff
  auto focal_length = 1.0;
  auto viewport_height = 2.0;
  auto viewport_width = viewport_height * (double(img_width) / img_height);
  auto camera_origin = point3(0,0,0);

  // viewport vectors
  auto viewport_u = vec3(viewport_width, 0, 0); // runs along the top of viewport, points right
  auto viewport_v = vec3(0, -viewport_height, 0); // runs along the side of viewport, points down

  // horizontal and vertical delta vectors from pixel to pixel
  auto pixel_delta_u = viewport_u / img_width;
  auto pixel_delta_v = viewport_v / img_height;

  // upper left corner of viewport
  auto viewport_upper_left = camera_origin - vec3(0,0,focal_length) - viewport_u/2 - viewport_v/2;
  auto pixel00 = viewport_upper_left + 0.5*pixel_delta_u + 0.5*pixel_delta_v; // center of pixel 0,0

  // render
  std::cout << "P3\n" << img_width << ' ' << img_height << "\n255\n";

  for (int i = 0; i < img_height; i++) {
    // progress indicator
    std::clog << "\rScanlines remaining: " << img_height - i << ' ' << std::flush;
    for (int j = 0; j < img_width; j++) {
      auto pixel_center = pixel00 + j*pixel_delta_u + i*pixel_delta_v;
      auto ray_dir = pixel_center - camera_origin;
      ray r(camera_origin, ray_dir);

      color pixel_color = ray_color(r, world);
      write_color(std::cout, pixel_color);
    }

    std::clog << "\nDone.\n";
  }
}