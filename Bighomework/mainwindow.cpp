#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QPainter>
#include <QPixmap>
#include <QPaintEvent>
#include <QPushButton>
#include <QDebug>
#include "button.h"
#include "ks.h"
#include<QtCore/qmath.h>
#include<QMediaPlayer>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->setFixedSize(1000,600);
    ui->setupUi(this);
    QMediaPlayer *player1 = new QMediaPlayer;//主界面音乐
    player1->setMedia(QUrl("qrc:/Worlds Collide.mp3"));//
    player1->setVolume(30);
    player1->play();
    Button*btn = new Button(":/Leave.png");//进入游戏的按钮
    btn->setParent(this);
    btn->move(450,400);
    Ks*scene =  new Ks;
    connect(btn,&QPushButton::clicked,this,[=](){
        btn->zoomdown();
        btn->zoomup();
        QTimer::singleShot(500,this,[=](){
            this->close();
            scene->show();
            player1->stop();
        });//进入游戏
        connect(scene,&Ks::chooseback,this,[=](){
            scene->hide();
            this->show();
        });//回到主界面

    });
}

void MainWindow:: paintEvent(QPaintEvent*){
    QPainter painter(this);
    QPixmap pixmap(":/zhujiemian1.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
}
MainWindow::~MainWindow()
{
    delete ui;
}

