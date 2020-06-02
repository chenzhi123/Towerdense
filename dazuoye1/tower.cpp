#include "tower.h"
#include <QPoint>
#include <QPixmap>
#include<QPainter>
tower::tower(QPoint pos,QString pixfilename) : QObject(0),pixmap(pixfilename)
{
  _pos=pos;
}
void tower::draw(QPainter *painter){
    painter->drawPixmap(_pos,pixmap);
}
