#include "mainwindow.h"

#include <iostream>
using namespace std;

MainWindow::MainWindow(){

  points=100;
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

  wallimg=new QPixmap("wall.png");
  QBrush mountain;
  mountain.setTexture(*wallimg);

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

  QFont font("Times",25);
  QString s="Score: ";
  QString sco=QString::number(points);
  sco=sco.rightJustified(7,'0');
  s=s+sco;
  score=new QGraphicsSimpleTextItem(s);
  score->setFont(font);
  QPointF p(20,10);
  score->setPos(p);
  score->setZValue(2);
  scene->addItem(score);

  timer=new QTimer(this);
  timer->setInterval(20);
  connect(timer, SIGNAL(timeout()), this, SLOT(handleTimer()));

  garlicimg=new QPixmap("garlic.png");

  warioimg=new QPixmap("Wario.png");
  bigboulderimg=new QPixmap("bigboulder.png");
  diamondimg=new QPixmap("diamond.png");
  coinimg=new QPixmap("Coin.png");
  ledgeimg=new QPixmap("ledge.png");
  smallrockimg=new QPixmap("smallrock.png");

  warioimg->scaled(500,500,Qt::IgnoreAspectRatio);

}

MainWindow::~MainWindow(){
}

void MainWindow::keyPressEvent(QKeyEvent *e){
  switch(e->key()){
  case Qt::Key_Left:  war->direction(-3,0);
    break;
  case Qt::Key_Right:  war->direction(3,0);
    break;
  case Qt::Key_Up: war->direction(0,-3);
    break;
  case Qt::Key_Down:  war->direction(0,3);
    break;
  }

}

void MainWindow::keyReleaseEvent(QKeyEvent *e){
  switch(e->key()){
  case Qt::Key_Left:  war->direction(3,0);
    break;
  case Qt::Key_Right:  war->direction(-3,0);
    break;
  case Qt::Key_Up: war->direction(0,3);
    break;
  case Qt::Key_Down:  war->direction(0,-3);
    break;
  }

}

void MainWindow::stop(){
  if(timer->isActive()){
    timer->stop();
  }
  else{
    timer->start();
  }
}



void MainWindow::handleTimer(){
  counter++;
  if(counter==100){
    counter=0;
  }
  for(int i=0;i<list.size();i++){
    if(!(list.at(i)->isAlive())){
      list.removeAt(i);
    
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
	cout<<"DEATH"<<endl;
	delete war;

      }
      delete list.at(i);
      list.removeAt(i);
    }
      	
  }
   
}
void MainWindow::begin(){

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
