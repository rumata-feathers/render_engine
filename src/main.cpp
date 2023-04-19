#include "../resources.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGL);
  interface new_interface;
  return a.exec();
}

