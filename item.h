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
  int getName();

 protected:
  float x;
  float y;
  float vY;
  float vX;
  bool alive;
  bool nice;
  QPixmap *pixMap;
  int points;
  /* 1 is a coin, 2 is a diamond, 3 is a ledge, 4 is garlic */
  int name;
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
  void direction(float mX, float mY);
  void reset();
};

class Diamond:public Item {
 public:
  Diamond(QPixmap *pm, int nx, int ny);
  void move();
 private: 
  bool left;

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
