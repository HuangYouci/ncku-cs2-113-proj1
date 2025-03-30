#include "LaboratoryScene.h"

LaboratoryScene::LaboratoryScene(QObject *parent) : QGraphicsScene(parent) {
    qDebug() << "[LaboratoryScene] 實驗室場景已構建";
    setupScene();
}

void LaboratoryScene::keyPressEvent(QKeyEvent *event) {
    qDebug() << "[LaboratoryScene] 已按下鍵盤：" << event->key();
    switch (event->key()) {
        case Qt::Key_Up:
            qDebug() << "[LaboratoryScene] Up arrow pressed";
            // 在這裡執行向上移動的動作 (例如：移動玩家、調整視角)
            break;
        case Qt::Key_Down:
            qDebug() << "[LaboratoryScene] Down arrow pressed";
            // 在這裡執行向下移動的動作
            break;
        case Qt::Key_Left:
            qDebug() << "[LaboratoryScene] Left arrow pressed";
            // 在這裡執行向左移動的動作
            break;
        case Qt::Key_Right:
            qDebug() << "[LaboratoryScene] Right arrow pressed";
            // 在這裡執行向右移動的動作
            break;
        default:
            qDebug() << "[LaboratoryScene] Unhandled key:" << event->key();
            QGraphicsScene::keyPressEvent(event); // 將未處理的事件傳遞給父類別
            return;
        }

        event->accept(); // 標記事件已被處理
}

void LaboratoryScene::setupScene() {
    QPixmap background(":/images/scene/lab.png");
    setBackgroundBrush(QBrush(background));
    qDebug() << "[LaboratoryScene] 背景圖片已載入";
}
