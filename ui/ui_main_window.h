/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include "main_window_par.h"

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow {
 public:
  QAction* actionRender;
  QAction* actionSave;
  QWidget* centralwidget;
  QHBoxLayout* horizontalLayout;
  QSplitter* splitter;
  QGraphicsView* graphicsView;
  QListView* listView;
  QMenuBar* menubar;
  QMenu* menuRender;
//  QStatusBar* statusbar;

  void setupUi(QMainWindow* MainWindow) {
    if (MainWindow->objectName().isEmpty())
      MainWindow->setObjectName("MainWindow");
    MainWindow->setWindowModality(Qt::WindowModal);
    MainWindow->resize(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);
    MainWindow->setMouseTracking(true);
    MainWindow->setAutoFillBackground(true);

    actionRender = new QAction(MainWindow);
    actionRender->setObjectName("actionRender");
    actionRender->setCheckable(false);
    QIcon icon(QIcon::fromTheme(QString::fromUtf8("applications-graphics")));
    actionRender->setIcon(icon);

    actionSave = new QAction(MainWindow);
    actionSave->setObjectName("actionSave");
    actionSave->setCheckable(false);

    centralwidget = new QWidget(MainWindow);
    centralwidget->setObjectName("centralwidget");
    centralwidget->setMinimumSize(QSize(MAIN_WINDOW_MIN_WIDTH, MAIN_WINDOW_MIN_HEIGHT));

    horizontalLayout = new QHBoxLayout(centralwidget);
    horizontalLayout->setObjectName("horizontalLayout");
    horizontalLayout->setSizeConstraint(QLayout::SetNoConstraint);
    horizontalLayout->setContentsMargins(0, 0, 0, 0);

    splitter = new QSplitter(centralwidget);
    splitter->setObjectName("splitter");
    splitter->setMouseTracking(true);
    splitter->setLayoutDirection(Qt::LeftToRight);
    splitter->setInputMethodHints(Qt::ImhMultiLine);
    splitter->setFrameShape(QFrame::NoFrame);
    splitter->setLineWidth(2);
    splitter->setOrientation(Qt::Horizontal);
    splitter->setOpaqueResize(true);
    splitter->setHandleWidth(3);
    // remove dot in splitter handle
    splitter->setStyleSheet("QSplitter::handle { image: none; }");

    graphicsView = new QGraphicsView(splitter);
    graphicsView->setObjectName("graphicsView");
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(1);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
    graphicsView->setSizePolicy(sizePolicy);
    graphicsView->setMouseTracking(true);
    graphicsView->setRenderHints(
        QPainter::LosslessImageRendering | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);
    graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    splitter->addWidget(graphicsView);

    listView = new QListView(splitter);
    listView->setObjectName("listView");
    listView->setEnabled(true);
    listView->setMouseTracking(true);
    listView->setResizeMode(QListView::Adjust);
    splitter->addWidget(listView);

    horizontalLayout->addWidget(splitter);

    MainWindow->setCentralWidget(centralwidget);

    menubar = new QMenuBar(MainWindow);
    menubar->setObjectName("menubar");
    menubar->setGeometry(QRect(0, 0, MAIN_WINDOW_WIDTH, MENUBAR_HEIGHT));
    menuRender = new QMenu(menubar);
    menuRender->setObjectName("menuRender");
    MainWindow->setMenuBar(menubar);

    menubar->addAction(menuRender->menuAction());
    menuRender->addAction(actionRender);
    menuRender->addAction(actionSave);

//    statusbar = new QStatusBar(MainWindow);
//    statusbar->setObjectName("statusbar");
//    statusbar->setFixedHeight(STATUSBAR_HEIGHT);
//    MainWindow->setStatusBar(statusbar);



    retranslateUi(MainWindow);

    QMetaObject::connectSlotsByName(MainWindow);
  } // setupUi

  void retranslateUi(QMainWindow* MainWindow) {
    MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Rumat", nullptr));
    actionRender->setText(QCoreApplication::translate("MainWindow", "Render Image", nullptr));
    actionSave->setText(QCoreApplication::translate("MainWindow", "Save Rendered Image", nullptr));
#if QT_CONFIG(whatsthis)
    graphicsView->setWhatsThis(QCoreApplication::translate("MainWindow",
                                                           "<html><head/><body><p>graphics_view</p><p><br/></p></body></html>",
                                                           nullptr));
#endif // QT_CONFIG(whatsthis)
    menuRender->setTitle(QCoreApplication::translate("MainWindow", "Render", nullptr));
  } // retranslateUi

};
class Ui_RenderWindow {
 public:
  QAction* actionSaveImage;
  QMenuBar* menubar;
  QMenu* menuSaveImage;
 public:
  void setupUi(QWidget* window) {
    if (window->objectName().isEmpty())
      window->setObjectName("Render");
    window->setWindowModality(Qt::WindowModal);
    window->setMouseTracking(true);
    window->setAutoFillBackground(true);

    actionSaveImage = new QAction(window);
    actionSaveImage->setObjectName("save rendered image");
    actionSaveImage->setCheckable(false);
//    return;
    menubar = new QMenuBar(window);
    menubar->setObjectName("menubar");
    menubar->setGeometry(QRect(0, 0, MAIN_WINDOW_WIDTH, MENUBAR_HEIGHT));
    menuSaveImage = new QMenu(menubar);
    menuSaveImage->setObjectName("menuSaveImage");
    menubar->addMenu(menuSaveImage);
    window->layout()->setMenuBar(menubar);

    menubar->addAction(menuSaveImage->menuAction());
    menuSaveImage->addAction(actionSaveImage);

    retranslateUi(window);

    QMetaObject::connectSlotsByName(window);
  }
  void retranslateUi(QWidget* window) {
    window->setWindowTitle(QCoreApplication::translate("RenderWindow", "Render", nullptr));
    actionSaveImage->setText(QCoreApplication::translate("RenderWindow", "save", nullptr));
//#if QT_CONFIG(whatsthis)
//    graphicsView->setWhatsThis(QCoreApplication::translate("MainWindow", "<html><head/><body><p>graphics_view</p><p><br/></p></body></html>", nullptr));
//#endif // QT_CONFIG(whatsthis)
    menuSaveImage->setTitle(QCoreApplication::translate("RenderWindow", "image", nullptr));
  } // retranslateUi
};

namespace Ui {
class MainWindow : public Ui_MainWindow {};
} // namespace Ui

namespace Render_Ui {
class RenderWindow : public Ui_RenderWindow {};
} //namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
