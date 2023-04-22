//
// Created by Георгий Кузнецов on 12.04.2023.
//

#ifndef ENGINE_LOGIC_SCENES_SRC_SCENE_H_
#define ENGINE_LOGIC_SCENES_SRC_SCENE_H_

#include <string>
#include "camera.h"

class Scene {
 public:
  int get_render_samples() const;
  camera get_camera() const;

  Scene();
  ~Scene();
 private:
  std::string name;
  std::string location;
  std::unordered_map<std::string, std::string> objects;
  camera camera_;
  int rend_samples;
};

#endif //ENGINE_LOGIC_SCENES_SRC_SCENE_H_
