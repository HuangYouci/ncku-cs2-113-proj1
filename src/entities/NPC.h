#ifndef NPC_H
#define NPC_H

#include <QGraphicsPixmapItem>
#include <QKeyEvent>

class NPC : public QGraphicsPixmapItem
{
public:
    NPC(QGraphicsItem *parent = nullptr);
    ~NPC() override;

private:
    QPixmap npcImage;
};

#endif // NPC_H
