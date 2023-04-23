//
// Created by Георгий Кузнецов on 17.04.2023.
//

#ifndef ENGINE_LOGIC_SRC_LOGIC_H_
#define ENGINE_LOGIC_SRC_LOGIC_H_

#include "resources.h"

class logic {
 public:
  logic();
  QPixmap* get_pixmap();
  int get_samples();
  std::pair<int, int> get_camera_rect();
  ~logic();

 private:
  Scene* cur_scene;
};

class sphere {
 public:
  sphere() = default;
  sphere(const point3& a, const double& b): center_(a), radius_(b) {}
  ~sphere() = default;

  point3 center_ = point3 (0, 0, 0);
  double radius_ = 0.0;
};
class triangle {
 public:
  triangle() = default;
  triangle(const point3& a, const point3& b, const point3& c) : v0(a), v1(b), v2(c) {}
  ~triangle() = default;

  point3 v0;
  point3 v1;
  point3 v2;
};
#endif //ENGINE_LOGIC_SRC_LOGIC_H_
