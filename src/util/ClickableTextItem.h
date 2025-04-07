#ifndef CLICKABLETEXTITEM_H
#define CLICKABLETEXTITEM_H

#include <QGraphicsTextItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include <functional>

class ClickableTextItem : public QGraphicsTextItem {
public:
    explicit ClickableTextItem(const QString &text, QGraphicsItem *parent = nullptr);

    std::function<void()> onClick;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
};

#endif // CLICKABLETEXTITEM_H
