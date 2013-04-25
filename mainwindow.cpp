#include "mainwindow.h"

#include <iostream>
using namespace std;

MainWindow::MainWindow(){
  mb=menuBar();
  mb->addAction("start");
  
  scene=new QGraphicsScene();
  view=new QGraphicsView(scene);
  //scene->setFocus();
  view->setFixedSize(800,800);
  view->setWindowTitle("Wario's Treasure Mountain");
  view->setAlignment(Qt::AlignLeft | Qt::AlignTop);
  scene->setSceneRect(0,0,700,700);
  
  quit=new QPushButton(tr("Quit"));
  connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));
  start=new QPushButton(tr("Start"));
  connect(start,SIGNAL(clicked()), this, SLOT(begin()));
  pause=new QPushButton(tr("pause"));
  connect(pause, SIGNAL(clicked()), this, SLOT(stop()));

  timer=new QTimer(this);
  timer->setInterval(10);
  connect(timer, SIGNAL(timeout()), this, SLOT(handleTimer()));

  wartimer=new QTimer(this);
  wartimer->setInterval(10);
  connect(wartimer, SIGNAL(timeout()), this, SLOT(handleTimer()));
  
  gridLayout=new QGridLayout();
  gridLayout->addWidget(start,0,0);
  gridLayout->addWidget(pause,0,1);
  gridLayout->addWidget(quit,0,2);
  gridLayout->addWidget(view,1,0,3,3);
  setLayout(gridLayout);
  
  garlicimg=new QPixmap("diamond.png");
  warioimg=new QPixmap("diamond.png");

}

MainWindow::~MainWindow(){
}

void MainWindow::keyPressEvent(QKeyEvent *e){
  cout<<"here?"<<endl;
  switch(e->key()){
  case Qt::Key_Left:
    war->direction(-3,0);
  case Qt::Key_Right:
    war->direction(3,0);
  case Qt::Key_Up:
    war->direction(0,-3);
  case Qt::Key_Down:
    war->direction(0,3);
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
  Garlic* garlic1=new Garlic(garlicimg,500, 50);
  scene->addItem(garlic1);
  list.push_back(garlic1);

  Wario* wario1=new Wario(warioimg, 250, 250);
  scene->addItem(wario1);
  list.push_back(wario1);
}
