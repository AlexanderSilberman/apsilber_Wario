#include "mainwindow.h"

#include <iostream>
using namespace std;

/**Constuctor of main window which holds all of the main functions of the program*/
MainWindow::MainWindow(){
  /**Set up the initial values*/
  timeout=40;
  counter=0;
  started=false;
  ended=false;
  lives=2;
  points=100;
  total=0;
  coins=0;
  randgarlic=rand()%4+3;
  randsboulder=rand()%4;
  randbboulder=rand()%2;
  spikescreate=false;
  ledgecreate=false;
  

  /**Creates a menu bar with pause, start, and exit under File. Connects the actions to various functions*/
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


  /**Creates the background for the scene*/
  wallimg=new QPixmap("wall.png");
  QBrush mountain;
  mountain.setTexture(*wallimg);

  /**Creates the scene and the scoring section*/
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

  /**Creates the score text*/
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

  /**Create the Lives text*/
  QString l="Lives: ";
  l+=QString::number(lives);
  life=new QGraphicsSimpleTextItem(l);
  life->setFont(font);
  QPointF p1(10,10);
  life->setPos(p1);
  life->setZValue(2);
  scene->addItem(life);

  /** Creates a timer and sets its interval and connects it to handleTimer */
  timer=new QTimer(this);
  timer->setInterval(timeout);
  connect(timer, SIGNAL(timeout()), this, SLOT(handleTimer()));


  /**Creates the pixmaps for the various items*/
  garlicimg=new QPixmap("garlic.png");
  warioimg=new QPixmap("Wario.png");
  bigboulderimg=new QPixmap("bigboulder.png");
  diamondimg=new QPixmap("diamond.png");
  coinimg=new QPixmap("Coin.png");
  ledgeimg=new QPixmap("ledge.png");
  smallrockimg=new QPixmap("smallrock.png");
  spikesimg=new QPixmap("spikes.png");

  r=new QGraphicsRectItem(200,200,400,400);
  r->setBrush(brush);
  scene->addItem(r);

  QString l1="Control Wario with arrow keys";
  QString l2="Diamonds and coins add points";
  QString l3="Boulders and spikes hurt";
  QString l4="Garlic gives you extra lives";
  QString l5="Ledges will push the spikes down";

  line1=new QGraphicsSimpleTextItem(l1);
  line1->setFont(font);
  QPointF p2(200,210);
  line1->setPos(p2);
  line1->setZValue(2);
  scene->addItem(line1);
  line2=new QGraphicsSimpleTextItem(l2);
  line2->setFont(font);
  QPointF p3(200,240);
  line2->setPos(p3);
  line2->setZValue(2);
  scene->addItem(line2);
  line3=new QGraphicsSimpleTextItem(l3);
  line3->setFont(font);
  QPointF p4(200,270);
  line3->setPos(p4);
  line3->setZValue(2);
  scene->addItem(line3);
  line4=new QGraphicsSimpleTextItem(l4);
  line4->setFont(font);
  QPointF p5(200,300);
  line4->setPos(p5);
  line4->setZValue(2);
  scene->addItem(line4);
  line5=new QGraphicsSimpleTextItem(l5);
  line5->setFont(font);
  QPointF p6(200,330);
  line5->setPos(p6);
  line5->setZValue(2);
  scene->addItem(line5);

}

MainWindow::~MainWindow(){
for(int i=0;i<list.size();i++){
      delete list.at(i);
      
    }
    list.clear();
}

/** Multiplies the timer interval by 0.15 and sends it to wario's direction function in a different direction for each arrow key press. Setting it by the timer interval keeps wario at the same speed while everything else speeds up. */
void MainWindow::keyPressEvent(QKeyEvent *e){
  if(!started){
    return;
  }
  float dir=0.1*timeout;
  
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
/** Sends 9 to direction to reset the x or y velocity of wario when a key is released. Only activates if the game has been started. */
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
/**Starts the timer or stops the timer to pause and unpause the game */
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
/** Called when the counter reaches an interval of 10 and creates an item on the screen based on the counter number. */
void MainWindow::create(int count){

 switch(count){
   /**Every 500 timeouts the timer interval decreases by 1 */
 case 10:{
   total++;
   if(total%5==0){
     if(timeout!=20){
       timeout--;
     }
   }
   /** after 300 timeouts there is a 33% chance the spikes will be created */
   if(total>=3 && !spikescreate){
     int s=rand()%3;
     if(s==2){
       Spikes* spike=new Spikes(spikesimg, 0,800);
       scene->addItem(spike);
       list.push_back(spike);
       spikescreate=true;
     }
   }
   timer->setInterval(timeout);
   if(randbboulder==0){
     int xrand=rand()%800;
     BBoulder* big=new BBoulder(bigboulderimg,xrand,-20);
     scene->addItem(big);
     list.push_back(big);
     randbboulder=rand()%2;
   }
     break;
 }
 case 20:{
   if(randsboulder==0){
     int xrand=rand()%800;
     SBoulder* small=new SBoulder(smallrockimg,xrand,-20);
     scene->addItem(small);
     list.push_back(small);
     randsboulder=rand()%4;
   }
   break;
 }
 case 30:{
   int r=rand()%2;
   if(r==0){
     int yrand=rand()%780;
     int dirrand=rand()%2;
     Diamond *dia=NULL;
     if(dirrand==0){
       dia=new Diamond(diamondimg, 810,yrand);
     }
     if(dirrand==1){
       dia=new Diamond(diamondimg,-20,yrand);
     }
     scene->addItem(dia);
     list.push_back(dia);
     break;
   }
 }
 case 40:{
   if(randsboulder==1){
     int xrand=rand()%800;
     SBoulder* small=new SBoulder(smallrockimg,xrand,-20);
     scene->addItem(small);
     list.push_back(small);
     randsboulder=rand()%4;
   }
   break;
 }

 case 50:{
   if(total==randgarlic){
     int xrand=200+rand()%400;
     Garlic* gar=new Garlic(garlicimg,xrand,0);
     scene->addItem(gar);
     list.push_back(gar);
     randgarlic=rand()%4+3;
   }
   break;
 }
 case 60:{
   int r=rand()%4;
   if(!ledgecreate && r==3){
     int xrand=rand()%600;
     int yrand=rand()%300+50;
     led=new Ledge(ledgeimg,xrand,yrand);
     scene->addItem(led);
     list.push_back(led);
   }
 }


case 70:{
   if(randsboulder==2){
     int xrand=rand()%800;
     SBoulder* small=new SBoulder(smallrockimg,xrand,-20);
     scene->addItem(small);
     list.push_back(small);
     randsboulder=rand()%4;
   }
   break;
 }
 case 80:{
   if(randbboulder==0){
     int xrand=rand()%800;
     BBoulder* big=new BBoulder(bigboulderimg,xrand,-20);
     scene->addItem(big);
     list.push_back(big);
     randbboulder=rand()%2;
   }
   break;
 }
case 90:{
   if(randsboulder==3){
     int xrand=rand()%800;
     SBoulder* small=new SBoulder(smallrockimg,xrand,-20);
     scene->addItem(small);
     list.push_back(small);
     randsboulder=rand()%4;
   }
   break;
 }
 }
}

/**Series of events that are called every time the timer timesout mostly involved with checking collisions and moving objects */
void MainWindow::handleTimer(){
  counter++;
  /**resets the counter every 100 ticks*/
  if(counter==100){
    counter=0;
  }
  if(counter%10==0){
    create(counter);
  }
  /**If an item goes off screen it will be deleted and removed from the list. */
  for(int i=0;i<list.size();i++){
    if(!(list.at(i)->isAlive())  && i!=0){
      list.removeAt(i);
    }
  }
  /**If Wario goes off screen he will lose a life */
  if(!(list.at(0)->isAlive())){
    setLives(-1);
  }
  /**Initiate movement for every item on the screen */
  for(int i=0;i<list.size();i++){
    list.at(i)->move();
  }
  /** Collision detection for wario who is always in the 0th spot of the list. */
  for(int i=1;i<list.size();i++){
    if(list.at(0)->collidesWithItem(list.at(i))){
      /**Different actions for any of the "good" items */
      int name=list.at(i)->getName();
      if(list.at(i)->getNice()){
	if(name==1 || name==2 ){
	  changePoints(i);
	}
	if(name==3){
	  setLives(1);
	}
	if(name==4){
	  led->stood();
	}
      }
      /*Any bad items kills Wario at this stage of the game production */
      else{
	setLives(-1);
	if(!started){
	  return;
	}
      }
      if(name!=4){
	delete list.at(i);
	list.removeAt(i);
      }
     
    }
      	
  }
  if(spikescreate && ledgecreate){
    if(spike->collidesWithItem(led)){
      spike->down();
    }
  }
}
/** Gets the point value from the item and adds it to the total point value. Creates a new string for scores and sets the score text to the new string.
@param i The location in the list of the item collided with */
void MainWindow::changePoints(int i){
  /**If game is being reset  i will be 1 and points will be returned to 100 */
  if(i==-1){
    points=100;
  }
  /**Otherwise find the point value of the item collided with and add that to the point total */
  else{
    i=list.at(i)->getPoints();
    points+=i;
  }
  /** If a coin is encounter (point value 100) decrease the number of coins on map and call new level if there are no more coins */
  if(i==100){
    coins--;
    if(coins==0){
      newLevel();
    }
  }
  /** Change the text */
  QFont font("Times",25);
  QString s="Score: ";
  QString sco=QString::number(points);
  sco=sco.rightJustified(7,'0');
  s=s+sco;
  score->setText(s);
}

/** Changes the number of lives the player has remaining. 
    @param num Number of lives gained (usually 1 or -1) */
void MainWindow::setLives(int num){
  lives+=num;
  if(lives>=0){
    /**If number of lives is not negative change the text on the lives section */
    QFont font("Times",25);
    QString l="Lives: ";
    l+=QString::number(lives);
    life->setText(l);
    if(num<0){
      war->reset();
    }
  }
  /**Otherwise delete wario and stop the game */
  else{
    delete war;
    list.removeAt(0);
    started=false;
    ended=true;
    timer->stop();
    return;
  }
}

/**Initialization of the game and resetting function */

void MainWindow::begin(){
  /**If being used to reset the game it deletes every item in the list, resets lives,points and the timer interval */
  if(started || ended){
    for(int i=0;i<list.size();i++){
      delete list.at(i);
      
    }
    list.clear();
    points=100;
    timeout=40;
    lives=2;
    setLives(0);
    changePoints(-1);
  }
  else{
    delete r;
    delete line1;
    delete line2;
    delete line3;
    delete line4;
    delete line5;
  }
  started=true;
  /**Creates Wario */
  war=new Wario(warioimg, 500, 500);
  scene->addItem(war);
  list.push_back(war);

  /**Starts timer and gives a free diamond, garlic, and boulder */
  timer->start();
  Garlic* garlic1=new Garlic(garlicimg,400, 000);
  scene->addItem(garlic1);
  list.push_back(garlic1);

  Diamond* diamond1=new Diamond(diamondimg,0,400);
  scene->addItem(diamond1);
  list.push_back(diamond1);

  SBoulder* sboulder=new SBoulder(smallrockimg,400,0);
  scene->addItem(sboulder);
  list.push_back(sboulder);

  newLevel();
}

/** Sends Wario back to his original location and creates the coins and decreases the timeout interval by 1 */
void MainWindow::newLevel(){
  war->reset();
  /** 5-8 coins will be created on the map*/
  int num=5+rand()%4;
  QList<int> c;
  /**List of all possible cases is created */
  for(int i=0;i<10;i++){
    c.push_back(i);
  }
  /**For the number of coins that will be created a random slot in the list will be chosen, the case value it points to will be stored in ran, and removed from the list. Then the coin of that case will be created */
  for(int i=0;i<num;i++){
    coins++;
    int r=rand()%(c.size());
    int ran=c.at(r);
    c.removeAt(r);
    Coin* coin1=NULL;
    switch(ran){
    case 0:{ coin1=new Coin(coinimg,200,400); break;}
    case 1:{ coin1=new Coin(coinimg,200,400); break;}
    case 2:{ coin1=new Coin(coinimg,450,120); break;}
    case 3:{ coin1=new Coin(coinimg,70,700); break;}
    case 4:{ coin1=new Coin(coinimg,700,200); break;}
    case 5:{ coin1=new Coin(coinimg,400,400); break;}
    case 6:{ coin1=new Coin(coinimg,200,400); break;}
    case 7:{ coin1=new Coin(coinimg,489,700); break;}
    case 8:{ coin1=new Coin(coinimg,660,180); break;}
    case 9:{ coin1=new Coin(coinimg,389,618); break;}
    }
    scene->addItem(coin1);
    list.push_back(coin1);
  }
  if(timeout!=20){
    timeout--;
  }
}
/** Resets focus to the mainwindow if the main window is clicked (currently does nothing due to no other mainwindow widgets besides the scene */
void MainWindow::mousePressEvent(QGraphicsSceneMouseEvent *e){
  e=e;
setFocus();
}
/**Upon creation of the viewindow sets focus on the mainwindow.
@param nscene The scene the view will be part of.
@param main A pointer to the main window so it can set focus */
ViewWindow::ViewWindow(QGraphicsScene* nscene, QMainWindow* main) : QGraphicsView(nscene){
  main->setFocus();
}

/** Constructor for the Graphics Screen
    @param main Pointer to the main window so it can set focus when clicked on */
Screen::Screen(QMainWindow* main){
  main_=main;
}

/** Mouse Press Event that sets the focus back to the main window */
void Screen::mousePressEvent(QGraphicsSceneMouseEvent *e){
  e=e;
  main_->setFocus();
}
