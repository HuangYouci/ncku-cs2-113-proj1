#ifndef LABORATORYSCENE_H
#define LABORATORYSCENE_H

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>
#include <QList>
#include <QStringList>

#include "src/core/Scene.h"
#include "src/entities/Player.h"
#include "src/entities/Barrier.h"
#include "src/entities/NPC.h"
#include "src/ui/UIdialog.h"
#include "src/ui/UIbag.h"

class LaboratoryScene : public Scene
{
public:
    // 玩家
    Player *player;
    LaboratoryScene(QObject *parent = nullptr, ResourceManager *resourceManager = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    // --- 場景元素 --- //
    NPC *npc;
    QGraphicsPixmapItem *bgItem;
    QList<Barrier*> barriers;
    UIdialog *uiDialog;
    UIbag *uiBag;
    QGraphicsPixmapItem *pokeball01;
    QGraphicsPixmapItem *pokeball02;
    QGraphicsPixmapItem *pokeball03;


    // --- 暫存數值 --- //
    int playerX;
    int playerY;
    QStringList dialogues;

    // --- 函數功能 --- //
    void centerOnPlayer(); // 居中玩家
    void setupScene(); // 設置場景
    void move(int x, int y); // 移動
    bool barrierTest(int x, int y); // 檢查屏障
    void showNPCdialog(int x, int y); // 觸發對話
};

#endif // LABORATORYSCENE_H
