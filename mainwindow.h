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

class ViewWindow : public QGraphicsView{
 public:
  ViewWindow(QGraphicsScene* nscene, QMainWindow* main);

};

class Screen: public QGraphicsScene{
 public:
  Screen(QMainWindow* main);
  void mousePressEvent(QGraphicsSceneMouseEvent *e);
 private:
  QMainWindow* main_;
    };

class MainWindow : public QMainWindow {
  Q_OBJECT

    public:
  MainWindow();
  ~MainWindow();

  void keyPressEvent(QKeyEvent *e);
  void keyReleaseEvent(QKeyEvent *e);
  void mousePressEvent(QGraphicsSceneMouseEvent *e);
  

  public slots:

  void begin();
  void stop();
  void handleTimer();

 private: 
  int points;

  Screen* scene;
  ViewWindow* view;
  QPushButton *start;
  QPushButton *quit;
  QPushButton *pause;
  QGridLayout *gridLayout;
  QTimer *timer;

  QMenuBar *mb;

  QList<Item*> list;

  QPixmap *garlicimg;
  QPixmap *warioimg;
  QPixmap *bigboulderimg;
  QPixmap *diamondimg;
  QPixmap *coinimg;
  QPixmap *wallimg;
  QPixmap *ledgeimg;
  QPixmap *smallrockimg;

  QGraphicsSimpleTextItem * score;

  Wario *war;

  int counter;
};



#endif
