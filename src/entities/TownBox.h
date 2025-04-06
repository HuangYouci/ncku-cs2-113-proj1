#ifndef TOWNBOX_H
#define TOWNBOX_H

#include <QGraphicsPixmapItem>

class TownBox : public QGraphicsPixmapItem
{
public:
    TownBox(QGraphicsItem *parent = nullptr);
    ~TownBox() override;
private:
    QPixmap boxImage;
};

#endif // TOWNBOX_H
