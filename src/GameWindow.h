#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>

// 管理場景 //
#include "LaboratoryScene.h"
#include "TitleScene.h"


class GameWindow : public QMainWindow {
    Q_OBJECT

public:
    // 建構與解構
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

    // 切換場景
    void switchScene(int index);

private:
    // 主要顯示
    QGraphicsView *view;

    // 場景們
    TitleScene *titleScene = nullptr;

    // 現在顯示的場景
    QGraphicsScene *currentScene = nullptr;
};

#endif // GAMEWINDOW_H
