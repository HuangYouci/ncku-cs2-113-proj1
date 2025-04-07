#include "src/util/ClickableTextItem.h"

#include <QCursor>

ClickableTextItem::ClickableTextItem(const QString &text, QGraphicsItem *parent)
    : QGraphicsTextItem(text, parent)
{
    setAcceptHoverEvents(true);
    setCursor(Qt::PointingHandCursor);
}

void ClickableTextItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (onClick) {
        onClick();
    }
    setDefaultTextColor(Qt::black);
    QGraphicsTextItem::mousePressEvent(event);
}

void ClickableTextItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    setDefaultTextColor(Qt::red);
    QGraphicsTextItem::hoverEnterEvent(event);
}

void ClickableTextItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    setDefaultTextColor(Qt::black);
    QGraphicsTextItem::hoverLeaveEvent(event);
}
