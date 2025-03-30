#ifndef TITLESCENE_H
#define TITLESCENE_H

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>


class TitleScene : public QGraphicsScene
{  
public:
    TitleScene(QObject *parent = nullptr);

//protected:
//    void keyPressEvent(QKeyEvent *event) override;

private:
    void setupScene();
};

#endif // TITLESCENE_H
