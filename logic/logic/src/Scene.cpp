//
// Created by Георгий Кузнецов on 12.04.2023.
//

#include "../inc/Scene.h"
Scene::Scene() = default;
int Scene::get_render_samples() const{
  return rend_samples;
}
camera Scene::get_camera() const {
  return camera_;
}
Scene::~Scene() = default;
