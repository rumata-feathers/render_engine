//
// Created by Георгий Кузнецов on 19.04.2023.
//

#ifndef ENGINE_MAINWINDOW_INC_RENDER_WINDOW_H_
#define ENGINE_MAINWINDOW_INC_RENDER_WINDOW_H_

#include "resources.h"

class RenderWindow : public QOpenGLWidget,
                      protected QOpenGLFunctions {
 public:
  explicit RenderWindow(QWidget* parent = nullptr);
};

#endif //ENGINE_MAINWINDOW_INC_RENDER_WINDOW_H_
