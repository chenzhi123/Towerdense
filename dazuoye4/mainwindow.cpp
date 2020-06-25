#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "waypoint.h"
#include "towerposition.h"
#include "tower.h"
#include <QPainter>
#include <QTimer>
#include "enemy.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_playerHp(5)
    , m_playerGlod(1000)
    ,m_waves(0)
    ,m_gameWin(false)
    ,m_gameLose(false)

{
    ui->setupUi(this);
    addWayPoint1();//增加航点函数的调用
    loadTowerPosition1();
    QTimer * timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateMap()));
    timer->start(30);
    QTimer::singleShot(300,this,SLOT(gameStart()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent*)
{
    //添加在函数的前端
    if(m_gameLose || m_gameWin)//画出游戏结束的画面
        {
            QString text=m_gameLose ? "YOU LOST":"YOU WIN";
            QPainter painter(this);
            painter.setPen(Qt::red);
            painter.drawText(rect(),Qt::AlignCenter,text);
            return ;
        }

    QPainter painter(this);
    QString path(":/timg.jfif");//path是你图片的路径
    painter.drawPixmap(0,0,1000,600,path);
    //drawPixmap的前四个参数代表的分别是，图片左上角的横坐标，图片左上角的纵坐标，图片的width，图片的height。我们一般把width和height，与图片的真实大小匹配起来
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

        drawHp(&painter);
        drawGlod(&painter);
        drawWaves(&painter);

}
void MainWindow::addWayPoint1(){
    wayPoint *waypoint1 = new wayPoint(QPoint(25,325));
    m_wayPointList.push_back(waypoint1);

    wayPoint * waypoint2=new wayPoint(QPoint(975,325));
        waypoint1->setNextWayPoint(waypoint2);
        m_wayPointList.push_back(waypoint2);
}
void MainWindow::loadTowerPosition1()
{
    //这里和找航点是一样的，制作者需要自己不断尝试
    //找到比较合适的防御塔坑点
    QPoint pos[]=
    {

        QPoint(300,240),
        QPoint(300,375),
        QPoint(400,240),
        QPoint(400,375),
        QPoint(500,240),
        QPoint(500,375),
        QPoint(600,240),
        QPoint(600,375),
        QPoint(700,240),
        QPoint(700,375),



    };
    int len=sizeof(pos)/sizeof(pos[0]);
    for(int i=0;i<len;i++)
    {
        m_towerPositionList.push_back(pos[i]);
    }
}
void MainWindow::mousePressEvent(QMouseEvent * event)
{
    QPoint pressPos=event->pos();//得到鼠标点击的位置
    auto it=m_towerPositionList.begin();
    while(it!=m_towerPositionList.end())//遍历所有的防御塔坑
    {
        if(Qt::LeftButton==event->button())//如果是鼠标左键点击
        {
            if(it->ContainPos(pressPos) && !it->hasTower() && canBuyTower())//如果鼠标点击的位置在防御塔坑的范围内
            {
                Tower * tower=new Tower(it->getCenterPos(),this);//创建一个新的防御塔
                m_playerGlod-=300;
                m_towerList.push_back(tower);//把这个防御塔放到储存防御塔的list中
                it->setHasTower(true);
                update();//更新地图
                break;//进行了一次操作，可以直接退出循环了
            }
        }
        ++it;
    }
}
void MainWindow::getHpDamaged()
{
    m_playerHp-=1;//敌人进入基地，扣一滴血
    if(m_playerHp<=0)
    {
        doGameOver();
    }
}

void MainWindow::awardGlod()
{
    m_playerGlod+=200;//杀死一个敌人，奖励200，制作者可以自由更改数值
}

void MainWindow::removeEnemy(Enemy *enemy)
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

QList<Enemy *> MainWindow::getEnemyList()
{
    return m_enemyList;
}
bool MainWindow::loadWaves()
{
    if(m_waves>=6)
    {
        return false;
    }
    int enemyStartInterval[]={100,500,600,1000,3000,6000};//敌人出现的时间
    for(int i=0;i<6;++i)
    {
        wayPoint * startWayPoint;
        startWayPoint=m_wayPointList.first();
        Enemy * enemy=new Enemy(startWayPoint,this);//创建一个新得enemy
        m_enemyList.push_back(enemy);
        QTimer::singleShot(enemyStartInterval[i],enemy,SLOT(doActive()));
    }
    return true;
}

void MainWindow::gameStart()
{
    loadWaves();
}

void MainWindow::updateMap()
{
    foreach(Enemy * enemy,m_enemyList)
        enemy->move();
    foreach(Tower * tower,m_towerList)
        tower->checkEnemyInRange();
    update();
}
void MainWindow::doGameOver()
{
    if(!m_gameLose)
    {
        m_gameLose=true;
    }
}

bool MainWindow::canBuyTower()
{
    if(m_playerGlod>=300)
    {
        return true;
    }
    return false;
}

void MainWindow::drawWaves(QPainter *painter) const
{
    painter->save();
    painter->setPen(Qt::red);
    painter->drawText(QRect(500,5,100,25),QString("WAVES: %1").arg(m_waves+1));
    painter->restore();
}

void MainWindow::drawHp(QPainter *painter) const
{
    painter->save();
    painter->setPen(Qt::red);
    painter->drawText(QRect(30,5,100,25),QString("HP: %1").arg(m_playerHp));
    painter->restore();
}

void MainWindow::drawGlod(QPainter *painter) const
{
    painter->save();
    painter->setPen(Qt::red);
    painter->drawText(QRect(300,5,100,25),QString("GLOD: %1").arg(m_playerGlod));
}

void MainWindow::removeBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);
    m_bulletList.removeOne(bullet);

}

void MainWindow::addBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);
    m_bulletList.push_back(bullet);
}
void MainWindow::setPath(QString path)
{
    m_path=path;
}

QString MainWindow::getPath()
{
    return m_path;
}
