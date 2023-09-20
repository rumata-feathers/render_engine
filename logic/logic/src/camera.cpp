//
// Created by Георгий Кузнецов on 21.04.2023.
//

#include "../inc/camera.h"

camera::camera() {
  img_height = static_cast<int>((float) img_width / aspect_ratio);
  auto viewport_height = 2.0;
  auto viewport_width = viewport_height * aspect_ratio;

  horizontal = vec3(viewport_width, 0.0, 0.0);
  vertical = vec3(0.0, viewport_height, 0.0);
  llc = position - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);
}
point3 camera::pos() const {
  return position;
}
void camera::set_pos(const point3& other_position) {
  position = other_position;
}
vec3 camera::rot() const {
  return rotation;
}
void camera::set_rot(vec3& other_rotation) {
  rotation = other_rotation;
}
std::vector<vec3> camera::axes() const {
  std::vector<vec3> axis{
      vec3(1.0, 0.0, 0.0),
      vec3(0.0, 1.0, 0.0),
      vec3(0.0, 0.0, 1.0)
  };

  std::vector<vec3> x_mat{
      vec3(1.0, 0.0, 0.0),
      vec3(0.0, cos(rotation.x_angle()), -sin(rotation.x_angle())),
      vec3(0.0, sin(rotation.x_angle()), cos(rotation.x_angle()))
  };

  std::vector<vec3> y_mat{
      vec3(cos(rotation.y_angle()), 0.0, sin(rotation.y_angle())),
      vec3(0.0, 1.0, 0.0),
      vec3(-sin(rotation.y_angle()), 0.0, cos(rotation.y_angle()))
  };

  std::vector<vec3> z_mat{
      vec3(cos(rotation.z_angle()), -sin(rotation.z_angle()), 0.0),
      vec3(sin(rotation.z_angle()), cos(rotation.z_angle()), 0.0),
      vec3(0.0, 0.0, 1.0)
  };

  axis = mat_mul(axis, x_mat);
  axis = mat_mul(axis, y_mat);
  axis = mat_mul(axis, z_mat);

  axis[0].normalize();
  axis[1].normalize();
  axis[2].normalize();
  return axis;
}
vec3 camera::hor_axis() const {
  return horizontal;
}
vec3 camera::ver_axis() const {
  return vertical;
}
vec3 camera::get_llc() const {
  return llc;
}
float camera::focal_len() const {
  return focal_length;
}
void camera::set_focal_len(float other) {
  focal_length = other;
}
std::pair<int, int> camera::size() const {
  return {img_width, img_height};
}
int camera::img_w() const {
  return img_width;
}
void camera::set_img_w(int other) {
  img_width = other;
}
int camera::img_h() const {
  return img_height;
}
void camera::set_img_h(int other) {
  img_height = other;
}
ray camera::get_ray(double s, double t) const {
  vec3 rd = lens_radius * random_in_unit_disk();
  vec3 offset = u * rd.x() + v * rd.y();

  return {position + offset, llc + s * horizontal + t * vertical - position - offset,
          random_double(time_start, time_end)};
}
camera::camera(const point3& lookfrom, const point3& lookat, const vec3& vup, double vfov, double aspect_ratio)
    : position(lookfrom) {
  auto theta = degrees_to_radians(vfov);
  auto h = tan(theta / 2);
  auto viewport_height = 2.0 * h;
  auto viewport_width = aspect_ratio * viewport_height;

  w = unit_vector(lookfrom - lookat);
  u = unit_vector(cross(vup, w));
  v = cross(w, u);

  img_height = static_cast<int>((float) img_width / aspect_ratio);

  position = lookfrom;
  horizontal = viewport_width * u;
  vertical = viewport_height * v;
  llc = position - horizontal / 2 - vertical / 2 - w;
}
camera::camera(
    const point3& lookfrom,
    const point3& lookat,
    const vec3& vup,
    double vfov, // vertical field-of-view in degrees
    double aspect_ratio,
    double aperture,
    double focus_dist,
    double tm_start,
    double tm_end
              ) {
  auto theta = degrees_to_radians(vfov);
  auto h = tan(theta/2);
  auto viewport_height = 2.0 * h;
  auto viewport_width = aspect_ratio * viewport_height;

  w = unit_vector(lookfrom - lookat);
  u = unit_vector(cross(vup, w));
  v = cross(w, u);

  position = lookfrom;
  horizontal = focus_dist * viewport_width * u;
  vertical = focus_dist * viewport_height * v;
  llc = position - horizontal/2 - vertical/2 - focus_dist*w;

  lens_radius = aperture / 2;
  time_start = tm_start;
  time_end = tm_end;
  img_height = static_cast<int>((float) img_width / aspect_ratio);
}
camera::~camera() = default;
