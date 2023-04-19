//
// Created by Георгий Кузнецов on 13.04.2023.
//

#ifndef MAINWINDOW_FRONT_INTERFACE_H_
#define MAINWINDOW_FRONT_INTERFACE_H_

#include "front_resources.h"
#include <vector>

class interface {
 public:
  interface();
  ~interface();

  void set_pixmap(QPixmap* new_pixmap);

 private:
  MainWindow *main_window_;

};

#endif //MAINWINDOW_FRONT_INTERFACE_H_
