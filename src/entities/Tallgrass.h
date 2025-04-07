#ifndef TALLGRASS_H
#define TALLGRASS_H

#include <QGraphicsRectItem>

class Tallgrass : public QGraphicsRectItem
{
public:
    Tallgrass(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = nullptr);
    bool triggered = false;
};

#endif // TALLGRASS_H
