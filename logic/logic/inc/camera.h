//
// Created by Георгий Кузнецов on 21.04.2023.
//

#ifndef ENGINE_LOGIC_LOGIC_INC_CAMERA_H_
#define ENGINE_LOGIC_LOGIC_INC_CAMERA_H_

#include "vector3.h"
#include "ray.h"

class camera {
 public:
  camera();
  // get camera position
  [[nodiscard]] point3 pos() const;
  // set camera position
  void set_pos(point3&);
  // get camera rotation
  [[nodiscard]] vec3 rot() const;
  // set camera rotation
  void set_rot(vec3&);

  // get new axes of the camera
  [[nodiscard]] vector3<vec3> axes() const;

  // get horizontal axis of the image
  [[nodiscard]] vec3 hor_axis() const;
  // get vertical axis of the image
  [[nodiscard]] vec3 ver_axis() const;
  // get normal axis of the image
  [[nodiscard]] vec3 norm_axis() const;
  // get lower left corner of the image
  [[nodiscard]] vec3 get_llc() const;

  // get camera focal length
  [[nodiscard]] float focal_len() const;
  // set camera focal length
  void set_focal_len(float other);


  // get image size {width, height}
  [[nodiscard]] std::pair<int, int> size() const;
  // get image width
  [[nodiscard]] int img_w() const;
  // set image width
  void set_img_w(int other);
  // get image height
  [[nodiscard]] int img_h() const;
  // set image height
  void set_img_h(int other);

  ray get_ray(double u, double v);

  ~camera();

 private:
  point3 position;
  vec3 rotation;
  float aspect_ratio;
  int img_width;
  int img_height;

  float viewport_height;
  float viewport_width;
  float focal_length;
};

#endif //ENGINE_LOGIC_LOGIC_INC_CAMERA_H_
