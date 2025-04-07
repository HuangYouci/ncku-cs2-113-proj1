#include "Ledge.h"

#include <QBrush>
#include <QPen>

Ledge::Ledge(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent) : QGraphicsRectItem(x, y, width, height, parent)
{
    setPen(QPen(Qt::NoPen));
}
