#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QGridLayout>
#include <QString>
#include <QTimer>
#include <QMessageBox>
#include <QList>
#include <QApplication>
#include <QKeyEvent>

#include <QPixmap>
#include <QGraphicsPixmapItem>

#include "item.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

    public:
  MainWindow();
  ~MainWindow();

  void keyPressEvent(QKeyEvent *e);

  public slots:

  void begin();
  void stop();
  void handleTimer();

 private: 
  QGraphicsScene *scene;
  QGraphicsView *view;
  QPushButton *start;
  QPushButton *quit;
  QPushButton *pause;
  QGridLayout *gridLayout;
  QTimer *timer;
  QTimer *wartimer;

  QMenuBar *mb;

  QList<Item*> list;

  QPixmap *garlicimg;
  QPixmap *warioimg;

  Wario *war;
};

#endif
