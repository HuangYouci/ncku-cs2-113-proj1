#ifndef LABORATORYSCENE_H
#define LABORATORYSCENE_H

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>

#include "src/core/Scene.h"
#include "src/entities/Player.h"
#include "src/entities/Barrier.h"

class LaboratoryScene : public Scene
{
public:
    LaboratoryScene(QObject *parent = nullptr, ResourceManager *resourceManager = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    // 玩家
    Player *player;

    // 背景
    QGraphicsPixmapItem *bgItem;
    Barrier *barrier01;
    Barrier *barrier02;
    Barrier *barrier03;
    Barrier *barrier04;
    Barrier *barrier05;
    Barrier *barrier06;
    Barrier *barrier07;
    Barrier *barrier08;
    int movingX = 0;
    int movingY = 0;
    void setupScene();
    void movingScene(int x, int y);
    bool barrierTest(int x, int y);
    bool barrierEachTest(Barrier *item, int x, int y);
};

#endif // LABORATORYSCENE_H
