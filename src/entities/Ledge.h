#ifndef LEDGE_H
#define LEDGE_H

#include <QGraphicsRectItem>

class Ledge : public QGraphicsRectItem
{
public:
    Ledge(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = nullptr);
};

#endif // LEDGE_H
