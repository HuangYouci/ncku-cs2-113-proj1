#include "Tallgrass.h"

#include <QPen>

Tallgrass::Tallgrass(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent) : QGraphicsRectItem(x, y, width, height, parent)
{
    setPen(QPen(Qt::NoPen));
}

