//
// Created by Георгий Кузнецов on 13.04.2023.
//
#include "main_window.h"
#include "ui_main_window.h"


#include <string>
#include <QtGui/QWindow>
#include <thread>
#include <chrono>
#include <QtConcurrent/QtConcurrent>
#include <QtConcurrent/QtConcurrentRun>
#include <QOpenGLWindow>
#include <QtGui>
#include <QtOpenGL>
#include <GLUT/glut.h>

using namespace std::chrono;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), pixmap_item(new QGraphicsPixmapItem), logic_linker(new logic) {
  ui->setupUi(this);
  scene = new QGraphicsScene(this);
  ui->graphicsView->setScene(scene);
  scene->addItem(pixmap_item);
  std::thread t([&]() {
//    auto* pix_map = logic_linker->get_pixmap();
//    pixmap_item->setPixmap(QPixmap::fromImage(*pix_map));
//    delete pix_map;
  });
  t.detach();
}

MainWindow::~MainWindow() {
  delete ui;
}
void MainWindow::set_pixmap(QPixmap* new_pixmap) {
  pixmap_item->setPixmap(*new_pixmap);
}
void MainWindow::paintEvent(QPaintEvent* event) {
//  draw();
}
void MainWindow::draw() {
//  QPainter painter(ui->graphicsView);
//  render(&painter);
  auto start = high_resolution_clock::now();
  auto* pix_map = logic_linker->get_pixmap();
  pixmap_item->setPixmap(QPixmap::fromImage(*pix_map));
//  qreal factor(ui->splitter->width() / pix_map->width());
//  pixmap_item->setScale(factor);
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  std::cerr << duration.count() << '\n';
  delete pix_map;
}
void MainWindow::on_actionRender_triggered() {
  auto [offset_x, offset_y] = std::make_pair(15, 30);
  render_window_ = new Render_Window();
  std::cout << "render_window: " << render_window_ << '\n';
  render_window_->resize(this->width(), this->height());

  render_window_->set_linker(logic_linker);
//  render_window_->move(this->pos().operator+=(QPoint(offset_x, offset_y)));
  render_window_->show();
}
void MainWindow::on_actionSave_triggered(int i) {
  return;
  /*on_actionRender_triggered();


  render_window_->render_animation();
  return;

  if (90 - i <= 5)
    return;

  if (!render_window_){
    moveToThread(this->thread());
    on_actionRender_triggered();
//    QFuture<void> future = QtConcurrent::run([=]{render_window_->render();});
//    future.waitForFinished();
    on_actionSave_triggered(i);
  }

  for (int j = 0; j < render_window_->threads.size(); ++j) {
    if (!render_window_->threads[j])
      continue;

    int* x = new int(1000);
    wait(x);
    QtConcurrent::run([&, i]{on_actionSave_triggered(i);});
    return;
  }

  std::string fileName = "/Users/georgiikuznetsov/Desktop/seq/file_" + std::to_string(i) + ".png";
  if (render_window_->pixmap->save(QString::fromStdString(fileName), "PNG", -1)){
    std::cout << "file saved!\n";
    logic_linker->cur_scene->camera_ = camera(point3(-2,2,1), point3(0,0,-1), vec3(0,1,0), 90-i, 16.0/9.0);
    QtConcurrent::run([=]{render_window_->render();});
    on_actionSave_triggered(++i);
  }else
    std::cout << "file not saved!\n";
//  render_window_->deleteLater();*/
}
void something(QImage* pix_map) {
  QColor color;
  color.setRedF((float) random_double(0, 255));
  color.setGreenF((float) random_double(0, 255));
  color.setBlueF((float) random_double(0, 255));
  pix_map->fill(color);
  for (int i = 0; i < 10000; ++i) {
    for (int j = 0; j < 10000; ++j) {
      double k = j;
      k = j << 15;
      double g = sqrt(k);
      k = sqrt(g) + k;
    }
    std::cerr << "asmdflkams" << '\n';
  }
}

/*RenderWindow::RenderWindow(logic* new_logic, QWidget* parent) : logic_linker(new_logic), QWidget(parent), ui(new Render_Ui::RenderWindow) {

  timer = new QTimer(this);
  scene = new QGraphicsScene(this);
  scene->setSceneRect(0, 0, logic_linker->get_camera_rect().first, logic_linker->get_camera_rect().second);
  view = new QGraphicsView(scene);
  view->setScene(scene);

  layout = new QVBoxLayout(this);
  ui->setupUi(this);

  pixmap =
      new QImage(logic_linker->get_camera_rect().first, logic_linker->get_camera_rect().second, QImage::Format_ARGB32);
  pixmap->fill(QColor(255, 255, 255, 255));
  scene->addPixmap(QPixmap::fromImage(*pixmap));

  layout->addWidget(view);
  layout->setContentsMargins(0, 0, 0, 0);
  view->setResizeAnchor(QGraphicsView::AnchorUnderMouse);

  toolbar = new QToolBar(this);
  layout->addWidget(toolbar);
  samples_lable = new QLabel(this);
  samples_lable->setText("samples: ");
  samples_lable->resize(this->width(), 20);

  toolbar->addWidget(samples_lable);
  toolbar->layout()->setAlignment(Qt::AlignTop);
  toolbar->resize(this->width(), 50);

  connect(timer, &QTimer::timeout, this, [&]() {
    render();
  });

//  connect(timer, &QObject::destroyed, this, [&]() { qDebug() << "timer_delete"; });
  timer->start();
}
std::ostream& operator<<(std::ostream& stream, const std::pair<int, int>& p) {
  stream << "(" << p.first << ", " << p.second << ")";
  return stream;
}
RenderWindow::~RenderWindow() {

  pixmap->~QImage();
  delete pixmap;

  timer->~QTimer();
  delete timer;

  scene->~QGraphicsScene();
  delete scene;

  view->~QGraphicsView();
  delete view;

  layout->~QLayout();
  delete layout;

  toolbar->~QToolBar();
  delete toolbar;

  samples_lable->~QLabel();
  delete samples_lable;

}
void RenderWindow::draw(int* sample, QTimer* q_timer, std::pair<int, int> start, std::pair<int, int> end)  {
//  std::cerr << "render_window from " << start << " to " << end << " draw sample " << sample << '\t';
//  std::cerr << q_timer->thread()->currentThreadId() << ' ' << q_timer->thread()->isRunning() << ' '
//            << q_timer->isActive() << ' '
//            << current_threads << '\n';
  if (*sample > logic_linker->get_samples()) {
    q_timer->stop();
//    q_thread->second.deleteLater();
    --current_threads;
    delete sample;
//    delete q_timer;
    return;
  }

  try {
    pixmap = logic_linker->get_pixmap(pixmap, *sample, start, end);
    set_lable(*sample);
    ++(*sample);
  } catch (...) {
    std::cout << "exception from draw->get_pixmap()\n";
  }
  scene->addPixmap(QPixmap::fromImage(*pixmap));
//  scene->update(start.first, start.second, end.first - start.first, end.second - start.second);
  this->update();
//  std::cerr << "finish render\n";
}
void RenderWindow::render() {
  std::cout << "start rendering " << *current_frame <<  ' ' << current_threads << "\n";
  bool render_anim = false;
  if(render_anim){
    if (threads.empty()){
      auto* p = new int;
      auto* p_timer = new QTimer;
      threads.push_back(p_timer);
      p_timer->start();

      connect(p_timer, &QTimer::timeout, this, [&, p, p_timer, this]() {
        draw(p, p_timer);
        scene->update();
      });
      return;
    }
    for (int i =0; i < threads.size(); ++i) {
      if (!threads[i] || !threads[i]->isActive()){
        continue;
      }
      return;
    }
    for (int i = 0; i <threads.size(); ++i) {
      threads[i]->deleteLater();
    }
    threads.clear();
    std::cout << "finished rendering\n";
    emit this->FinishedRendering();
    return;
  }








  if (current_threads >= max_threads) {
    return;
  }

  int max_samples = logic_linker->get_samples();
//  auto* thread = new QThread();

  ++current_threads;
  int cell_num = 0;

  for (int ver_cell = 0;
       ver_cell < std::ceil((double) logic_linker->get_camera_rect().second / (double) render_cell_height);
       ++ver_cell) {
    // left upper corner of the render_cell
    int y = ver_cell * render_cell_height;
    int cell_height = (y + render_cell_height > logic_linker->get_camera_rect().second) ?
                      logic_linker->get_camera_rect().second - y : render_cell_height;
    for (int hor_cell = 0;
         hor_cell < std::ceil((double) logic_linker->get_camera_rect().first / (double) render_cell_width);
         ++hor_cell) {
      if (cell_num++ < current_cell)
        continue;
      current_cell++;

      int x = hor_cell * render_cell_width;
      int cell_width = (x + render_cell_width > logic_linker->get_camera_rect().first) ?
                       logic_linker->get_camera_rect().first - x : render_cell_width;

      auto* p = new int;
      auto* p_timer = new QTimer;
      threads.push_back(p_timer);
      p_timer->start();

      connect(p_timer, &QTimer::timeout, this, [&, x, y, cell_height, cell_width, p, p_timer, this]() {
        draw(p, p_timer, {x, y}, {x + cell_width, y + cell_height});
        scene->update(QRect(x, y, cell_width, cell_height));
      });
      return;
    }
  }
  for (int i =0; i < threads.size(); ++i) {
//    std::cout << threads[i] << ' ' << threads[i]->isActive() << '\t';
//    std::cout << &threads[i]->second << ' ' << threads[i]->second.isActive() << '\t';
//    std::cout << threads[i]->second << '\n';
    if (!threads[i] || !threads[i]->isActive()){
//      delete threads[i];
      continue;
    }
    return;
  }
  for (int i = 0; i <threads.size(); ++i) {
    threads[i]->deleteLater();
  }
  threads.clear();
  std::cout << "finished rendering\n";
  emit this->FinishedRendering();
//  timer->stop();
}
void RenderWindow::render_animation() {
//  int cur_sample =
  logic_linker->cur_scene->camera_ = camera(point3(-2,2,1), point3(0,0,-1), vec3(0,1,0), 90-*current_frame, 16.0/9.0);
  end_frame = 89;
  connect(this, SIGNAL(FinishedRendering()), this, SLOT(anim()));
}
void RenderWindow::anim() {
  if (*current_frame >= end_frame){
    timer->stop();
    return;
  }
  std::string fileName = "/Users/georgiikuznetsov/Desktop/seq/file_" + std::to_string(*current_frame) + ".png";
  if (pixmap->save(QString::fromStdString(fileName), "PNG", -1)){
    std::cerr << "file saved!\n";
    pixmap->fill(QColor(255, 255, 255));
    ++(*current_frame);
    current_threads = 0;
    current_cell = 0;
    logic_linker->cur_scene->camera_ = camera(point3(-2,2,1), point3(0,0,-1), vec3(0,1,0), 90-*current_frame, 16.0/9.0);
  }else
    std::cout << "file not saved!\n";
  std::cout << "anim\n";
}
void RenderWindow::wheelEvent(QWheelEvent* event) {
  int angle = event->angleDelta().y();
  qreal factor;
  if (angle > 0) {
    factor = 1.1;
  } else {
    factor = 0.9;
  }
  view->scale(factor, factor);
}
void RenderWindow::set_lable(int sample) {
  std::string text = "samples: " + std::to_string(sample) + "/" + std::to_string(logic_linker->get_samples());
  samples_lable->setText(text.c_str());
}
void RenderWindow::on_actionSaveImage_triggered() {
  std::cout << "qlksfmq\n";
}*/

Render_Window::Render_Window(QWidget* parent) : ui(new Render_Ui::Render_Window) {
  ui->setupUi(this);
}
int get_pixel(int x, int y, int width, int height, int depth = 3) {
  return ((height - y) * width + x) * depth;
}
void Render_Window::set_linker(logic* other_linker) {
  linker = other_linker;
  timer = new QTimer;
  timer->start();
  connect(timer, &QTimer::timeout, this, [&] { render(); });
  connect(this, &Render_Window::finished_render, this, [=] {
    timer->stop();
    QImage output(linker->get_camera_rect().first, linker->get_camera_rect().second, QImage::Format_RGB32);
    for (int i = 0; i < linker->get_camera_rect().first; ++i) {
      for (int j = 0; j < linker->get_camera_rect().second; ++j) {
        QColor clr;
        clr.setRedF(pba[get_pixel(i, j, linker->get_camera_rect().first, linker->get_camera_rect().second)]);
        clr.setGreenF(pba[get_pixel(i, j, linker->get_camera_rect().first, linker->get_camera_rect().second) + 1]);
        clr.setBlueF(pba[get_pixel(i, j, linker->get_camera_rect().first, linker->get_camera_rect().second) + 2]);
        output.setPixelColor(i, j, clr);
      }
    }
    std::string fileName = "/Users/georgiikuznetsov/Desktop/seq/file.png";
    output.save(QString::fromStdString(fileName), "PNG", -1);
  });
//  QtConcurrent::run([&] {
//    while (sample < linker->get_samples())
//      QtConcurrent::run([&] { paintGL(); });
//  });
}
void Render_Window::mousePressEvent(QMouseEvent* e) {
  QWindow::mousePressEvent(e);
}
void Render_Window::mouseReleaseEvent(QMouseEvent* e) {
  QWindow::mouseReleaseEvent(e);
}
void Render_Window::timerEvent(QTimerEvent* e) {
  QObject::timerEvent(e);
}
void Render_Window::initializeGL() {
  setTitle("Render");
  // Set up the rendering context, load shaders and other resources, etc.:
  initializeOpenGLFunctions();
  glClearColor(0, 0, 0, 1);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);
}
void Render_Window::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45, (float) w / h, 0.01, 100.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
}

//void Render_Window::paintEvent(QPaintEvent*)
//{
//  QPainter painter(this);
//  QImage img(100, 100, QImage::Format_RGBA64);
//  img.fill(QColorConstants::DarkRed);
//  painter.drawImage(this->geometry(),img);
//}
void Render_Window::wheelEvent(QWheelEvent* event) {
  int angle = event->angleDelta().y();
  double factor;
  if (angle > 0) {
    factor = 1.1;
  } else {
    factor = 0.9;
  }
  auto z = geometry();
  resizeGL(double(z.width()) * factor, double(z.height()) * factor);
}
void Render_Window::paintGL() {
  // set background colour
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  GLfloat color[] = {float(23) / 255, float(23) / 255, float(25) / 255, float(255) / 255};
  glClearColor(color[0], color[1], color[2], color[3]);

  const int w = linker->get_camera_rect().first;
  const int h = linker->get_camera_rect().second;
  const double x = 0;
  const double y = 0;

  //buffer array
//  auto* pba = new float[w * h * 3];
//  float* pba = nullptr;
//  for (int i = 0; i < h; ++i) {
//    for (int j = 0; j < w; ++j) {
//      pba[(i * w + j) * 3] = float(i) / float(h);
//      pba[(i * w + j) * 3 + 1] = float(i + j) / float(w + h);
//      pba[(i * w + j) * 3 + 2] = float(j) / float(w);
//    }
//  }
  if (pba == nullptr) {
    std::cout << "create pba\n";
//  if (sample < linker->get_samples())
    pba = linker->get_pixmap(pba, sample++);
  }

//  glRasterPos2d(x, y);
  GLint iViewport[4];
  glGetIntegerv(GL_VIEWPORT, iViewport);
  glPixelZoom(iViewport[2] / w, iViewport[3] / h);
//  glRasterPos2d(iViewport[0],iViewport[1]);
  std::cout << "draw pba\n";
  glDrawPixels(w, h, GL_RGB, GL_FLOAT, pba);
  glEnd();
  update();
}
void Render_Window::render() {
  std::cout << "render\n";
  if (sample < linker->get_samples()) {
    pba = linker->get_pixmap(pba, sample++);
    std::cout << sample << '\n';
    //  auto* pba = new float[w * h * 3];
//  float* pba = nullptr;
//  for (int i = 0; i < h; ++i) {
//    for (int j = 0; j < w; ++j) {
//      pba[(i * w + j) * 3] = random_double();
//      pba[(i * w + j) * 3 + 1] = random_double();
//      pba[(i * w + j) * 3 + 2] = random_double();
//    }
//  }
  } else
      emit finished_render();
  paintGL();
}