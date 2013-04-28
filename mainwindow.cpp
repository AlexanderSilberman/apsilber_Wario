#include "mainwindow.h"

#include <iostream>
using namespace std;

MainWindow::MainWindow(){
  /*Set up the initial values*/
  timeout=20;
  counter=0;
  started=false;
  lives=2;
  points=100;
  total=0;

  /*Creates a menu bar with pause, start, and exit under File. Connects the actions to various functions*/
  mb=menuBar();
  QMenu *fileMenu = new QMenu("File",this);
  mb->addMenu(fileMenu);
  QAction *exitAction = new QAction("Exit",this);
  QAction *pauseAction = new QAction("Pause",this);
  QAction *startAction = new QAction("Start",this);
  fileMenu->addAction(startAction);
  connect(startAction,SIGNAL(triggered()), this, SLOT(begin()));
  fileMenu->addAction(pauseAction);
  connect(pauseAction,SIGNAL(triggered()), this, SLOT(stop()));
  fileMenu->addAction(exitAction);
  connect(exitAction,SIGNAL(triggered()),qApp, SLOT(quit()));


  /*Creates the background for the scene*/
  wallimg=new QPixmap("wall.png");
  QBrush mountain;
  mountain.setTexture(*wallimg);

  /*Creates the scene and the scoring section*/
  scene=new Screen(this);
  scene->setBackgroundBrush(mountain);
  scene->setSceneRect(0,0,700,700);
  view=new ViewWindow(scene,this);
  view->setAlignment(Qt::AlignLeft | Qt::AlignTop);
  view->setWindowTitle("Wario's Treasure Mountain");
  view->setFixedSize(800,800);
  setCentralWidget(view);
  QBrush brush(Qt::white);
  scene->addRect(0,0,500,50,QPen(),brush);

  /*Creates the score text*/
  QFont font("Times",25);
  QString s="Score: ";
  QString sco=QString::number(points);
  sco=sco.rightJustified(7,'0');
  s=s+sco;
  score=new QGraphicsSimpleTextItem(s);
  score->setFont(font);
  QPointF p(200,10);
  score->setPos(p);
  score->setZValue(2);
  scene->addItem(score);

  /*Create the Lives text*/
  QString l="Lives: ";
  l+=QString::number(lives);
  life=new QGraphicsSimpleTextItem(l);
  life->setFont(font);
  QPointF p1(10,10);
  life->setPos(p1);
  life->setZValue(2);
  scene->addItem(life);

  timer=new QTimer(this);
  timer->setInterval(timeout);
  connect(timer, SIGNAL(timeout()), this, SLOT(handleTimer()));



  garlicimg=new QPixmap("garlic.png");
  warioimg=new QPixmap("Wario.png");
  bigboulderimg=new QPixmap("bigboulder.png");
  diamondimg=new QPixmap("diamond.png");
  coinimg=new QPixmap("Coin.png");
  ledgeimg=new QPixmap("ledge.png");
  smallrockimg=new QPixmap("smallrock.png");


}

MainWindow::~MainWindow(){
}

void MainWindow::keyPressEvent(QKeyEvent *e){
  if(!started){
    return;
  }
  float dir=0.15*timeout;
  switch(e->key()){
  case Qt::Key_Left:  war->direction(-dir,0);
    break;
  case Qt::Key_Right:  war->direction(dir,0);
    break;
  case Qt::Key_Up: war->direction(0,-dir);
    break;
  case Qt::Key_Down:  war->direction(0,dir);
    break;
  }

}

void MainWindow::keyReleaseEvent(QKeyEvent *e){
  if(!started){
    return;
  }
  switch(e->key()){
  case Qt::Key_Left:  war->direction(9,0);
    break;
  case Qt::Key_Right:  war->direction(9,0);
    break;
  case Qt::Key_Up: war->direction(0,9);
    break;
  case Qt::Key_Down:  war->direction(0,9);
    break;
  }

}

void MainWindow::stop(){
  if(!started){
    return;
  }

  if(timer->isActive()){
    timer->stop();
  }
  else{
    timer->start();
  }
}

void MainWindow::create(int count){

 switch(count){
 case 10:{
   total++;
   if(timeout!=1){
   timeout--;
   }
   timer->setInterval(timeout);
   
   int xrand=rand()%800;
   BBoulder* big=new BBoulder(bigboulderimg,xrand,-20);
   scene->addItem(big);
   list.push_back(big);
   break;
 }
 case 20:{
   int xrand=rand()%800;
   SBoulder* small=new SBoulder(smallrockimg,xrand,-20);
   scene->addItem(small);
   list.push_back(small);
   break;
 }
 case 30:{
   int yrand=rand()%780;
   Diamond* dia=new Diamond(diamondimg,-20,yrand);
   scene->addItem(dia);
   list.push_back(dia);
   break;
 }
 }
}


void MainWindow::handleTimer(){
  counter++;
  if(counter==100){
    counter=0;
  }
  if(counter%10==0){
    create(counter);
  }
  for(int i=0;i<list.size();i++){
    if(!(list.at(i)->isAlive())  && i!=0){
      list.removeAt(i);
    }
  }
  if(!(list.at(0)->isAlive())){
    lives--;
    if(lives>=0){
    QFont font("Times",25);
    QString l="Lives: ";
    l+=QString::number(lives);
    life->setText(l);
    
      war->reset();
    }
    else{
      cout<<"DEATH"<<endl;
      delete war;
      started=false;
      timer->stop();
      return;
    }

  }
  for(int i=0;i<list.size();i++){
    list.at(i)->move();
  }
  for(int i=1;i<list.size();i++){
    if(list.at(0)->collidesWithItem(list.at(i))){
      if(list.at(i)->getNice()){
	points+=list.at(i)->getPoints();
	QFont font("Times",25);
	QString s="Score: ";
	QString sco=QString::number(points);
	sco=sco.rightJustified(7,'0');
	s=s+sco;

	score->setText(s);

      }
      else{
	lives--;
	if(lives>=0){
	  QFont font("Times",25);
	  QString l="Lives: ";
	  l+=QString::number(lives);
	  life->setText(l);
	  cout<<"died"<<endl;
	  war->reset();
	}
	else{
	  cout<<"DEATH"<<endl;
	  delete war;
	  started=false;
	  timer->stop();
	  return;
	}

      }
      delete list.at(i);
      list.removeAt(i);
    }
      	
  }
   
}
void MainWindow::begin(){
  if(started){
    for(int i=1;i<list.size();i++){
      delete list.at(i);
      
    }
    list.clear();
  }
  started=true;
  war=new Wario(warioimg, 500, 500);
  scene->addItem(war);
  list.push_back(war);


  timer->start();
  Garlic* garlic1=new Garlic(garlicimg,200, 200);
  scene->addItem(garlic1);
  list.push_back(garlic1);

  Diamond* diamond1=new Diamond(diamondimg,0,400);
  scene->addItem(diamond1);
  list.push_back(diamond1);

  SBoulder* sboulder=new SBoulder(smallrockimg,400,0);
  scene->addItem(sboulder);
  list.push_back(sboulder);

  //int num=5+rand()%3;
  coins=3;
  QList<int> c;
  int cas=rand()%4;
  switch(cas){
  case 0:{ c.push_back(1); c.push_back(5); c.push_back(8); break;}
  case 1:{c.push_back(2); c.push_back(3); c.push_back(6); break;}
  case 2:{c.push_back(3); c.push_back(7); c.push_back(4); break;}
  case 3:{c.push_back(4); c.push_back(0); c.push_back(9); break;}
  }
  for(int i=0;i<3;i++){
    int ran=c.at(i);
    Coin* coin1;
    switch(ran){
    case 0:{ coin1=new Coin(coinimg,200,400);c.push_back(0); break;}
    case 1:{ coin1=new Coin(coinimg,200,400);c.push_back(1); break;}
    case 2:{ coin1=new Coin(coinimg,450,120);c.push_back(2); break;}
    case 3:{ coin1=new Coin(coinimg,10,700);c.push_back(3); break;}
    case 4:{ coin1=new Coin(coinimg,700,200);c.push_back(4); break;}
    case 5:{ coin1=new Coin(coinimg,400,400);c.push_back(5); break;}
    case 6:{ coin1=new Coin(coinimg,200,400);c.push_back(6); break;}
    case 7:{ coin1=new Coin(coinimg,489,20);c.push_back(7); break;}
    case 8:{ coin1=new Coin(coinimg,660,180);c.push_back(8); break;}
    case 9:{ coin1=new Coin(coinimg,389,618);c.push_back(9); break;}
    }
    scene->addItem(coin1);
    list.push_back(coin1);
  }


}

void MainWindow::mousePressEvent(QGraphicsSceneMouseEvent *e){
  e=e;
}

ViewWindow::ViewWindow(QGraphicsScene* nscene, QMainWindow* main) : QGraphicsView(nscene){
  main->setFocus();
}


Screen::Screen(QMainWindow* main){
  main_=main;
}

void Screen::mousePressEvent(QGraphicsSceneMouseEvent *e){
  e=e;
  main_->setFocus();
}
