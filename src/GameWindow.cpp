#include "GameWindow.h"

#include <QDebug>
#include <QTimer>

GameWindow::GameWindow(QWidget *parent) : QMainWindow(parent) {
    qDebug() << "[GameWindow] 已被建構";

    // 創建視窗
    view = new QGraphicsView(this);
    view->setBackgroundBrush(QBrush(Qt::black)); // 黑色背景
    setCentralWidget(view);

    view->setFocusPolicy(Qt::StrongFocus); // 焦點鎖定
    view->setFocus();

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // 滾動條禁止使用
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setWindowTitle("[Game] Pokémon RPG (Group 17, Introduction to Computer Science, 2025 Spring, NCKU EE)");
    setFixedSize(525, 450);

    // 建立管理
    resourceManager = new ResourceManager();

    // 創建場景
    titleScene = new TitleScene(this, resourceManager);
    laboratoryScene = new LaboratoryScene(this, resourceManager);
    townScene = new TownScene(this, resourceManager);

    // 建立信號連結
    connect(titleScene, &TitleScene::switchScene, this, &GameWindow::switchScene);
    connect(laboratoryScene, &LaboratoryScene::switchScene, this, &GameWindow::switchScene);
    connect(townScene, &TownScene::switchScene, this, &GameWindow::switchScene);

    // 切換場景
    switchScene(0);
}

GameWindow::~GameWindow() {
}

void GameWindow::switchScene(int index) {
    qDebug() << "[GameWindow] 切換到場景 #" << index;

    if (currentScene) {
        view->setScene(nullptr);
    }

    switch (index){
    case 0:
        currentScene = titleScene;
        setWindowTitle("[Title] Pokémon RPG (Group 17, Introduction to Computer Science, 2025 Spring, NCKU EE)");
        break;
    case 1:
        currentScene = laboratoryScene;
        QTimer::singleShot(0, this, &GameWindow::centerOnPlayer);
        setWindowTitle("[Laboratory] Pokémon RPG (Group 17, Introduction to Computer Science, 2025 Spring, NCKU EE)");
        break;
    case 2:
        currentScene = townScene;
        QTimer::singleShot(0, this, &GameWindow::centerOnAnchor);
        setWindowTitle("[Town] Pokémon RPG (Group 17, Introduction to Computer Science, 2025 Spring, NCKU EE)");
        break;
    }

    view->setScene(currentScene);
    view->setFocus();
}

void GameWindow::centerOnPlayer() {
    if (currentScene == laboratoryScene) {
        // 將 LaboratoryScene 轉型並獲取玩家位置
        LaboratoryScene *labScene = static_cast<LaboratoryScene*>(currentScene);
        view->centerOn(labScene->player); // 將視圖中心鎖定在玩家上
    }
}

void GameWindow::centerOnAnchor(){
    if (currentScene == townScene) {
        TownScene *townScene = static_cast<TownScene*>(currentScene);
        view->centerOn(townScene->anchorCenter); // 將視圖中心鎖定在玩家上
    }
}
