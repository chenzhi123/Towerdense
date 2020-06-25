#ifndef TOWERPOSITION_H
#define TOWERPOSITION_H


#include <QSize>
#include <QPainter>
#include <QString>

class TowerPosition
{
public:
    TowerPosition(QPoint pos,QString path=(":/open_spot.png"));//图片的路径
    QPoint getCenterPos();//得到防御塔坑的中心点
    QPoint getPos();//得到防御塔坑的左上点

    bool ContainPos(QPoint pos);//判断pos点是否在防御塔坑的范围内

    void draw(QPainter * painter) const;

    bool hasTower();//判断该防御塔坑内有没有防御塔
    void setHasTower(bool hasTower=true);//设置是否有防御塔

 private:
    QPoint m_pos;
    QString m_path;

    bool m_hasTower;
    static const QSize m_fixedSize;//防御塔坑的固定大小
};


#endif // TOWERPOSITION_H
