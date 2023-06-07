//
// Created by Георгий Кузнецов on 21.04.2023.
//

#ifndef ENGINE_LOGIC_LOGIC_INC_CAMERA_H_
#define ENGINE_LOGIC_LOGIC_INC_CAMERA_H_

#include "resources.h"

class camera {
 public:
  camera();
  camera(double vfov, // vertical field-of-view in degrees
         double aspect_ratio);
  camera(const point3& lookfrom,
         const point3& lookat,
         const vec3& vup,
         double vfov, // vertical field-of-view in degrees
         double aspect_ratio);
  camera(const camera& other) = default;
  camera(
      const point3& lookfrom,
      const point3& lookat,
      const vec3& vup,
      double vfov, // vertical field-of-view in degrees
      double aspect_ratio,
      double aperture,
      double focus_dist,
      double tm_start = 0.0,
      double tm_end = 0.0
        );
  // get camera position
  [[nodiscard]]
  point3 pos() const;
  // set camera position
  void set_pos(const point3&);
  // get camera rotation
  [[nodiscard]] vec3 rot() const;
  // set camera rotation
  void set_rot(vec3&);

  // get new axes of the camera
  [[nodiscard]] std::vector<vec3> axes() const;

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

  ray get_ray(double, double) const;

  camera& operator=(const camera& other) = default;

  ~camera();

 private:
  point3 position = point3(0.0, 0.0, 0.0);
  vec3 rotation = point3(0.0, 0.0, 0.0);
  point3 llc;
  float aspect_ratio = 16.0 / 9.0;
  int img_width = 80;
  int img_height;

  vec3 horizontal;
  vec3 vertical;
  float focal_length = 1.0;

  double time_start = 0.0;
  double time_end = 0.0;

  //TODO
  vec3 u, v, w;
  double lens_radius;
};

#endif //ENGINE_LOGIC_LOGIC_INC_CAMERA_H_
