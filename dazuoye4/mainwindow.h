#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPaintEvent>
#include <QMouseEvent>
#include "waypoint.h"
#include"towerposition.h"
#include "tower.h"
#include "enemy.h"
#include "bullet.h"
#include "ui_mainwindow.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class wayPoint;
class Tower;
class Enemy;
class Bullet;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void addWayPoint1();//用来添加航点的函数
    void loadTowerPosition1();//用来加载防御塔坑的函数
public:
        void getHpDamaged();//敌人进入基地内部，基地要扣血
        void awardGlod();//敌人死亡，奖励金钱
        void removeEnemy(Enemy * enemy);//敌人死亡，在mainwindow中要移除
        QList<Enemy *> getEnemyList();//得到Enemy*的list
public:
        bool loadWaves();//加载敌人的函数
public:
    void removeBullet(Bullet * bullet);
    void addBullet(Bullet * bullet);
public:
    void drawHp(QPainter * painter)const;//画出当前基地血量的信息
    void drawGlod(QPainter * painter)const;//画出当前玩家金钱的信息
    void drawWaves(QPainter * painter)const;//画出当前的波数信息
    bool canBuyTower();

    void doGameOver();//执行游戏结束

    QString getPath();
    void setPath(QString path);

protected:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent *);//鼠标点击类函数

private:
    Ui::MainWindow *ui;

    QList<wayPoint * > m_wayPointList;//用来储存航点的list
    QList<TowerPosition > m_towerPositionList;//用来储存防御塔坑的list
    QList<Tower *> m_towerList;//用来储存防御塔的list
    QList<Enemy *> m_enemyList;//用来储存敌人的list
    QList<Bullet *> m_bulletList;//用来储存子弹的list
        int m_playerHp;//基地的血量
        int m_playerGlod;//初始金钱
        int m_waves;//波数
        bool m_gameWin;
        bool m_gameLose;
        QString m_path;
private slots:
    //私有信号槽，将Enemy，Tower和后续的Bullet连接
    void updateMap();
    void gameStart();
};
#endif // MAINWINDOW_H
