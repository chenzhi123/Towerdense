#ifndef SELECTBUTTON_H
#define SELECTBUTTON_H

#include <QPainter>
#include <QString>
#include <QPoint>
#include <QSize>

#include "mainwindow.h"
#include "ks.h"
class MainWindow;
class Ks;

class selectButton
{
public:
    selectButton(QPoint pos,Ks * game);
    ~selectButton();

    void draw(QPainter * painter)const;//绘画选择框
    void getRemoved();//选择框被点击了以后，就要被移除
    bool containPos(QPoint pos);//判断鼠标的点击点，是否在选择框的内部
    QPoint getPos();//得到选择框的左上店
private:
    Ks * m_game;//指向mainwindow的指针
    QPoint m_pos;//selectButton图片的左上角
    QString m_selectBoxImagePath[3];//用来储存选择框内的防御塔的图片，我设置的三个防御塔可以选择，就储存三张图片

    static const QSize m_fixedSize;
};
#endif // SELECTBUTTON_H
