#ifndef UICHOOSE_H
#define UICHOOSE_H

#include <QGraphicsWidget>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QKeyEvent>
#include <QGraphicsTextItem>

#include "src/core/ResourceManager.h"

class UIchoose : public QGraphicsWidget
{
   Q_OBJECT

public:
    UIchoose(ResourceManager *resourceManage, QGraphicsItem *parent = nullptr);
    ~UIchoose() override;

    void show();
    void hide();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    ResourceManager *resourceManager;

    QGraphicsTextItem *titleText;
    QGraphicsTextItem *chooseText;
    QGraphicsPixmapItem *background;
    QGraphicsPixmapItem *pk1;
    QGraphicsPixmapItem *pk2;
    QGraphicsPixmapItem *pk3;
    QGraphicsPixmapItem *pk4;
    int currentPK = 1;
};

#endif // UICHOOSE_H
