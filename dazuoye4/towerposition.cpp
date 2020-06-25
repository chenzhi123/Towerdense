#include "towerposition.h"

#include <QSize>
#include <QPainter>
#include <QPixmap>

const QSize TowerPosition::m_fixedSize(35,35);//设置图片的大小

TowerPosition::TowerPosition(QPoint pos, QString path):
    m_pos(pos),
    m_path(path),
    m_hasTower(false)
{
}

bool TowerPosition::hasTower()
{
    return m_hasTower;
}

void TowerPosition::setHasTower(bool hasTower)
{
    m_hasTower=hasTower;
}

QPoint TowerPosition::getCenterPos()
{
    QPoint tmp;
    tmp.setX(m_pos.x()+m_fixedSize.width()/2);
    tmp.setY(m_pos.y()+m_fixedSize.height()/2);
    return tmp;
}

QPoint TowerPosition::getPos()
{
    return m_pos;
}

bool TowerPosition::ContainPos(QPoint pos)
{
    bool xInHere=pos.x()>m_pos.x() && pos.x()<m_pos.x()+m_fixedSize.width();
    bool yInHere=pos.y()>m_pos.y() && pos.y()<m_pos.y()+m_fixedSize.height();
    return xInHere && yInHere;
}

void TowerPosition::draw(QPainter *painter) const
{
    painter->drawPixmap(m_pos.x(),m_pos.y(),m_path);
}
