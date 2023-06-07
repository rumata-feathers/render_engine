#include "../inc/ray.h"

ray::ray(const point3& origin, const vec3& direction, double time): orig(origin), dir(direction), time(time) {}
vec3 ray::direction() const {
  return dir;
}
point3 ray::origin() const {
  return orig;
}
point3 ray::at(double t) const {
  return orig + t*dir;
}
double ray::get_time() const {
  return time;
}
ray::ray() = default;
ray::~ray() = default;
