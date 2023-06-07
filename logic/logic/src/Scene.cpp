//
// Created by Георгий Кузнецов on 12.04.2023.
//

#include "../inc/Scene.h"

#include <fstream>

Scene::Scene() = default;
int Scene::get_render_samples() const{
  return rend_samples;
}
camera Scene::get_camera() const {
  return camera_;
}
Scene::~Scene() = default;
hittable_list random_scene() {
  hittable_list world;

  auto ground_material = std::make_shared<BSDF>(color(0.5, 0.5, 0.5), 1, 0);
  world.add(std::make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

  for (int a = -11; a < 11; a++) {
    for (int b = -11; b < 11; b++) {
      auto choose_mat = random_double();
      point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

      if ((center - point3(4, 0.2, 0)).length() > 0.9) {
        std::shared_ptr<material> sphere_material;

        if (choose_mat < 0.8) {
          // diffuse
          auto albedo = color::random() * color::random();
          sphere_material = std::make_shared<BSDF>(albedo, 1, 0);
          world.add(std::make_shared<sphere>(center, 0.2, sphere_material));
          auto center2 = center + vec3(0, random_double(0,.5), 0);
          world.add(std::make_shared<moving_sphere>(
              center, center2, 0.0, 1.0, 0.2, sphere_material));
        } else if (choose_mat < 0.95) {
          // metal
          auto albedo = color::random(0.5, 1);
          auto fuzz = random_double(0, 0.5);
          sphere_material = std::make_shared<BSDF>(albedo, 0, 1, fuzz);
          world.add(std::make_shared<sphere>(center, 0.2, sphere_material));
        } else {
          // glass
          sphere_material = std::make_shared<BSDF>(color(0.8, 0.8, 0.8), 0, 0, 0, 1.5);
          world.add(std::make_shared<sphere>(center, 0.2, sphere_material));
        }
      }
    }
  }

  auto material1 = std::make_shared<BSDF>(color(1.0, 1.0, 1.0), 0, 0, 0, 1.5);;
  world.add(std::make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

  auto material2 = std::make_shared<BSDF>(color(0.4, 0.2, 0.1), 1, 0);
  world.add(std::make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

  auto material3 = std::make_shared<BSDF>(color(0.7, 0.6, 0.5), 0, 1, 0.0);
  world.add(std::make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

  return world;
}

