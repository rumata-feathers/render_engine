//
// Created by Георгий Кузнецов on 17.04.2023.
//
#include "../inc/Scene.h"
#include <iostream>
//#include <QImage>
#include "logic.h"


int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  Scene s1;
  auto cam = s1.get_camera();
  logic lc;
  auto pixmap = lc.get_pixmap();
  QImage smth = pixmap->toImage();
  for (int j = 0; j < smth.width(); ++j) {
    for (int k = 0; k < smth.height(); ++k) {
      std::cout << '(' << smth.pixelColor(j, k).redF() << ", " << smth.pixelColor(j, k).greenF() << ", " << smth.pixelColor(j, k).blueF() << ", " << smth.pixelColor(j, k).alphaF() << ") ";
//      ray r(cam.pos(),
//        cam.get_llc() + (double)j * cam.hor_axis() + (double)k * cam.ver_axis() - cam.pos());
    }
  }

//  std::cout << cam.get_llc() << '\n';
//  std::cout << cam.pos() << '\n';
//  std::cout << cam.hor_axis() << '\n';
//  std::cout << cam.ver_axis() << '\n';
  return 0;
}