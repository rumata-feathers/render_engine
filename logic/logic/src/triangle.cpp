//
// Created by Георгий Кузнецов on 24.04.2023.
//

#include "../inc/triangle.h"
triangle::triangle() = default;
triangle::triangle(const point3& v0, const point3& v1, const point3& v2) : v0(v0), v1(v1), v2(v2) {}
bool triangle::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
  // equation:
  // t^2*b^2 + 2t*b⋅(A-C)+(A-C)⋅(A-C)−𝑟^2 = 0

  // find (x - Cx) for every coordinate
//  vec3 oc = r.origin() - center_;
  // a of the quadratic equation
//  auto a = r.direction().length_squared();
  // half_b = (A-C)*(A-C)
//  auto half_b = dot(oc, r.direction());
  // c = (A-C)⋅(A-C)−𝑟^2
//  auto c = oc.length_squared() - radius_ * radius_;
//  auto discriminant = half_b * half_b - a * c;
//  if (discriminant < 0)
//    return false;
  // there are roots
  // check if they get in the borders
//  auto root = (-half_b - std::sqrt(discriminant)) / (a);
//  if (root < t_min || t_max < root) {
    // try another root
//    root = (-half_b + std::sqrt(discriminant)) / (a);
//    if (root < t_min || t_max < root)
      return false;
//  }
  // there is collision
//  rec.t = root;
//  rec.p = r.at(rec.t);
//  vec3 outward_normal = (rec.p - center_) / radius_;
//  rec.set_face_normal(r, outward_normal);

//  return true;
}
triangle::~triangle() = default;

