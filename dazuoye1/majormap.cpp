#include "majormap.h"
#include <QPainter>
#include <QPixmap>
#include <QPaintEvent>
#include "button.h"
majormap::majormap(QWidget *parent) : QMainWindow(parent)
{
   this->setFixedSize(1000,600);
    Button*backbtn=new Button(":/Leave.png");
    backbtn->setParent(this);
    backbtn->move(40,40);
    Button*setTower =new Button(":/Leave.png");
    setTower->setParent(this);
    setTower->move(500,500);
    connect(setTower,&Button::clicked,this,&majormap::set_tower);
    connect(backbtn,&Button::clicked,this,[=](){
        emit chooseback();
    });

}
void majormap::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pixmap(":/map.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
    foreach(tower *tower,tower_list)
        tower->draw(&painter);
}
void majormap::set_tower(){
 tower *a_new_tower =new tower(QPoint(565,250),":/ta.png");
 tower_list.push_back(a_new_tower);
 update();
}
