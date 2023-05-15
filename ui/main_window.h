//
// Created by Георгий Кузнецов on 13.04.2023.
//

#ifndef ENGINE_FRONT_MAINWINDOW_H_
#define ENGINE_FRONT_MAINWINDOW_H_

#include "resources.h"
#include <queue>
#include <QtOpenGL>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

QT_BEGIN_NAMESPACE
namespace Render_Ui { class RenderWindow; }
QT_END_NAMESPACE

class RenderWindow;

class MainWindow : public QMainWindow, protected QOpenGLFunctions {
 Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();
  void paintEvent(QPaintEvent* Event);
  void set_pixmap(QPixmap* new_pixmap);

 private slots:
  void on_actionRender_triggered();
  void on_actionSave_triggered();

// protected slots:
 public:
  void draw();

 private:
  Ui::MainWindow* ui;
  RenderWindow* render_window_ = nullptr;

  QGraphicsScene* scene;
  QGraphicsPixmapItem* pixmap_item;
  logic* logic_linker;
};

class RenderWindow : public QWidget {
 Q_OBJECT
 public:
  RenderWindow(logic* new_linker, QWidget* parent = nullptr);
  ~RenderWindow() override;

  void wheelEvent(QWheelEvent* event) override;

  void draw(std::pair<int, QTimer>* q_timer = new std::pair<int, QTimer>(), std::pair<int, int> start = {0, 0},
            std::pair<int, int> end = {-1, -1});
  void render();

  void set_lable(int sample);

  QImage* pixmap;

 private:
  int current_sample = 0;

  int render_cell_width = 64;
  int render_cell_height = 64;

  int max_threads = 6;
  int current_threads = 0;
  int current_cell = 0;



  QGraphicsScene* scene;
  QGraphicsView* view;
  logic* logic_linker;
  QTimer* timer;

  QLayout* layout;
  QToolBar* toolbar;
  QLabel* samples_lable;
  std::queue<std::pair<int, QTimer>*> threads;
 private:
  Render_Ui::RenderWindow* ui;


};
//class Render_Window : public QOpenGLWindow, protected QOpenGLFunctions {
// Q_OBJECT
// public:
//  Render_Window(logic* linker, QWidget* parent = nullptr);
//  ~Render_Window() override = default;
//
// protected:
//  void mousePressEvent(QMouseEvent* e) override;
//  void mouseReleaseEvent(QMouseEvent* e) override;
//  void timerEvent(QTimerEvent* e) override;
//
//  void initializeGL() override;
//  void resizeGL(int w, int h) override;
//  void paintGL() override;
// private:
//  logic* linker;
// private:
//  Render_Ui::Render_Window* ui;
//};
#endif //ENGINE_FRONT_MAINWINDOW_H_
