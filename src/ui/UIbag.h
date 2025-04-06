#ifndef UIBAG_H
#define UIBAG_H

#include <QGraphicsWidget>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QKeyEvent>
#include <QGraphicsTextItem>

#include "src/core/ResourceManager.h"

class UIbag : public QGraphicsWidget
{
   Q_OBJECT

public:
    UIbag(ResourceManager *resourceManage, QGraphicsItem *parent = nullptr);
    ~UIbag() override;

    void showBag();
    void hideBag();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    ResourceManager *resourceManager;

    QGraphicsTextItem *titleText;
    QGraphicsTextItem *pokeballText;
    QGraphicsTextItem *potionText;
    QGraphicsTextItem *etherText;
    QGraphicsPixmapItem *background01;
    QGraphicsPixmapItem *background02;
    QGraphicsPixmapItem *pokeballBag;
    QGraphicsPixmapItem *potionBag;
    QGraphicsPixmapItem *etherBag;

    QGraphicsPixmapItem *charmanderBag;
    QGraphicsPixmapItem *bulbasaurBag;
    QGraphicsPixmapItem *squirtleBag;
    QGraphicsTextItem *charmanderText;
    QGraphicsTextItem *bulbasaurText;
    QGraphicsTextItem *squirtleText;

    void updateItem();
};

#endif // UIBAG_H
