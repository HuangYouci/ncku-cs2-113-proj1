#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>

#include "src/core/Scene.h"

class GameOver : public Scene
{
    Q_OBJECT

public:
    GameOver(QObject *parent = nullptr, ResourceManager *resourceManager = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;

signals:
    void switchScene(int index);

private:
    void setupScene();

};

#endif // GAMEOVER_H
