#include "item.h"

#include <iostream>
using namespace std;

Item::Item(QPixmap*p, int nx, int ny){
  pixMap=p;
  setPixmap(*p);
  x=nx;
  y=ny;
  setPos(x,y);
  alive=true;
}
bool Item::isAlive(){
  return alive;
}

Garlic::Garlic(QPixmap *pm, int nx, int ny) : Item(pm, nx, ny){
  vY=5;
  vX=0;
}

void Garlic::move(){
  y+=vY;
  setPos(x,y);
}

Wario::Wario(QPixmap *pm, int nx, int ny) : Item(pm, nx, ny){
  vX=0;
  vY=0;
}

void Wario::move(){
  y+=vY;
  x+=vX;
  setPos(x,y);
}

void Wario::direction(int mX, int mY){
  vX+=mX;
  vY+=mY;
  cout<<"here"<<endl;
}
