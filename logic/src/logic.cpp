//
// Created by Георгий Кузнецов on 17.04.2023.
//

#include "../inc/logic.h"
#include <thread>
#include <functional>
#include <pthread.h>


logic::logic() : cur_scene(new Scene) {}

color ray_color(const ray& r) {
  vec3 unit_direction = unit_vector(r.direction());
  auto t = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

void print(int n, const std::string& str) {
  std::string msg = std::to_string(n) + " : " + str;
  std::cout << msg << std::endl;
}

QPixmap* logic::get_pixmap() {
  auto cur_camera = cur_scene->get_camera();
  auto* pix_map = new QPixmap(cur_camera.img_w(), cur_camera.img_h());
  QImage image = pix_map->toImage();

  std::vector<std::thread> threads;

  for (int j = 0; j < cur_camera.img_h(); ++j) {
    threads.emplace_back([&, j] {

      for (int k = 0; k < cur_camera.img_w(); ++k) {

        auto u = double(k) / (cur_camera.img_w() - 1);
        auto v = double(j) / (cur_camera.img_h() - 1);
//        ray r(cur_camera.pos(),
//              cur_camera.get_llc() + u * cur_camera.hor_axis() + v * cur_camera.ver_axis() - cur_camera.pos());
//        color pixel_color = ray_color(r);
//        image.setPixelColor(k, j, pixel_color);
//        std::cout << image.size().width() << ' ' << image.height()<< '\n';
        image.setPixelColor(k, j, QColor(Qt::darkMagenta));
      }
    });
//    threads.push_back(thread);
//    std::cout << j << '\n';
  }

  for (auto& th : threads) {
    if (th.joinable()) {
      th.join();
    }
//    std::cout << "destroying " << th << "\n";
//    delete th;
  }
  threads.clear();

//  std::for_each(threads.begin(), threads.end(), [](std::thread* i) {std::cout << i << '\n';});


  *pix_map = QPixmap::fromImage(image);
  std::cerr << "finish get_pixmap\n";
  return pix_map;
}
int logic::get_samples() {
  return cur_scene->get_render_samples();
}
std::pair<int, int> logic::get_camera_rect() {
  return cur_scene->get_camera().size();
}

logic::~logic() = default;