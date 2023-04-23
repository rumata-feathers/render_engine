//
// Created by Георгий Кузнецов on 17.04.2023.
//

#include "../inc/logic.h"
#include <thread>
#include <functional>

double hit_sphere(const sphere& s, const ray& r) {
  vec3 oc = r.origin() - s.center_;
  auto a = dot(r.direction(), r.direction());
  auto b = 2.0 * dot(oc, r.direction());
  auto c = dot(oc, oc) - s.radius_ * s.radius_;
  auto discriminant = b * b - 4 * a * c;
  if (discriminant < 0) {
    return -1.0;
  } else {
    return (-b - sqrt(discriminant)) / (2.0 * a);
  }
}

bool hit_triangle(const triangle& tr, const ray& r) {
  return true;
}

logic::logic() : cur_scene(new Scene) {}

color ray_color(const ray& r) {
  sphere s(point3(0, 0, -1), 0.4);
  auto dist = hit_sphere(s, r);
  if (dist > 0.0) {
    vec3 N = unit_vector(r.at(dist) - s.center_);
    return s.radius_ * color(N.x() + 1, N.y() + 1, N.z() + 1);
  }

  auto t = 0.5 * (unit_vector(r.direction()).y() + 1.0);
  return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}
QPixmap* logic::get_pixmap() {
  auto cur_camera = cur_scene->get_camera();
  auto* pix_map = new QPixmap(cur_camera.img_w(), cur_camera.img_h());
  QImage image = pix_map->toImage();
  image.fill(Qt::darkCyan);
  std::vector<std::thread*> threads;

  for (int j = 0; j < cur_camera.img_h(); ++j) {
    auto* thread = new std::thread([&cur_camera, &image, j] {

      for (int k = 0; k < cur_camera.img_w(); ++k) {
        auto u = double(k) / (cur_camera.img_w() - 1);
        auto v = double(j) / (cur_camera.img_h() - 1);
        ray r(cur_camera.pos(),
              cur_camera.get_llc() + u * cur_camera.hor_axis() + v * cur_camera.ver_axis() - cur_camera.pos());
        color pixel_color = ray_color(r);
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