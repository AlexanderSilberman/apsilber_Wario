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
  name=3;
  iX=nx;
  iY=ny;
}

void Garlic::move(){
  if(y==304 && x<iX+104){
    x+=8;
  }
  if(y==504 && x<=iX+104 && x!=iX){
    x-=8;
  }
  if(x==iX || x==iX+104){
    y+=8;
  }
  
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
  name=1;
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
    x-=5;
  }
  else{
    x+=5;
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
  y+=7.5;
  setPos(x,y);
  if(y>=820){
    alive=false;
  }
}

Coin::Coin(QPixmap *pm, int nx, int ny) : Item(pm, nx, ny){
  nice=true;
  points=100;
  name=2;
}

void Coin::move(){

}

Ledge::Ledge(QPixmap *pm, int nx, int ny) : Item(pm, nx, ny){
  touched=false;
  nice=true;
  counter=0;
  name=4;
}

void Ledge::move(){
  if(touched){
    counter++;
  }
  if(counter>=5){
  y+=7.5;
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
  y+=5;
  setPos(x,y);
  if(y>=820){
    alive=false;
  }
}

Spikes::Spikes(QPixmap *pm, int nx, int ny) :Item(pm, nx, ny){
  nice=false;
  counter=0;
}

void Spikes::move(){
  counter++;
  if(counter<0){
    y+=7.5;
    setPos(x,y);
  }
  else{
  if(counter%50<20){
    y-=8;
    setPos(x,y);
  }
  else if(counter%50<25){

  }
  else if(counter%50<45){
    y+=6;
    setPos(x,y);
  }
  else{

  }
  }
  
}


void Spikes::down(){
  counter=-20;
}
