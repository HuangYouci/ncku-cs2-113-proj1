#ifndef TITLESCENE_H
#define TITLESCENE_H

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>

#include "src/core/Scene.h"

class TitleScene : public Scene
{  
Q_OBJECT

public:
    TitleScene(QObject *parent = nullptr, ResourceManager *resourceManager = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;

signals:
    void startGame();

private:
    void setupScene();
};

#endif // TITLESCENE_H
