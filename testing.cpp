//
// Created by Георгий Кузнецов on 17.04.2023.
//
#include "resources.h"
#include "main_window.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow new_interface;
  new_interface.set_pixmap(new QPixmap(100, 200));
  new_interface.show();
  return a.exec();
}
