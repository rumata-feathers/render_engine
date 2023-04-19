//
// Created by Георгий Кузнецов on 12.04.2023.
//

#ifndef ENGINE_LOGIC_SCENES_SRC_SCENE_H_
#define ENGINE_LOGIC_SCENES_SRC_SCENE_H_

#include <string>

class Scene {
 public:
  Scene();
  ~Scene();
 private:
  std::string name;
  std::string location;
  std::unordered_map<std::string, std::string> objects;
};

#endif //ENGINE_LOGIC_SCENES_SRC_SCENE_H_
