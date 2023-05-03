//
// Created by Георгий Кузнецов on 17.04.2023.
//

#ifndef ENGINE_LOGIC_SRC_LOGIC_H_
#define ENGINE_LOGIC_SRC_LOGIC_H_

#include "resources.h"
#include "../logic/inc/resources.h"
#include "../logic/inc/hittable_list.h"

class logic {
 public:
  logic();
  QImage* get_pixmap(QImage* pixmap = nullptr, int sample = 0, std::pair<int, int> start = {0, 0}, std::pair<int, int> end = {-1, -1});
  int get_samples();
  std::pair<int, int> get_camera_rect();
  ~logic();

 private:
  Scene* cur_scene;
  hittable_list world;
};
#endif //ENGINE_LOGIC_SRC_LOGIC_H_
