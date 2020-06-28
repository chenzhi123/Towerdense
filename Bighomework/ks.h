#ifndef KS_H
#define KS_H

#include <QMainWindow>
#include<QPaintEvent>
#include <QMouseEvent>
#include "waypoint.h"
#include"towerposition.h"
#include "tower.h"
#include "enemy.h"
#include "bullet.h"
#include "selectbutton.h"

//QT_BEGIN_NAMESPACE
namespace Ui { class Ks; }
//QT_END_NAMESPACE
class wayPoint;
class Tower;
class Enemy;
class Bullet;
class selectButton;
class TowerPosition;
class Ks : public QMainWindow
{
    Q_OBJECT

public:
    Ks(QWidget *parent = nullptr);
    ~Ks();

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
    bool canBuyTower2();//判断是否可以买第二种塔
    bool canBuyTower3();//判断是否可以买第三种塔
    void removeButton(selectButton * button);//在mainwindow中对button进行移除

    void doGameOver();//执行游戏结束

protected:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent *);//鼠标点击类函数

private:
    //Ui::Ks *ui;

    QList<wayPoint * > m_wayPointList;//用来储存航点的list
    QList<TowerPosition > m_towerPositionList;//用来储存防御塔的list
    QList<Tower *> m_towerList;//用来储存防御塔的list
    QList<Enemy *> m_enemyList;//用来储存敌人的list
    QList<Bullet *> m_bulletList;//用来储存子弹的list
    QList<selectButton * > m_selectButtonList;
        int m_playerHp;//基地的血量
        int m_playerGlod;//初始金钱
        int m_waves;//波数
        bool m_gameWin;
        bool m_gameLose;
private slots:
    //私有信号槽，将Enemy，Tower和后续的Bullet连接
    void updateMap();
    void gameStart();
signals:
    void chooseback();
};
#endif // KS_H
