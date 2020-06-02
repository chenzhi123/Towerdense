#ifndef TOWER_H
#define TOWER_H

#include <QObject>
#include <QPoint>
#include <QPixmap>
class tower : public QObject
{
    Q_OBJECT
public:
    explicit tower(QObject *parent = nullptr);
    tower(QPoint pos,QString pixfilename);
    void draw(QPainter *painter);
private:
    QPoint _pos;
    QPixmap pixmap;
signals:

};

#endif // TOWER_H
