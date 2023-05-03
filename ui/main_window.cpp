//
// Created by Георгий Кузнецов on 13.04.2023.
//
#include "main_window.h"
#include "ui_main_window.h"

#include <string>
#include <QtGui/QWindow>
#include <thread>
#include <chrono>

using namespace std::chrono;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), pixmap_item(new QGraphicsPixmapItem), logic_linker(new logic) {
  ui->setupUi(this);
  scene = new QGraphicsScene(this);
  ui->graphicsView->setScene(scene);
  scene->addItem(pixmap_item);
//  std::thread t( [&](){
//    auto* pix_map = logic_linker->get_pixmap();
//    scene->addPixmap(QPixmap::fromImage(*pix_map));
//    delete pix_map;});
//  t.detach();
//  auto* pix_map = logic_linker->get_pixmap();
//  pixmap_item->setPixmap(*pix_map);
//  scene->addPixmap(QPixmap::fromImage(*pix_map));
//  delete pix_map;
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
  auto render_window = new RenderWindow(logic_linker);
  std::cout << "render_window: " << render_window << '\n';
  render_window->resize(this->width(), this->height());
  render_window->move(this->pos().operator+=(QPoint(offset_x, offset_y)));
  render_window->show();
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

RenderWindow::RenderWindow(logic* new_logic, QWidget* parent) : logic_linker(new_logic), QWidget(parent) {
  timer = new QTimer(this);
  scene = new QGraphicsScene(this);
  scene->setSceneRect(0, 0, logic_linker->get_camera_rect().first, logic_linker->get_camera_rect().second);
  view = new QGraphicsView(scene);
  view->setScene(scene);

  layout = new QVBoxLayout(this);

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
void RenderWindow::draw(std::pair<int, QTimer>* q_thread, std::pair<int, int> start, std::pair<int, int> end) {
//  std::cerr << "render_window from " << start << " to " << end << " draw sample " << q_thread->first << '\n';
  if (q_thread->first > logic_linker->get_samples()) {
    q_thread->second.stop();
    --current_threads;
    q_thread->second.~QTimer();
    return;
  }

  try {
    pixmap = logic_linker->get_pixmap(pixmap, q_thread->first, start, end);
    set_lable(q_thread->first);
    ++(q_thread->first);
  } catch (...) {
    std::cout << "exception from draw->get_pixmap()\n";
  }
  scene->addPixmap(QPixmap::fromImage(*pixmap));
  this->update();
//  std::cerr << "finish render\n";
}

void manage_render(QTimer* render_timer, std::vector<std::pair<int, QTimer>*>* threads, int max_thread,
                   int max_samples) {
  int cur_threads = 0;
  bool empty = true;
  for (auto* th : *threads) {
    if (th->first <= max_samples && th->first > 0)
      ++cur_threads;
    empty = false;
  }
//  std::cout << cur_threads << '\n';
  if (empty) {
    render_timer->stop();
    delete render_timer;
    threads->clear();
    return;
  }

//  for (auto& th : *threads) {
//    std::cout << *(th->first) << ' ' << (th->second) << '\n';
//  }

//  if (cur_threads <= max_thread) {
  for (auto* th : *threads) {
//      if (th->first == 0) {
    th->second.start();
//        std::cout << &th->second << '\n';
//        break;
//      }
  }
//  }
//  std::cout << "end\n";
}

bool can_thread(std::vector<std::pair<int, QTimer>*>* threads, int max_samples, int max_threads) {
  int threads_num = 0;
  for (auto* th : *threads) {
    std::cout << th->first << ' ' << &th->second << ' ' << th->second.isActive() << '\n';
    if (th->second.isActive())
      ++threads_num;
  }

  return threads_num < max_threads;
}



void RenderWindow::render() {
  if (current_threads >= max_threads){
    return;
  }

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
      auto* p = new std::pair<int, QTimer>{0, this};
      threads.push(p);
      p->second.start();
      connect(&p->second,
              &QTimer::timeout,
              this,
              [&, x, y, cell_height, cell_width, p, this]() {
                draw(p, {x, y}, {x + cell_width, y + cell_height});
                update();
              });
      return;
//      std::cout << std::pair<int, int>(x, y) << " -- " << std::pair<int, int>(x + cell_width, y + cell_height) << '\n';
    }
  }

//  int x = 0;
//  int y = 0;
//  int cell_width = 32;
//  int cell_height = 32;
//  threads.push_back(new QTimer());
//  auto* sample = new int;
//  threads[threads.size() - 1]->start();
//  connect(threads[threads.size() - 1],
//          &QTimer::timeout,
//          this,
//          [&, x, y, cell_height, cell_width, threads, sample, this]() {
//            draw(sample, threads[threads.size() - 1], {x, y}, {x + cell_width, y + cell_height});
//            update();
//          });
//  timer->stop();
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
