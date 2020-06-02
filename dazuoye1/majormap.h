#ifndef MAJORMAP_H
#define MAJORMAP_H

#include <QMainWindow>
#include "tower.h"
#include<QList>
class majormap : public QMainWindow
{
    Q_OBJECT
public:
    explicit majormap(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);
    void set_tower();//
private:
    QList<tower*> tower_list;
signals:
    void chooseback();//

};

#endif // MAJORMAP_H
