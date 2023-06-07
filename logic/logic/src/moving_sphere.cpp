//
// Created by Георгий Кузнецов on 02.06.2023.
//

#include "../inc/moving_sphere.h"
moving_sphere::moving_sphere(const point3& center_s, const point3& center_e, double t_s, double t_e,
                             double r, std::shared_ptr<material> mat) :
    pos_start(center_s), pos_end(center_e), time_start(t_s), time_end(t_e), radius(r), mat_ptr(mat) {}

point3 moving_sphere::center(double time) const {
  return pos_start + ((time - time_start) / (time_end - time_start)) * (pos_end - pos_start);
}
bool moving_sphere::hit(const ray& r, double t_min, double t_max, hit_record& record) const {
  vec3 oc = r.origin() - center(r.get_time());
  auto a = r.direction().length_squared();
  auto half_b = dot(oc, r.direction());
  auto c = oc.length_squared() - radius * radius;

  auto discriminant = half_b * half_b - a * c;
  if (discriminant < 0) return false;
  auto sqrtd = sqrt(discriminant);

  // Find the nearest root that lies in the acceptable range.
  auto root = (-half_b - sqrtd) / a;
  if (root < t_min || t_max < root) {
    root = (-half_b + sqrtd) / a;
    if (root < t_min || t_max < root)
      return false;
  }

  record.t = root;
  record.p = r.at(record.t);
  auto outward_normal = (record.p - center(r.get_time())) / radius;
  record.set_face_normal(r, outward_normal);
  record.mat_ptr = mat_ptr;

  return true;
}