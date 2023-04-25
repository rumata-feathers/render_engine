//
// Created by Георгий Кузнецов on 17.04.2023.
//

#ifndef ENGINE_LOGIC_SRC_LOGIC_H_
#define ENGINE_LOGIC_SRC_LOGIC_H_

#include "resources.h"
#include "../logic/inc/resources.h"

class logic {
 public:
  logic();
  QPixmap* get_pixmap();
  int get_samples();
  std::pair<int, int> get_camera_rect();
  ~logic();

 private:
  Scene* cur_scene;
  hittable_list world;
};
#endif //ENGINE_LOGIC_SRC_LOGIC_H_
