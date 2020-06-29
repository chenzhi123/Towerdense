#include "ks.h"
#include "waypoint.h"
#include "towerposition.h"
#include "tower.h"
#include <QPainter>
#include <QTimer>
#include "enemy.h"
#include "button.h"
#include "selectbutton.h"
#include "selectbutton2.h"
#include<QMediaPlayer>
#include "mainwindow.h"
static const int tower1Cost=250;//第一种塔的价钱
static const int tower2Cost=500;//第二种塔的价钱
static const int tower3Cost=750;//第三种塔的价钱
QMediaPlayer *player2 = new QMediaPlayer;//游戏音乐
Ks::Ks(QWidget *parent)
    : QMainWindow(parent)
    , m_playerHp(5)
    , m_playerGlod(1000)
    ,m_waves(0)
    ,m_gameWin(false)
    ,m_gameLose(false)

{
    this->setFixedSize(1000,600);
    addWayPoint1();
    loadTowerPosition1();
    QTimer * timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateMap()));
    timer->start(30);
    QTimer::singleShot(300,this,SLOT(gameStart()));
    Button*backbtn=new Button(":/gameover.png");//返回按钮
    backbtn->setParent(this);
    backbtn->move(40,40);
    connect(backbtn,&Button::clicked,this,[=](){
        emit chooseback();
    });
    QMediaPlayer *player2 = new QMediaPlayer;//游戏音乐
    player2->setMedia(QUrl("qrc:/gamebgm.mp3"));//
    player2->setVolume(2);
    player2->play();


}

Ks::~Ks()
{
   // delete ui;
}
void Ks::paintEvent(QPaintEvent*)
{
    player2->play();
    if(m_gameLose)
        {
            player2->stop();
            QMediaPlayer *player3 = new QMediaPlayer;//失败音乐
            player3->setMedia(QUrl("qrc:/"));//
            player3->setVolume(30);
            player3->play();

            QString text="Defeat";
            QPainter painter(this);
            painter.setPen(Qt::red);
            painter.drawText(rect(),Qt::AlignCenter,text);
            return ;
        }
else if(m_gameWin)
    {
        player2->stop();
        QMediaPlayer *player4 = new QMediaPlayer;//胜利音乐
        player4->setMedia(QUrl("qrc:/"));//
        player4->setVolume(30);
        player4->play();
        QString text="Victory";
        QPainter painter(this);
        painter.setPen(Qt::red);
        painter.drawText(rect(),Qt::AlignCenter,text);
        return ;
    }
    QPainter painter(this);
    QString path(":/map.jpg");
    painter.drawPixmap(0,0,1000,600,path);
    foreach(const wayPoint * waypoint,m_wayPointList)
            waypoint->draw(&painter);
    foreach(const TowerPosition towerposition,m_towerPositionList)
           towerposition.draw(&painter);
    foreach(const Tower * tower, m_towerList)
            tower->draw(&painter);
    foreach(const Enemy * enemy,m_enemyList)
            enemy->draw(&painter);
    foreach(const Bullet * bullet,m_bulletList)
            bullet->draw(&painter);
    foreach(const selectButton * button,m_selectButtonList)
            button->draw(&painter);

    drawHp(&painter);
    drawGlod(&painter);
    drawWaves(&painter);

}
void Ks::addWayPoint1(){
    wayPoint *waypoint1 = new wayPoint(QPoint(25,330));
    m_wayPointList.push_back(waypoint1);

    wayPoint * waypoint2=new wayPoint(QPoint(500,330));
        waypoint1->setNextWayPoint(waypoint2);
        m_wayPointList.push_back(waypoint2);
    wayPoint * waypoint3=new wayPoint(QPoint(500,175));
            waypoint2->setNextWayPoint(waypoint3);
            m_wayPointList.push_back(waypoint3);
     wayPoint * waypoint4=new wayPoint(QPoint(660,175));
            waypoint3->setNextWayPoint(waypoint4);
            m_wayPointList.push_back(waypoint4);
     wayPoint * waypoint5=new wayPoint(QPoint(660,275));
                   waypoint4->setNextWayPoint(waypoint5);
                   m_wayPointList.push_back(waypoint5);
     wayPoint * waypoint6=new wayPoint(QPoint(990,275));
                   waypoint5->setNextWayPoint(waypoint6);
                   m_wayPointList.push_back(waypoint6);

}
void Ks::loadTowerPosition1()
{
    //防御塔坑点
    QPoint pos[]=
    {
        QPoint(100,240),
        QPoint(100,400),
        QPoint(400,240),
        QPoint(400,400),
        QPoint(250,240),
        QPoint(250,400),
        QPoint(565,240),
        QPoint(565,325),
        QPoint(725,175),
        QPoint(700,350),
        QPoint(825,175),
        QPoint(800,350),
        QPoint(400,140),
        QPoint(900,350),
        QPoint(565,75),
        QPoint(500,75),
        QPoint(630,75),
    };
    int len=sizeof(pos)/sizeof(pos[0]);
    for(int i=0;i<len;i++)
    {
        m_towerPositionList.push_back(pos[i]);
    }
}
void Ks::mousePressEvent(QMouseEvent * event)
{
    QPoint pressPos=event->pos();
    auto it=m_towerPositionList.begin();
    while(it!=m_towerPositionList.end())
        {
        if(Qt::LeftButton==event->button())//左键点击
        {//左键点击实现防御塔选择
            if(it->ContainPos(pressPos) && !it->hasButton() && !it->hasTower() )
            {
                QPoint tmp(it->getPos().x()-45,it->getPos().y()-45);
                selectButton * button=new selectButton(tmp,this);
                m_selectButtonList.push_back(button);//
                it->setButton(button);
                it->setHasButton(true);
                update();
                break;
            }
                          else if(it->hasButton() && it->getButton()->containPos(pressPos) && !it->hasTower())//如果这个位置有button，并且没有防御塔
                {
                    if(pressPos.x()<it->getButton()->getPos().x()+35 && canBuyTower())//如果鼠标点击的地方在第一张图片内，创造第一个防御塔
                    {
                        it->setHasTower1(true);
                        m_playerGlod-=tower1Cost;
                        QString path=":/ta2.png";
                        Tower * tower=new Tower(it->getCenterPos(),this,path,2,100);//
                        m_towerList.push_back(tower);
                    }
                    else if(pressPos.x()>it->getButton()->getPos().x()+35 && pressPos.x()<it->getButton()->getPos().x()+70
                            && canBuyTower2())
                    {
                        it->setHasTower2(true);
                        m_playerGlod-=tower2Cost;
                        QString path=":/ta3.png";
                        Tower * tower=new Tower(it->getCenterPos(),this,path,4,120);//
                        m_towerList.push_back(tower);
                    }
                    else if(pressPos.x()>it->getButton()->getPos().x()+70 && pressPos.x()<it->getButton()->getPos().x()+105
                            && canBuyTower3())
                    {
                        it->setHasTower3(true);
                        m_playerGlod-=tower3Cost;
                        QString path=":/tower.png";
                        Tower * tower=new Tower(it->getCenterPos(),this,path,6,140);
                        m_towerList.push_back(tower);
                    }

                    it->getButton()->getRemoved();
                    it->setButton(NULL);
                    it->setHasButton(false);
                    update();
                    break;
                }
            }
                 ++it;
        }

}
void Ks::getHpDamaged()
{
    m_playerHp-=1;//进入基地减一滴血
    if(m_playerHp<=0)
    {
        doGameOver();
    }
}

void Ks::awardGlod()
{
    m_playerGlod+=100;//杀死一个敌人的奖励，
}

void Ks::removeEnemy(Enemy *enemy)
{
    Q_ASSERT(enemy);
    m_enemyList.removeOne(enemy);//死亡的敌人从enemylist中移除
    delete enemy;
    if(m_enemyList.empty())
        {
            ++m_waves;
            if(!loadWaves())
            {
                m_gameWin=true;
            }
        }
}

QList<Enemy *> Ks::getEnemyList()
{
    return m_enemyList;
}
bool Ks::loadWaves()
{
    if(m_waves>=6)
    {
        return false;
    }
    int enemyStartInterval[]={2000,3000,4000,5000,6000,7000};//敌人出现的时间
    for(int i=0;i<6;++i)
    {
        wayPoint * startWayPoint;
        startWayPoint=m_wayPointList.first();
        Enemy * enemy=new Enemy(startWayPoint,this);//创建一个新的enemy
        m_enemyList.push_back(enemy);
        enemy->HpUP(40+60*m_waves);//随着波数增加，怪物的血量一波增加60点
        QTimer::singleShot(enemyStartInterval[i],enemy,SLOT(doActive()));
    }
    return true;
}

void Ks::gameStart()
{
    loadWaves();
}

void Ks::updateMap()
{
    foreach(Enemy * enemy,m_enemyList)
        enemy->move();
    foreach(Tower * tower,m_towerList)
        tower->checkEnemyInRange();
    update();
}
void Ks::doGameOver()
{
    if(!m_gameLose)
    {
        m_gameLose=true;
    }
}
void Ks::drawWaves(QPainter *painter) const
{
    painter->save();
    painter->setPen(Qt::red);
    painter->drawText(QRect(500,5,200,50),QString("WAVES: %1").arg(m_waves+1));
    painter->restore();
}

void Ks::drawHp(QPainter *painter) const
{
    painter->save();
    painter->setPen(Qt::red);
    painter->drawText(QRect(250,5,200,50),QString("HP: %1").arg(m_playerHp));
    painter->restore();
}

void Ks::drawGlod(QPainter *painter) const
{
    painter->save();
    painter->setPen(Qt::red);
    painter->drawText(QRect(750,5,200,50),QString("GLOD: %1").arg(m_playerGlod));
}

void Ks::removeBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);
    m_bulletList.removeOne(bullet);

}

void Ks::addBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);
    m_bulletList.push_back(bullet);
}
bool Ks::canBuyTower()
{
    if(m_playerGlod>=tower1Cost)
    {
        return true;
    }
    return false;
}

bool Ks::canBuyTower2(){
    if(m_playerGlod>=tower2Cost)
        {
            return true;
        }
        return false;
}
bool Ks::canBuyTower3(){
    if(m_playerGlod>=tower3Cost)
        {
            return true;
        }
        return false;
}
void Ks::removeButton(selectButton *button){
    m_selectButtonList.removeOne(button);
}

