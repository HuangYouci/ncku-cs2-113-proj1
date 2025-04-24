#ifndef UIBAG_H
#define UIBAG_H

#include <QGraphicsWidget>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QKeyEvent>
#include <QGraphicsTextItem>
#include <QList>

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

    QList<QGraphicsPixmapItem*> pokemonsImage;
    QList<QGraphicsTextItem*> pokemonsText;
    QList<QGraphicsRectItem*> pokemonsBackground;

    void updateItem();
    QString tellType(int type);
};

#endif // UIBAG_H
