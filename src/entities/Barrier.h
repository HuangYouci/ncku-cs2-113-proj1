#ifndef BARRIER_H
#define BARRIER_H

#include <QGraphicsRectItem>

class Barrier : public QGraphicsRectItem
{
public:
    Barrier(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = nullptr);
};

#endif // BARRIER_H
