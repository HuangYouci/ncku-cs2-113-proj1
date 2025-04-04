#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>

// 管理場景 //
#include "src/scenes/TitleScene.h"
#include "src/scenes/LaboratoryScene.h"

// 管理資料 //
#include "src/core/ResourceManager.h"


class GameWindow : public QMainWindow {
    Q_OBJECT

public:
    // 建構與解構
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

    // 聚焦玩家
    void centerOnPlayer();

private:
    // 主要顯示
    QGraphicsView *view;

    // 資料
    ResourceManager *resourceManager;

    // 場景們
    TitleScene *titleScene = nullptr;
    LaboratoryScene *laboratoryScene = nullptr;

    // 現在顯示的場景
    Scene *currentScene = nullptr;

private slots:
    // 切換場景
    void switchScene(int index);
};

#endif // GAMEWINDOW_H
