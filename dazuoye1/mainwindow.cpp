#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPainter"
#include "QPaintEvent"
#include "QPaintDevice"
#include <QMainWindow>
#include <QPainter>//
#include <QPixmap>
#include <QPaintEvent>
#include <QPushButton>
#include <QDebug>
#include "button.h"
#include "majormap.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->setFixedSize(800,600);
    ui->setupUi(this);
    Button*btn=new Button(":/Leave.png");
    btn->setParent(this);
    btn->move(450,400);
    majormap *scene =new majormap;
    connect(btn,&QPushButton::clicked,this,[=](){
        this->close();
        scene->show();
    });//进入游戏
    connect(scene,&majormap::chooseback,this,[=](){
        scene->hide();
        this->show();
    });//回到主界面


}
void MainWindow::paintEvent(QPaintEvent *)
{
    //qDebug()<<"hello";
    // QPainter painter(this);
    //painter.drawPixmap(0, 0, QPixmap(":/image/Bg.png"));
    QPainter painter(this);
    QPixmap pixmap(":/zhujiemian1.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);

}

MainWindow::~MainWindow()
{
    delete ui;
}

