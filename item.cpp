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

int Item::getPoints(){
  return points;
}

bool Item::getNice(){
  return nice;
}

Garlic::Garlic(QPixmap *pm, int nx, int ny) : Item(pm, nx, ny){
}

void Garlic::move(){
  y+=3;
  setPos(x,y);
}

Wario::Wario(QPixmap *pm, int nx, int ny): Item(pm,nx,ny){
  
  vX=0;
  vY=0;
  
}

void Wario::move(){
  y+=vY;
  x+=vX;
  setPos(x,y);
  if(y==790){
    alive=false;
  }
}

void Wario::direction(int mX, int mY){
  vX+=mX;
  vY+=mY;
}

Diamond::Diamond(QPixmap *pm, int nx, int ny) : Item(pm, nx, ny){
  nice=true;
  points=1000;
}

void Diamond::move(){
  x+=2;
  setPos(x,y);
  if(x==-40 || x==840){
    alive=false;
  }
}

SBoulder::SBoulder(QPixmap *pm, int nx, int ny) : Item(pm, nx, ny){
  nice=false;
}

void SBoulder::move(){
  y+=3;
  setPos(x,y);
  if(y>=780){
    alive=false;
  }
}

Coin::Coin(QPixmap *pm, int nx, int ny) : Item(pm, nx, ny){
  nice=true;
  points=100;
}

void Coin::move(){

}

Ledge::Ledge(QPixmap *pm, int nx, int ny) : Item(pm, nx, ny){
  touched=false;
  nice=true;
  counter=0;
}

void Ledge::move(){
  if(touched){
    counter++;
  }
  if(counter==50){
  y+=3;
  setPos(x,y);
  if(y>=780){
    alive=false;
  }
  }
}

void Ledge::stood(){
  touched=true;
}

BBoulder::BBoulder(QPixmap *pm, int nx, int ny) : Item(pm, nx, ny){
  nice=false;
}

void BBoulder::move(){
  y+=2;
  setPos(x,y);
  if(y>=780){
    alive=false;
  }
}
