//
// Created by Георгий Кузнецов on 13.04.2023.
//

#ifndef ENGINE_FRONT_MAINWINDOW_H_
#define ENGINE_FRONT_MAINWINDOW_H_

#include "resources.h"
#include <queue>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow, protected QOpenGLFunctions {
 Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();
  void paintEvent(QPaintEvent* Event);
  void set_pixmap(QPixmap* new_pixmap);

 private slots:
  void on_actionRender_triggered();

// protected slots:
 public:
  void draw();

 private:
  Ui::MainWindow* ui;

  QGraphicsScene* scene;
  QGraphicsPixmapItem* pixmap_item;
  logic* logic_linker;
};

class RenderWindow : public QWidget {
 Q_OBJECT
 public:
  explicit RenderWindow(logic* new_linker, QWidget* parent = nullptr);
  ~RenderWindow() override;

  void wheelEvent(QWheelEvent* event) override;

  void draw(std::pair<int, QTimer>* q_timer = new std::pair<int, QTimer>(), std::pair<int, int> start = {0, 0}, std::pair<int, int> end = {-1, -1});
  void render();

  void set_lable(int sample);

 private:
  int current_sample = 0;

  int render_cell_width = 32;
  int render_cell_height = 32;

  int max_threads = 1;
  int current_threads = 0;
  int current_cell = 0;


  QImage* pixmap;

  QGraphicsScene* scene;
  QGraphicsView* view;
  logic* logic_linker;
  QTimer* timer;

  QLayout* layout;
  QToolBar* toolbar;
  QLabel* samples_lable;
  std::queue<std::pair<int, QTimer>*> threads;

};
#endif //ENGINE_FRONT_MAINWINDOW_H_
