#ifndef LABORATORYSCENE_H
#define LABORATORYSCENE_H

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>

class LaboratoryScene : public QGraphicsScene
{
public:
    LaboratoryScene(QObject *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    void setupScene();
};

#endif // LABORATORYSCENE_H
