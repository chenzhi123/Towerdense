#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QPoint>
#include <QPainter>
#include <QString>
#include <QSize>

#include "enemy.h"
#include "tower.h"
#include "mainwindow.h"

class Enemy;
class MainWindow;
class Tower;

class Bullet :public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPoint m_currentPos READ getCurrentPos WRITE setCurrentPos)//子弹动态移动
public:
    Bullet();
    Bullet(QPoint startPos,QPoint targetPos,int damage,Enemy * targetEnemy,MainWindow * game,QString path=":/bullet.png");
    QPoint getCurrentPos();//得到子弹的当前位置
    void setCurrentPos(QPoint pos);//设置子弹的当前位置

    void move();//子弹的移动
    void draw(QPainter * painter)const;//绘画子弹

private slots:
    void hitTarget();//私有信号槽，击中敌人的时候触发

private:
    QPoint m_startPos;
    QPoint m_targetPos;
    QPoint m_currentPos;
    int m_damage;
    QString m_path;

    Enemy * m_targetEnemy;
    MainWindow * m_game;

    static const QSize m_fixedSize;
};


#endif // BULLET_H
