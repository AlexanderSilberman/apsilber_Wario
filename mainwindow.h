#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>
#include <iostream>

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
#include <QTextEdit>
#include <QDockWidget>

#include <fstream>
#include <QLatin1String>

#include <QPixmap>
#include <QGraphicsPixmapItem>



#include "item.h"

using namespace std;

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
  void create(int count);
  void changePoints(int i);
  void setLives(int life);
  void newLevel();
  void end();

  public slots:

  void begin();
  void stop();
  void handleTimer();
 

 private: 
  int coins;
  int points;
  int lives;
  bool started;
  bool ended;
  int timeout;
  int level;

  QString nm;
  QTextEdit *text;

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
  QPixmap *spikesimg;
  QPixmap *level2img;
  QPixmap *level3img;

  QGraphicsSimpleTextItem * score;
  QGraphicsSimpleTextItem * life;

  Wario *war;
  Ledge *led;
  Spikes *spike;

  int counter;
  int total;
  int ledgetimer;
  int randbboulder;
  int randsboulder;
  int randgarlic;
  bool spikescreate;
  bool ledgecreate;

  QGraphicsRectItem *r;
  QGraphicsSimpleTextItem *line1;
  QGraphicsSimpleTextItem *line2;
  QGraphicsSimpleTextItem *line3;
  QGraphicsSimpleTextItem *line4;
  QGraphicsSimpleTextItem *line5;



};

struct Score{
  QString user;
  int hscore;
  string test;
};

#endif
