#ifndef LABORATORYSCENE_H
#define LABORATORYSCENE_H

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>
#include <QList>
#include <QStringList>
#include <QTimer>

#include "src/core/Scene.h"
#include "src/entities/Player.h"
#include "src/entities/Barrier.h"
#include "src/entities/NPC.h"
#include "src/ui/UIdialog.h"
#include "src/ui/UIbag.h"
#include "src/ui/UIchoose.h"

class LaboratoryScene : public Scene
{
Q_OBJECT

public:
    // 玩家
    Player *player;
    LaboratoryScene(QObject *parent = nullptr, ResourceManager *resourceManager = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;

signals:
    void switchScene(int index);

private:
    // --- 場景元素 --- //
    NPC *npc;
    QGraphicsPixmapItem *bgItem;
    QList<Barrier*> barriers;
    UIdialog *uiDialog;
    UIbag *uiBag;
    UIchoose *uiChoose;
    QGraphicsPixmapItem *pokeball01;
    QGraphicsPixmapItem *pokeball02;
    QGraphicsPixmapItem *pokeball03;
    QTimer *npcMoveTimer;

    // --- 暫存數值 --- //
    int playerX;
    int playerY;
    QStringList dialogues;

    // --- 函數功能 --- //
    void centerOnPlayer(); // 居中玩家
    void setupScene(); // 設置場景
    void move(int x, int y); // 移動
    bool barrierTest(int x, int y); // 檢查屏障
    bool showNPCdialog(int x, int y); // 觸發對話
    bool showUIchoose(int x, int y); // 觸發選擇寶可夢
    void npcRandomMove();

};

#endif // LABORATORYSCENE_H
