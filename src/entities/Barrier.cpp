#include "Barrier.h"

#include <QBrush>
#include <QPen>

Barrier::Barrier(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent) : QGraphicsRectItem(x, y, width, height, parent)
{
    setPen(QPen(Qt::red));
}
