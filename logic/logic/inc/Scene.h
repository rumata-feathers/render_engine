//
// Created by Георгий Кузнецов on 12.04.2023.
//

#ifndef ENGINE_LOGIC_SCENES_SRC_SCENE_H_
#define ENGINE_LOGIC_SCENES_SRC_SCENE_H_

#include <string>
#include "camera.h"
#include "resources.h"
#include "hittable_list.h"
#include "sphere.h"
#include "moving_sphere.h"

class Scene {
 public:
  int get_render_samples() const;
  camera get_camera() const;

  Scene();
  Scene(const camera& cam) : camera_(cam) {}
  void set_camera(const camera& cam) { camera_ = cam; }
  ~Scene();

  int rend_samples = 3;
  int max_depth = 5;

  camera camera_;
 private:
  std::string name;
  std::string location;
  std::unordered_map<std::string, std::string> objects;

  int sample_x = 32;
  int sample_y = 32;
};

hittable_list random_scene();


#endif //ENGINE_LOGIC_SCENES_SRC_SCENE_H_
