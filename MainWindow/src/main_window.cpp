//
// Created by Георгий Кузнецов on 13.04.2023.
//

#include "../inc/main_window.h"
#include "../inc/ui_main_window.h"
#include "../src/render_window.cpp"



#include <iostream>
#include <string>
#include <QtGui/QWindow>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), pixmap_item(new QGraphicsPixmapItem), logic_linker(new logic) {
  ui->setupUi(this);
  scene = new QGraphicsScene(this);
  ui->graphicsView->setScene(scene);
  scene->addItem(pixmap_item);
}

MainWindow::~MainWindow() {
  delete ui;
}
void MainWindow::set_pixmap(QPixmap* new_pixmap) {
  pixmap_item->setPixmap(*new_pixmap);
}
void MainWindow::paintEvent(QPaintEvent* event) {
  draw();
}

void MainWindow::draw() {
  QPainter painter(ui->graphicsView);
  render(&painter);
  auto* pix_map = logic_linker->get_pixmap();
  pixmap_item->setPixmap(*pix_map);
  delete pix_map;
}

void MainWindow::on_actionRender_triggered() {
//  auto [offset_x, offset_y] = std::make_pair(15, 30);
//  auto render_window = new RenderWindow(logic_linker);
//  render_window->resize(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);
//  render_window->move(this->pos().operator+=(QPoint(offset_x, offset_y)));
//  render_window->draw();
//  render_window->show();

  auto r_w = new RenderWindow(this);
  r_w->show();
}

//RenderWindow::RenderWindow(logic* new_logic, QWidget* parent) : logic_linker(new_logic), QWidget(parent) {
//  timer = new QTimer(this);
//  scene = new QGraphicsScene(this);
//  scene->setSceneRect(0, 0, logic_linker->get_camera_rect().first, logic_linker->get_camera_rect().second);
//  view = new QGraphicsView(scene);
//  view->setScene(scene);
//
////  paint_engine = new QPaintEngine;
//
//  layout = new QVBoxLayout(this);
//
//  pixmap = logic_linker->get_pixmap();
//
//  layout->addWidget(view);
//  layout->setContentsMargins(0, 0, 0, 0);
//  view->setResizeAnchor(QGraphicsView::AnchorUnderMouse);
////  view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
//
//
////  toolbar = new QToolBar(this);
////  layout->addWidget(toolbar);
////  auto toolbar_layout = new QVBoxLayout(toolbar);
//
//  samples_lable = new QLabel(this);
//  samples_lable->setText("samples: ");
//  samples_lable->resize(this->width(), 20);
//
////  toolbar->addWidget(samples_lable);
//  layout->setAlignment(Qt::AlignTop);
////  toolbar->resize(this->width(), 20);
////  toolbar_layout->addWidget(samples_lable);
//  layout->addWidget(samples_lable);
//
//  connect(timer, &QTimer::timeout, this, [&]() { draw(); }, Qt::QueuedConnection);
//  connect(timer, &QObject::destroyed, this, [&]() { qDebug() << "timer_delete"; });
//  timer->start();
//}
//
//RenderWindow::~RenderWindow() {
//  timer->~QTimer();
//  scene->~QGraphicsScene();
//  view->~QGraphicsView();
//
//  layout->~QLayout();
//  toolbar->~QToolBar();
//  samples_lable->~QLabel();
//}
//void RenderWindow::draw() {
//
////  std::cout << view->sceneRect().x() << ' ' << view->sceneRect().y() << ' ' << view->sceneRect().width() << ' '
////            << view->sceneRect().height() << '\n';
////  std::cout << view->rect().x() << ' ' << view->rect().y() << ' ' << view->rect().width() << ' '
////            << view->rect().height() << '\n';
//  if (current_sample >= logic_linker->get_samples())
//    timer->stop();
//
//  set_lable();
//  ++current_sample;
////  std::cerr << current_sample << '\n';
//
////  auto* pix_map = logic_linker->get_pixmap();
////  auto map_image = pix_map->toImage();
////
////  auto cur_map_image = pixmap->toImage();
////  float old_multiplier = (float) current_sample / ((float) current_sample + 1);
////  float new_multiplier = 1 / ((float) current_sample + 1);
////
////  for (int y = 0; y < cur_map_image.height(); ++y) {
////    for (int x = 0; x < cur_map_image.width(); ++x) {
////
////      auto old_pixel = cur_map_image.pixelColor(x, y);
////      auto new_pixel = map_image.pixelColor(x, y);
////
////      QColor new_color;
////      new_color.setRedF(old_pixel.redF() * old_multiplier + new_pixel.redF() * new_multiplier);
////      new_color.setBlueF(old_pixel.blueF() * old_multiplier + new_pixel.blueF() * new_multiplier);
////      new_color.setGreenF(old_pixel.greenF() * old_multiplier + new_pixel.greenF() * new_multiplier);
////      new_color.setAlphaF(old_pixel.alphaF() * old_multiplier + new_pixel.alphaF() * new_multiplier);
////
////      cur_map_image.setPixelColor(x, y, new_color);
////    }
////  }
////
////  *pixmap = QPixmap::fromImage(cur_map_image);
//  QPixmap smth(1280, 720);
//  scene->addPixmap(smth);
////  scene->addPixmap(*pixmap);
//
////  pix_map->~QPixmap();
////  delete pix_map;
//}
//
//void RenderWindow::wheelEvent(QWheelEvent* event) {
//  int angle = event->angleDelta().y();
//  qreal factor;
//  if (angle > 0) {
//    factor = 1.1;
//  } else {
//    factor = 0.9;
//  }
//  view->scale(factor, factor);
//}
//void RenderWindow::set_lable() {
//  std::string text = "samples: " + std::to_string(current_sample) + "/" + std::to_string(logic_linker->get_samples());
//  samples_lable->setText(text.c_str());
//}
