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

int Item::getName(){
  return name;
}

Garlic::Garlic(QPixmap *pm, int nx, int ny) : Item(pm, nx, ny){
}

void Garlic::move(){
  y+=3;
  setPos(x,y);
  nice=true;
}

Wario::Wario(QPixmap *pm, int nx, int ny): Item(pm,nx,ny){
  
  vX=0;
  vY=0;
  
}

void Wario::move(){
  y+=vY;
  x+=vX;
  if(y<=0){
    y=0;
  }
  if(x<=0){
    x=0;
  }
  if(x>=790){
    x=790;
  }
  setPos(x,y);
  if(y>=790){
    alive=false;
  }
}

void Wario::direction(float mX, float mY){
  if(mX==9){
    vX=0;
  }
  else if(mY==9){
    vY=0;
  }
  else{
    vX+=mX;
    vY+=mY;
  }
}

void Wario::reset(){
  x=500;
  y=500;
  setPos(500,500);
  alive=true;
}

Diamond::Diamond(QPixmap *pm, int nx, int ny) : Item(pm, nx, ny){
  nice=true;
  points=1000;
  if(x>0){
    left=true;
  }
  else{
    left=false;
  }
}

void Diamond::move(){
  if(left){
  x-=2;
  }
  else{
    x+=2;
  }
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
  if(y>=820){
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
  if(y>=820){
    alive=false;
  }
}
