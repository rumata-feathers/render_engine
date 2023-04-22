//
// Created by Георгий Кузнецов on 21.04.2023.
//

#include "../inc/ray.h"

ray::ray() = default;
ray::ray(const point3& origin, const vec3& direction) {

}
vec3 ray::direction() const {
  return dir;
}
point3 ray::origin() const {
  return orig;
}
point3 ray::at(double t) const {
  return orig + t*dir;
}
ray::~ray() = default;
