#include "enemy.h"
#include "ks.h"
#include "tower.h"
#include "utility.h"
#include "waypoint.h"

#include <QPainter>
#include <QPoint>
#include <QSize>
#include <QString>
#include <QVector2D>

const QSize Enemy::m_fixedSize(22,23);//

Enemy::Enemy(wayPoint * startWayPoint,Ks *game,QString path):
    QObject(0),
    m_game(game),
    m_pos(startWayPoint->getPos()),
    m_path(path)
{
    m_maxHp=40;
    m_currentHp=m_maxHp;
    m_walkingSpeed=1;
    m_active=false;
    m_destinationWayPoint=startWayPoint->getNextWayPoint();//直接从当前航点得到下一个航点
}

Enemy::~Enemy()
{
    m_attackerTowerList.clear();//清楚在攻击该敌人的防御塔
    m_destinationWayPoint=NULL;//全部设为空指针
    m_game=NULL;
}

void Enemy::draw(QPainter *painter) const
{
    if(!m_active)//如果敌人不能移动，就不对它进行绘画
    {
        return ;
    }

    painter->save();
    //绘画敌人的血条
    static const int healthBarWidth=m_fixedSize.width();//设置血条的长度
    QPoint healthBarPoint=m_pos+QPoint(-m_fixedSize.width()/2,-m_fixedSize.height());//设置血条的左上点
    painter->setPen(Qt::NoPen);//画笔的颜色
    painter->setBrush(Qt::red);//刷子的颜色，用来填充内部
    QRect healthBarBackRect(healthBarPoint,QSize(healthBarWidth,2));
    painter->drawRect(healthBarBackRect);//画出血条

    //由于敌人被攻击后会扣血，因此还要画一个显示敌人当前血量的柱形
    painter->setBrush(Qt::green);
    QRect healthBarRect(healthBarPoint,QSize((double)m_currentHp/m_maxHp*healthBarWidth,2));
    painter->drawRect(healthBarRect);//画出当前血量血条

    //把敌人画出来
    QPoint tmp(m_pos.x()-m_fixedSize.width()/2,m_pos.y()-m_fixedSize.height()/2);//得到图片的左上点
    painter->drawPixmap(tmp.x(),tmp.y(),m_path);
    painter->restore();
}

void Enemy::move()
{
    if(!m_active)//如果不能移动，就直接return
    {
        return ;
    }
    if(collisionWithCircle(m_pos,1,m_destinationWayPoint->getPos(),1))//如果到达了目标航点
    {
        if(m_destinationWayPoint->getNextWayPoint())//如果还存在下一个航点
        {//重新设置敌人的位置，和目标航点
            m_pos=m_destinationWayPoint->getPos();
            m_destinationWayPoint=m_destinationWayPoint->getNextWayPoint();
        }
        else//如果没有下一个航点了，代表敌人已经到达了基地
        {
            m_game->getHpDamaged();
            m_game->removeEnemy(this);
            return ;
        }
    }
    else//如果还在去目标航点的路上
    {//采用QVectoer2D中的两点移动方法
        QPoint targetPoint=m_destinationWayPoint->getPos();
        double movementSpeed=m_walkingSpeed;
        QVector2D normailzed(targetPoint-m_pos);
        normailzed.normalize();
        m_pos=m_pos+normailzed.toPoint()*movementSpeed;
    }
}

void Enemy::doActive()
{
    m_active=true;
}

QPoint Enemy::getPos()
{
    return m_pos;
}

void Enemy::getAttacked(Tower *tower)
{
    m_attackerTowerList.push_back(tower);
}

void Enemy::getDamaged(int damage)
{
    m_currentHp-=damage;
    if(m_currentHp<=0)
    {
        m_game->awardGlod();
        getRemoved();
    }
}

void Enemy::getRemoved()
{
    if(m_attackerTowerList.empty())
    {
        return ;
    }
    else
    {
        foreach(Tower * tower,m_attackerTowerList)
                    tower->targetKilled();
        m_game->removeEnemy(this);
    }
}

void Enemy::getLostSight(Tower *tower)
{
    m_attackerTowerList.removeOne(tower);
}
void Enemy::HpUP(int maxHp){
    m_maxHp=maxHp;
    m_currentHp=maxHp;
}
