#ifndef TOWERPOSITION_H
#define TOWERPOSITION_H


#include <QSize>
#include <QPainter>
#include <QString>
#include "selectbutton.h"

class selectButton;
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
public:
    bool hasButton();//判断该位置有没有button
    void setHasButton(bool hasButton=true);//设置是否有button
    void setButton(selectButton * button);//设置button
    selectButton * getButton();//得到该位置的button

    bool hasTower1();//判断是否有第一种塔
    void setHasTower1(bool hasTower1=true);//判断是否有第一种塔

    bool hasTower2();
    void setHasTower2(bool hasTower2=true);

    bool hasTower3();
    void setHasTower3(bool hasTower3=true);
private:
    bool m_hasButton;
    bool m_hasTower1;
    bool m_hasTower2;
    bool m_hasTower3;

    selectButton * m_button;//私有化button

};


#endif // TOWERPOSITION_H
