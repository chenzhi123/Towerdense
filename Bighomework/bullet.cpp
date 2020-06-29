#include "bullet.h"
#include "tower.h"
#include "ks.h"
#include "utility.h"
#include "enemy.h"

#include <QPoint>
#include <QPainter>
#include <QString>
#include <QPropertyAnimation>

const QSize Bullet::m_fixedSize(8,8);

Bullet::Bullet()
{
}

Bullet::Bullet(QPoint startPos,QPoint targetPos,int damage,Enemy * targetEnemy,Ks * game,QString path):
    m_startPos(startPos),
    m_targetPos(targetPos),
    m_damage(damage),
    m_path(path),
    m_targetEnemy(targetEnemy),
    m_game(game)
{
}

QPoint Bullet::getCurrentPos()
{
    return m_currentPos;
}

void Bullet::setCurrentPos(QPoint pos)
{
    m_currentPos=pos;
}

void Bullet::move()
{
    static int duration=200;//子弹飞行的时间（ms)
    QPropertyAnimation * animation=new QPropertyAnimation(this,"m_currentPos");
    animation->setDuration(duration);//持续时间
    animation->setStartValue(m_startPos);//起始位置
    animation->setEndValue(m_targetPos);//目标位置
    connect(animation,SIGNAL(finished()),this,SLOT(hitTarget()));//连接信号槽，击中敌人后，子弹动态运动结束
    animation->start();
}

void Bullet::hitTarget()
{
    if(m_game->getEnemyList().indexOf(m_targetEnemy)!=-1)//敌人列表中，有子弹击中的这个敌人，则敌人受到相应的伤害
    {
        m_targetEnemy->getDamaged(m_damage);
    }
    m_game->removeBullet(this);
}

void Bullet::draw(QPainter *painter) const
{
    painter->drawPixmap(m_currentPos,m_path);
}
