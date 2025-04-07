#ifndef GRASSLANDSCENE_H
#define GRASSLANDSCENE_H

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>
#include <QList>
#include <QStringList>

#include "src/core/Scene.h"
#include "src/entities/Player.h"
#include "src/entities/Barrier.h"
#include "src/entities/Ledge.h"
#include "src/entities/Tallgrass.h"
#include "src/ui/UIdialog.h"
#include "src/ui/UIbag.h"

class GrasslandScene : public Scene
{
Q_OBJECT

public:
    Player *player;
    QGraphicsPixmapItem *anchorCenter;
    GrasslandScene(QObject *parent = nullptr, ResourceManager *resourceManager = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;

signals:
    void switchScene(int index);

private:
    // --- 場景元素 --- //
    QGraphicsPixmapItem *bgItem;
    QList<Barrier*> barriers;
    QList<Ledge*> ledges;
    QList<Tallgrass*> tallgrasses;
    UIbag *uiBag;
    UIdialog *uiDialog;

    // --- 暫存數值 --- //
    int playerX;
    int playerY;
    QStringList dialogues;

    // --- 函數功能 --- //
    void centerOnAnchor();
    void setupScene();
    void move(int x, int y);
    bool barrierTest(int x, int y);
    bool ledgeTest(int x, int y);
    bool showBulletinDialog(int x, int y);
};

#endif // GRASSLANDSCENE_H
