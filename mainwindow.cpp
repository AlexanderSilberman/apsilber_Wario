#include "mainwindow.h"

#include <iostream>
using namespace std;

MainWindow::MainWindow(){
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
  setCentralWidget(view);
  /*
  scene=new QGraphicsScene();
  view=new QGraphicsView(scene);
  //scene->setFocus();
  
  view->setFixedSize(800,800);
  view->setWindowTitle("Wario's Treasure Mountain");
  view->setAlignment(Qt::AlignLeft | Qt::AlignTop);
  scene->setSceneRect(0,0,700,700);
  */
 
  timer=new QTimer(this);
  timer->setInterval(20);
  connect(timer, SIGNAL(timeout()), this, SLOT(handleTimer()));

  garlicimg=new QPixmap("garlic.png");
  warioimg=new QPixmap("Wario.png");
  bigboulderimg=new QPixmap("bigboulder.png");
  diamondimg=new QPixmap("diamond.png");
  coinimg=new QPixmap("Coin.png");


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
  for(int i=0;i<list.size();i++){
    if(!(list.at(i)->isAlive())){
      list.removeAt(i);
    
    }
  }
  for(int i=0;i<list.size();i++){
    list.at(i)->move();
  }

}

void MainWindow::begin(){
  timer->start();
  Garlic* garlic1=new Garlic(garlicimg,200, 200);
  scene->addItem(garlic1);
  list.push_back(garlic1);

  war=new Wario(warioimg, 500, 500);
  scene->addItem(war);
  list.push_back(war);
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
  main_->setFocus();
}
