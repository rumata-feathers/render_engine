//
// Created by Георгий Кузнецов on 17.04.2023.
//
#include "../inc/resources.h"
#include "../inc/main_window.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow new_interface;
  new_interface.show();
  return a.exec();
}
