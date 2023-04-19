//
// Created by Георгий Кузнецов on 13.04.2023.
//

#ifndef ENGINE_FRONT_MAINWINDOW_H_
#define ENGINE_FRONT_MAINWINDOW_H_

#include "resources.h"

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

//class RenderWindow: public QWidget{
//  Q_OBJECT
// public:
//  RenderWindow(logic* new_linker, QWidget *parent = nullptr);
//  ~RenderWindow();
//
//  void wheelEvent (QWheelEvent* event);
//
//  void draw();
//
//  void set_lable();
//
// private:
//  int current_sample = 0;
//
//  QPixmap* pixmap;
//
//  QGraphicsScene* scene;
//  QGraphicsView* view;
//  logic* logic_linker;
//  QTimer* timer;
//
//  QLayout* layout;
//  QToolBar* toolbar;
//  QLabel* samples_lable;
//  QPaintEngine* paint_engine;
//  QPainter* painter;
//};
#endif //ENGINE_FRONT_MAINWINDOW_H_
