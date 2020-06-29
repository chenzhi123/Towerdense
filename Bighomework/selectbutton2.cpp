#include "selectbutton2.h"

#include "mainwindow.h"
#include <QPainter>
#include <QRect>
#include <QPoint>
#include <QString>
#include "ks.h"
static const int towerupdate1Cost=300;//第一次升级
static const int towerupdate2Cost=400;//第二次升级

const QSize selectButton2::m_fixedSize(100,50);

selectButton2::selectButton2(QPoint pos,Ks * game,int width,int height):
    m_game(game),
    m_pos(pos),
    m_width(width),
    m_height(height)
{
}

selectButton2::~selectButton2()
{
    m_game=NULL;
    m_tower=NULL;
}

QPoint selectButton2::getPos()
{
    return m_pos;
}

void selectButton2::getRemoved()
{
    m_game->removeButton2(this);
}

void selectButton2::setTower(Tower *tower)
{
    m_tower=tower;
}

void selectButton2::draw(QPainter *painter) const
{
    int level=m_tower->getLevel();
    painter->save();
    painter->setPen(Qt::black);
    //不同等级升级的钱不一样，所以画出来也不一样
    if(level==1)
    {
        painter->drawText(QRect(m_pos.x(),m_pos.y(),100,25),QString("update: %1").arg(towerupdate1Cost));
    }
    else
    {
        painter->drawText(QRect(m_pos.x(),m_pos.y(),100,25),QString("update: %1").arg(towerupdate2Cost));
    }
    painter->drawText(QRect(m_pos.x(),m_pos.y()+25,100,25),QString("remove"));//画出移除框
    painter->restore();
}

bool selectButton2::containPos(QPoint pos)
{
    bool xInHere=pos.x()>m_pos.x() && pos.x()<m_pos.x()+m_fixedSize.width();
    bool yInHere=pos.y()>m_pos.y() && pos.y()<m_pos.y()+m_fixedSize.height();
    return xInHere && yInHere;
}
