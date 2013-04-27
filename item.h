#ifndef ITEM_H
#define ITEM_H

#include <QPixmap>
#include <QGraphicsPixmapItem>

class MainWindow;

class Item : public QGraphicsPixmapItem {

 public:
  Item(QPixmap *pm, int nx, int ny);
  virtual void move() = 0;
  bool isAlive();
  int getPoints();
  bool getNice();

 protected:
  int x;
  int y;
  int vY;
  int vX;
  bool alive;
  bool nice;
  QPixmap *pixMap;
  int points;
};


class Garlic:public Item {
 public:
  Garlic(QPixmap *pm, int nx, int ny);
  void move();

};

class Wario:public Item {
 public:
  Wario(QPixmap *pm, int nx, int ny);
  void move();
  void direction(int mX, int mY);
};

class Diamond:public Item {
 public:
  Diamond(QPixmap *pm, int nx, int ny);
  void move();

};

class BBoulder:public Item {
 public:
  BBoulder(QPixmap *pm, int nx, int ny);
  void move();

};

class SBoulder:public Item {
 public:
  SBoulder(QPixmap *pm, int nx, int ny);
  void move();

};

class Ledge:public Item {
 public:
  Ledge(QPixmap *pm, int nx, int ny);
  void move();
  void stood();
 private:
  bool touched;
  int counter;
};

class Coin:public Item {
 public:
  Coin(QPixmap *pm, int nx, int ny);
  void move();

};

#endif
