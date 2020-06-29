#ifndef SELECTBUTTON2_H
#define SELECTBUTTON2_H


#include <QPainter>
#include <QPoint>
#include <QRect>
#include <QSize>

#include "mainwindow.h"
#include "tower.h"
#include "ks.h"

class Tower;
class Ks;
class selectButton2
{
public:
    selectButton2(QPoint pos,Ks * game,int width,int height);
    ~selectButton2();

    void draw(QPainter * painter)const;//绘画button
    void getRemoved();//移除button2
    Tower * getTower();
    void setTower(Tower * tower);//设置该button2防御塔
    bool containPos(QPoint pos);//判断点击点是否在button2的内部
    QPoint getPos();//得到button2的左上点
private:
    Ks * m_game;
    Tower * m_tower;
    QPoint m_pos;
    static const QSize m_fixedSize;
    int m_width;
    int m_height;
};


#endif // SELECTBUTTON2_H
