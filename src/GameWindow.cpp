#include "GameWindow.h"

#include <QDebug>

GameWindow::GameWindow(QWidget *parent) : QMainWindow(parent) {
    qDebug() << "[GameWindow] 已被建構";

    // 創建視窗
    view = new QGraphicsView(this);
    setCentralWidget(view);
    view->setFocusPolicy(Qt::StrongFocus);
    view->setFocus();
    setWindowTitle("[Game] Pokémon RPG (Group 17, Introduction to Computer Science, 2025 Spring, NCKU EE)");
    setFixedSize(525, 450);

    // 創建場景
    titleScene = new TitleScene(this);

    // 切換場景
    switchScene(0);
}

GameWindow::~GameWindow() {
    delete titleScene;
    delete view;
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
    }

    view->setScene(currentScene);
    view->setFocus();
}
