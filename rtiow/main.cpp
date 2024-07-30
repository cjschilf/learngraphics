#include "rtweekend.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"

color ray_color(const ray& r, const hittable& world) {
  hit_record rec;
  if (world.hit(r, interval(0, infinity), rec)) {
    return 0.5 * (rec.normal + color(1,1,1));
  }

  // lerp between blue and white based on ray direction
  // looks like sky gradient
  vec3 unit_dir = unit_vector(r.direction());
  auto a = 0.5 * (unit_dir.y() + 1.0);
  return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}

int main() {
  // 'world' of hittable objects
  hittable_list world;

  auto mat_ground = make_shared<lambertian>(color(0.5, 0.8, 0.0));
  auto mat_matte_blue = make_shared<lambertian>(color(0.1, 0.2, 0.5));
  auto mat_metal_blue = make_shared<metal>(color(0.2, 0.2, 0.8), 0.2);
  auto mat_metal_red = make_shared<metal>(color(0.8, 0.2, 0.2), 0.5);

  world.add(make_shared<sphere>(point3(0,0,-1), 0.5, mat_matte_blue));
  world.add(make_shared<sphere>(point3(0,-100.5,-1), 100, mat_ground));
  world.add(make_shared<sphere>(point3(-1.0,0.0,-1.0), 0.5, mat_metal_blue));
  world.add(make_shared<sphere>(point3(1.0,0.0,-1.0), 0.5, mat_metal_red));


  camera world_cam;

  world_cam.aspect_ratio = 16.0 / 9.0;
  world_cam.image_width = 400;
  world_cam.samples_per_pixel = 100; // 100 samples per pixel, controls degree of anti-aliasing
  world_cam.max_depth = 25; // max ray recursion depth

  world_cam.render(world);
}
