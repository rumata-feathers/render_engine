//
// Created by Георгий Кузнецов on 17.04.2023.
//

#include "../inc/logic.h"
#include "../logic/inc/resources.h"
#include <thread>
#include <functional>

double hit_sphere(const sphere& s, const ray& r) {
  vec3 oc = r.origin() - s.center_;
  auto a = r.direction().length_squared();
  auto half_b = dot(oc, r.direction());
  auto c = oc.length_squared() - s.radius_ * s.radius_;
  auto discriminant = half_b * half_b - a * c;
  if (discriminant < 0) {
    return -1.0;
  } else {
    return (-half_b - std::sqrt(discriminant)) / (a);
  }
}

bool hit_triangle(const triangle& tr, const ray& r) {
  return true;
}

logic::logic() : cur_scene(new Scene) {
  world.add(std::make_shared<sphere>(point3(0,0,-1), 0.5));
  world.add(std::make_shared<sphere>(point3(0,-100.5,-1), 100));
}

color ray_color(const ray& r, const hittable& world) {
  hit_record record;
  if (world.hit(r, 0, infinity, record)) {
    return 0.5 * (record.normal + color(1,1,1));
  }
  auto t = 0.5 * (unit_vector(r.direction()).y() + 1.0);
  return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}
QPixmap* logic::get_pixmap() {
  auto cur_camera = cur_scene->get_camera();
  auto* pix_map = new QPixmap(cur_camera.img_w(), cur_camera.img_h());
  QImage image = pix_map->toImage();

  // image is divided into
//  std::cout << std::thread::hardware_concurrency();

//  std::vector<std::thread*> threads(std::thread::hardware_concurrency());
  std::vector<std::thread*> threads;

  for (int j = 0; j < cur_camera.img_h(); ++j) {
    auto* thread = new std::thread([&, j] {

      for (int k = 0; k < cur_camera.img_w(); ++k) {
        auto u = double(k + random_double()) / (cur_camera.img_w() - 1);
        auto v = double(cur_camera.img_h() - j + random_double()) / (cur_camera.img_h() - 1);
        ray r = cur_camera.get_ray(u, v);
        color pixel_color = ray_color(r, world);
        image.setPixelColor(k, j, pixel_color);
      }
    });
    threads.push_back(thread);
  }

  for (auto* th : threads) {
    th->join();
    delete th;
  }

  *pix_map = QPixmap::fromImage(image);
//  std::cerr << "finish get_pixmap\n";
  return pix_map;
}
int logic::get_samples() {
  return cur_scene->get_render_samples();
}
std::pair<int, int> logic::get_camera_rect() {
  return cur_scene->get_camera().size();
}
logic::~logic() = default;