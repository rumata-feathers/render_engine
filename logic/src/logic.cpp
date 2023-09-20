//
// Created by Георгий Кузнецов on 17.04.2023.
//

#include "../inc/logic.h"

logic::logic(): cur_scene(new Scene) {};

<<<<<<< Updated upstream
QPixmap* logic::get_pixmap() {
  QTime cur_time = QTime::currentTime();
  auto* pix_map = new QPixmap(100, 100);
  pix_map->fill(QColor(rand()%255, rand()%255, rand()%255));
=======
using namespace std::chrono;

QColor q_color(const vec3& col) {
  QColor color_;
  color_.setRedF((float) col.x());
  color_.setGreenF((float) col.y());
  color_.setBlueF((float) col.z());
  color_.setAlpha(255);
  return color_;
}

logic::logic() : cur_scene(new Scene()) {

//  std::cout << object_reader(world, "/Users/georgiikuznetsov/Desktop/coding/engine/logic/scenes/Scene Monkey/monkey.obj");
//  std::cout << object_reader(world, "/Users/georgiikuznetsov/Desktop/coding/engine/logic/scenes/Scene0/cube.obj");
  point3 lookfrom(13, 2, 3);
  point3 lookat(0, 0, 0);
  vec3 vup(0, 1, 0);
  auto dist_to_focus = 10.0;
  auto aperture = 0.1;
  auto aspect_ratio = 16.0 / 9.0;

  cur_scene->camera_ = camera(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);
//  cur_scene->camera_.set_pos(point3(0.0, 1.0, 0.0));
  world = random_scene();
  auto material_ground = std::make_shared<BSDF>(color(0.8, 0.8, 0.0), 1, 0);
//  auto material_center = std::make_shared<BSDF>(color(0.1, 0.2, 0.5), 0.7f, 0.3f);
//  auto material_left = std::make_shared<BSDF>(color(0.8, 0.8, 0.8), 0, 0, 0, 1.0);
//  auto material_right = std::make_shared<BSDF>(color(0.8, 0.6, 0.2), 0, 1, 0.7f);
//  world.add(std::make_shared<sphere>(point3(0, -100.5, -1), 100, material_ground));
//  world.add(std::make_shared<triangle>(point3(.5, 1, .5), point3(.5, .5, 1), point3(1, .5, .5), material_center));
//  world.add(std::make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
//  world.add(std::make_shared<sphere>(point3(-1.0, 0.0, -1.0), -0.4, material_left));
//  world.add(std::make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));
}

color ray_color(const ray& r, const hittable& world, int depth) {
  // hit point
  hit_record record;

  // If we've exceeded the ray bounce limit, no more light is gathered.
  if (depth <= 0)
    return {0, 0, 0};

  // count hitting
  if (world.hit(r, 0.001, infinity, record)) {
    ray scattered;
    color attenuation;
    if (record.mat_ptr->scatter(r, record, attenuation, scattered))
      return attenuation * ray_color(scattered, world, depth - 1);

    return {0, 0, 0};
  }
  auto t = 0.5 * (unit_vector(r.direction()).y() + 1.0);
  return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}
int get_pixel_pos(int x, int y, int width, int height, int depth = 3) {
  return ((height - y) * width + x) * depth;
}
QImage* logic::get_pixmap(QImage* pix_map, int sample, std::pair<int, int> start, std::pair<int, int> end) {
  auto cur_camera = cur_scene->get_camera();
  if (end == std::make_pair(-1, -1)) {
    end = {cur_camera.img_w(), cur_camera.img_h()};
  }

  if (pix_map == nullptr)
    pix_map = new QImage((int) cur_camera.img_w(), (int) cur_camera.img_h(), QImage::Format_RGB32);
//  return pix_map;
  bool complete = false;
  int cell_w = end.first - start.first;
  int cell_h = end.second - start.second;
//  int max_threads = (int) std::thread::hardware_concurrency();
  int max_threads = 4;
  // how much to give for the thread
  int thread_cell_w = std::floor((double) cell_w / (double) max_threads);
  int thread_cell_h = std::floor((double) cell_h / (double) max_threads);

  std::vector<std::thread*> threads;
  // coefficient for old pixel
  double old_multiplier = (float) sample / ((float) sample + 1);
  // coefficient for new pixel
  double new_multiplier = 1 / ((float) sample + 1);

  try {
    for (int thread_num = 0; thread_num < max_threads; ++thread_num) {
      int y_start = (int) start.second + thread_num * thread_cell_h;
      int y_end = (thread_num == max_threads - 1) ? end.second : (int) start.second + (thread_num + 1) * thread_cell_h;

      auto* thread = new std::thread([&, y_start, y_end] {
        for (int j = y_start; j < y_end; ++j) {

          // vertical offset of the casting ray
          auto v = double(cur_camera.img_h() - j + random_double()) / (cur_camera.img_h() - 1);

          for (int k = start.first; k < end.first; ++k) {
            auto u = double(k + random_double()) / (cur_camera.img_w() - 1);
            ray r = cur_camera.get_ray(u, v);
            color pixel_color = ray_color(r, world, cur_scene->get_camera().max_depth);

            auto old_pix = pix_map->pixelColor(k, j);
            pixel_color *= new_multiplier;
            pixel_color[0] += old_pix.redF() * old_multiplier;
            pixel_color[1] += old_pix.greenF() * old_multiplier;
            pixel_color[2] += old_pix.blueF() * old_multiplier;
            pix_map->setPixelColor(k, j, q_color(pixel_color));
          }
        }
      });
      threads.push_back(thread);
    }
    for (auto* th : threads) {
      if (th->joinable()) {
        th->join();
      }
      delete th;
    }
  } catch (...) {
    std::cerr << "got exception in logic::get_pixmap\n";
    for (auto* th : threads) {
      delete th;
    }
  }
  return pix_map;
}

float* logic::get_pixmap(float* pix_map, int sample, std::pair<int, int> start,
                         std::pair<int, int> end) {
  auto cur_camera = cur_scene->get_camera();
  if (end == std::make_pair(-1, -1)) {
    end = {cur_camera.img_w(), cur_camera.img_h()};
  }

// coefficient for old pixel
  double old_multiplier = (float) sample / ((float) sample + 1);
  // coefficient for new pixel
  double new_multiplier = 1 / ((float) sample + 1);

  if (pix_map == nullptr) {
    pix_map = new float[cur_camera.img_w() * cur_camera.img_h() * 3];
    for (int i = 0; i < cur_camera.img_w() * cur_camera.img_h() * 3; ++i) {
      pix_map[i] = 0;
    }
    return pix_map;
    old_multiplier = 0;
    new_multiplier = 1;
  }

  int pixmap_width = cur_camera.img_w();
  int pixmap_height = cur_camera.img_h();
  bool complete = false;
  int cell_w = end.first - start.first;
  int cell_h = end.second - start.second;
//  int max_threads = (int) std::thread::hardware_concurrency();
  int max_threads = 8;
  // how much to give for the thread
  int thread_cell_w = std::floor((double) cell_w / (double) max_threads);
  int thread_cell_h = std::floor((double) cell_h / (double) max_threads);

  std::vector<std::thread*> threads;
  double multiplier = (double) 1 / get_samples();

  try {
    for (int thread_num = 0; thread_num < max_threads; ++thread_num) {
      int y_start = (int) start.second + thread_num * thread_cell_h;
      int y_end = (thread_num == max_threads - 1) ? end.second : (int) start.second + (thread_num + 1) * thread_cell_h;

      auto* thread = new std::thread([&, y_start, y_end] {
        for (int j = y_start; j < y_end; ++j) {

          // vertical offset of the casting ray
          auto v = double(cur_camera.img_h() - j + random_double()) / (cur_camera.img_h() - 1);

          for (int k = start.first; k < end.first; ++k) {
            auto u = double(k + random_double()) / (cur_camera.img_w() - 1);
            ray r = cur_camera.get_ray(u, v);
            color pixel_color = ray_color(r, world, cur_scene->get_camera().max_depth);

            pix_map[get_pixel_pos(k, j, pixmap_width, pixmap_height)] += pixel_color[0] * multiplier;
            pix_map[get_pixel_pos(k, j, pixmap_width, pixmap_height) + 1] += pixel_color[1] * multiplier;
            pix_map[get_pixel_pos(k, j, pixmap_width, pixmap_height) + 2] += pixel_color[2] * multiplier;
          }
        }
      });
      threads.push_back(thread);
    }
    for (auto* th : threads) {
      if (th->joinable()) {
        th->join();
      }
      delete th;
    }
  } catch (...) {
    std::cerr << "got exception in logic::get_pixmap\n";
    for (auto* th : threads) {
      delete th;
    }
  }
>>>>>>> Stashed changes
  return pix_map;
}
int logic::get_samples() {
  return 1000;
}
std::pair<int, int> logic::get_camera_rect() {
  return {100, 100};
}

logic::~logic() = default;