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

 protected:
  int x;
  int y;
  int vY;
  int vX;
  bool alive;
  QPixmap *pixMap;
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

#endif
