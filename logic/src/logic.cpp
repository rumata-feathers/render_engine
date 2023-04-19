//
// Created by Георгий Кузнецов on 17.04.2023.
//

#include "../inc/logic.h"

logic::logic(): cur_scene(new Scene) {};

QPixmap* logic::get_pixmap() {
  QTime cur_time = QTime::currentTime();
  auto* pix_map = new QPixmap(100, 100);
  pix_map->fill(QColor(rand()%255, rand()%255, rand()%255));
  return pix_map;
}
int logic::get_samples() {
  return 1000;
}
std::pair<int, int> logic::get_camera_rect() {
  return {100, 100};
}

logic::~logic() = default;