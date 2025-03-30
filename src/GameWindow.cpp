#include "GameWindow.h"

#include <QDebug>

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

    // 建立信號連結
    connect(titleScene, &TitleScene::startGame, this, &GameWindow::startGame);

    // 切換場景
    switchScene(0);
}

GameWindow::~GameWindow() {
    delete titleScene;
    delete view;
    delete resourceManager;
    delete laboratoryScene;
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
        setWindowTitle("[Laboratory] Pokémon RPG (Group 17, Introduction to Computer Science, 2025 Spring, NCKU EE)");
        break;
    }

    view->setScene(currentScene);
    view->setFocus();
}

void GameWindow::startGame() {
    qDebug() << "[GameWindow] 接收到開始遊戲";
    switchScene(1);
}
