//
// Created by Георгий Кузнецов on 13.04.2023.
//

#include "../inc/interface.h"

interface::interface() {
  main_window_ = new MainWindow();
  main_window_->show();
}

void interface::set_pixmap(QPixmap* new_pixmap) {
  main_window_->set_pixmap(new_pixmap);
  main_window_->update();
}

interface::~interface() = default;
