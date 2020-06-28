#include "selectbutton.h"
const QSize selectButton::m_fixedSize(105,35);

selectButton::selectButton(QPoint pos,Ks * game):
    m_game(game),
    m_pos(pos)
{
    //三张图片的路径信息
    m_selectBoxImagePath[0]=":/tower.png";
    m_selectBoxImagePath[1]=":/ta.png";
    m_selectBoxImagePath[2]=":/tower1.jpg";
}

selectButton::~selectButton()
{
    m_game=NULL;
}

void selectButton::draw(QPainter *painter) const
{
    painter->save();
    painter->drawPixmap(m_pos.x(),m_pos.y(),m_selectBoxImagePath[0]);
    painter->drawPixmap(m_pos.x()+35,m_pos.y(),m_selectBoxImagePath[1]);
    painter->drawPixmap(m_pos.x()+70,m_pos.y(),m_selectBoxImagePath[2]);
    painter->restore();
}

void selectButton::getRemoved()
{
    m_game->removeButton(this);
}

bool selectButton::containPos(QPoint pos)
{
    bool xInhere=pos.x()>m_pos.x() && pos.x()<m_pos.x()+m_fixedSize.width();
    bool yInhere=pos.y()>m_pos.y() && pos.y()<m_pos.y()+m_fixedSize.height();
    return xInhere && yInhere;
}

QPoint selectButton::getPos()
{
    return this->m_pos;
}
