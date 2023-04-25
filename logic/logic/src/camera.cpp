//
// Created by Георгий Кузнецов on 21.04.2023.
//

#include "../inc/camera.h"
#include "vector3.cpp"

camera::camera() {
  position = point3(0.0, 0.0, 0.0);
  rotation = vec3(0.0, 0.0, 0.0);
  aspect_ratio = 16.0 / 9.0;
  img_width = 120;
  img_height = static_cast<int>((float) img_width / aspect_ratio);
  viewport_height = 2.0;
  viewport_width = viewport_height * aspect_ratio;
  focal_length = 1.0;
}
point3 camera::pos() const {
  return position;
}
void camera::set_pos(point3& other_position) {
  position = other_position;
}
vec3 camera::rot() const {
  return rotation;
}
void camera::set_rot(vec3& other_rotation) {
  rotation = other_rotation;
}
vector3<vec3> camera::axes() const {
  vector3<vec3> axis(
      vec3(1.0, 0.0, 0.0),
      vec3(0.0, 1.0, 0.0),
      vec3(0.0, 0.0, 1.0)
  );

  vector3<vec3> x_mat{
      vec3(1.0, 0.0, 0.0),
      vec3(0.0, cos(rotation.x_angle()), -sin(rotation.x_angle())),
      vec3(0.0, sin(rotation.x_angle()), cos(rotation.x_angle()))
  };

  vector3<vec3> y_mat{
      vec3(cos(rotation.y_angle()), 0.0, sin(rotation.y_angle())),
      vec3(0.0, 1.0, 0.0),
      vec3(-sin(rotation.y_angle()), 0.0, cos(rotation.y_angle()))
  };

  vector3<vec3> z_mat{
      vec3(cos(rotation.z_angle()), -sin(rotation.z_angle()), 0.0),
      vec3(sin(rotation.z_angle()), cos(rotation.z_angle()), 0.0),
      vec3(0.0, 0.0, 1.0)
  };

  axis = mat_mul(axis, x_mat);
  axis = mat_mul(axis, y_mat);
  axis = mat_mul(axis, z_mat);

  axis.x().normalize();
  axis.y().normalize();
  axis.z().normalize();
  return axis;
}
vec3 camera::norm_axis() const {
  return (double) focal_length * axes().z();
}
vec3 camera::hor_axis() const {
  return (double) viewport_width * axes().x();
}
vec3 camera::ver_axis() const {
  return (double) viewport_height * axes().y();
}
vec3 camera::get_llc() const {
  return position - hor_axis() / 2.0 - ver_axis() / 2.0 - norm_axis();
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
ray camera::get_ray(double u, double v) {
  return ray(position, get_llc() + u*hor_axis() + v*ver_axis() - position);
}
camera::~camera() = default;
