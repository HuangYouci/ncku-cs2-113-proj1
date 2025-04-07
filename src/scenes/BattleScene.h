#ifndef BATTLESCENE_H
#define BATTLESCENE_H

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>
#include <QSoundEffect>

#include "src/core/Scene.h"
#include "src/util/ClickableTextItem.h"

class BattleScene : public Scene
{
Q_OBJECT

public:
    BattleScene(QObject *parent = nullptr, ResourceManager *resourceManager = nullptr);
    void start(); // 開始戰鬥（外部呼叫，目前設定怪物由此類別創建）

protected:
    void keyPressEvent(QKeyEvent *event) override;

signals:
    void switchScene(int index);

private:
    void setupScene();
    void updateBattleStatus();

    void choosePokemonToStart(int current = 0);
    void myround();
    void myroundBag();
    void myroundPokemon(int current = 0);
    void myroundFight();
    void myroundFightUse(int methodIndex);
    void myroundConfirm(QString message);
    void myroundBack(QString message);
    void myroundCaptureSuccess();

    void enemyround();

    bool judgeVictor();
    void iWon();
    void iLost();
    QString iWonLevelup();

    Pokemon generateRandomEnemy();

    QGraphicsTextItem *textDescription;
    ClickableTextItem *optionA;
    ClickableTextItem *optionB;
    ClickableTextItem *optionC;
    ClickableTextItem *optionD;

    QGraphicsPixmapItem *myPokemon;
    QGraphicsPixmapItem *enemyPokemon;
    QGraphicsTextItem *myPokemonName;
    QGraphicsTextItem *enemyPokemonName;
    QGraphicsTextItem *myPokemonStat;
    QGraphicsTextItem *enemyPokemonStat;
    QGraphicsRectItem *myPokemonHealthBar0;
    QGraphicsRectItem *myPokemonHealthBar1;
    QGraphicsRectItem *enemyPokemonHealthBar0;
    QGraphicsRectItem *enemyPokemonHealthBar1;

    QSoundEffect *sound;

    Pokemon enemy;
    int myPokemonIndex;

};

#endif // BATTLESCENE_H
