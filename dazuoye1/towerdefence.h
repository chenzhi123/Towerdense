#ifndef TOWERDEFENCE_H
#define TOWERDEFENCE_H
#include <QWidget>
#include <QKeyEvent>
#include <QMouseEvent>
class Towerdefence: public QWidget
{
public:
    Towerdefence();
protected:
    QImage map;
    void loadmap();
};

#endif // TOWERDEFENCE_H
