#include "LaboratoryScene.h"

LaboratoryScene::LaboratoryScene(QObject *parent, ResourceManager *resourceManager) : Scene(parent, resourceManager) {
    qDebug() << "[LaboratoryScene] 實驗室場景已構建";
    setupScene();
}

void LaboratoryScene::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Up:
            qDebug() << "[LaboratoryScene] 已按鍵「↑」";
            player->moveUp();
            movingScene(0, 10);
            break;
        case Qt::Key_Down:
            qDebug() << "[LaboratoryScene] 已按鍵「↓」";
            player->moveDown();
            movingScene(0, -10);
            break;
        case Qt::Key_Left:
            qDebug() << "[LaboratoryScene] 已按鍵「←」";
            player->moveLeft();
            movingScene(10, 0);
            break;
        case Qt::Key_Right:
            qDebug() << "[LaboratoryScene] 已按鍵「→」";
            player->moveRight();
            movingScene(-10, 0);
            break;
        default:
            qDebug() << "[LaboratoryScene] 按下未知鍵:" << event->key();
            QGraphicsScene::keyPressEvent(event);
            return;
        }

        event->accept(); // 標記事件已被處理
}

void LaboratoryScene::setupScene() {
    // 背景圖片
    QPixmap background(":/images/scene/lab.png");
    bgItem = new QGraphicsPixmapItem(background);
    addItem(bgItem);
    bgItem->setPos(movingX, movingY);
    qDebug() << "[LaboratoryScene] 背景圖片已載入";

    // 玩家建立
    player = new Player();
    addItem(player);
    player->setPos(210, 195);

    // 屏障建立
    barrier01 = new Barrier(0, 0, 455, 70); // 最上方一排
    barrier02 = new Barrier(0, 87, 34, 70); // 打勾桌
    barrier03 = new Barrier(33, 105, 75, 90); // 孵化器
    barrier04 = new Barrier(279, 128, 108, 61); // 寶可夢球檯
    barrier05 = new Barrier(0, 248, 174, 72); // 左書桌
    barrier06 = new Barrier(279, 248, 176, 72); // 寶可夢球檯
    barrier07 = new Barrier(0, 375, 34, 63); // 左樹
    barrier08 = new Barrier(420, 375, 35, 63); // 右樹
    addItem(barrier01);
    addItem(barrier02);
    addItem(barrier03);
    addItem(barrier04);
    addItem(barrier05);
    addItem(barrier06);
    addItem(barrier07);
    addItem(barrier08);
}

void LaboratoryScene::movingScene(int x, int y) {

    // 處理正負方向（變小的方向）
    int stepX = (x > 0) ? -1 : ((x < 0) ? 1 : 0);
    int stepY = (y > 0) ? -1 : ((y < 0) ? 1 : 0);

    while (true) {
        if (!barrierTest(x, y)) {
            // 找到可移動距離（從 10 逐漸變小）
            qDebug() << "[LaboratoryScene] 碰撞測試成功（於" << x << "," << y << "）";
            break;
        }

        // 如果有碰撞，逐步調整
        qDebug() << "[LaboratoryScene] 碰撞測試失敗（於" << x << "," << y << "）";

        // 如果 x 和 y 都到達 0，停止移動
        if (x == 0 && y == 0) {
            break;
        }

        // 優先調整較大的移動方向
        if (abs(x) > abs(y) && x != 0) {
            x += stepX;
        } else if (y != 0) {
            y += stepY;
        } else if (x != 0) {
            x += stepX;
        }
    }

    movingX += x;
    movingY += y;

    bgItem->setPos(movingX, movingY);
    barrier01->setPos(movingX, movingY);
    barrier02->setPos(movingX, movingY);
    barrier03->setPos(movingX, movingY);
    barrier04->setPos(movingX, movingY);
    barrier05->setPos(movingX, movingY);
    barrier06->setPos(movingX, movingY);
    barrier07->setPos(movingX, movingY);
    barrier08->setPos(movingX, movingY);

}

bool LaboratoryScene::barrierTest(int x, int y) {
    // true 代表不通過、false 代表通過（可移動）
    if (barrierEachTest(barrier01, x, y)) return true;
    if (barrierEachTest(barrier02, x, y)) return true;
    if (barrierEachTest(barrier03, x, y)) return true;
    if (barrierEachTest(barrier04, x, y)) return true;
    if (barrierEachTest(barrier05, x, y)) return true;
    if (barrierEachTest(barrier06, x, y)) return true;
    if (barrierEachTest(barrier07, x, y)) return true;
    if (barrierEachTest(barrier08, x, y)) return true;
    return false;
}

bool LaboratoryScene::barrierEachTest(Barrier *item, int x, int y){
    QRectF playerFutureRect = player->boundingRect().translated(player->pos());
    QRectF barrierRect = item->boundingRect().translated(item->pos() + QPointF(x, y));
    if (playerFutureRect.intersects(barrierRect)) {
        qDebug() << "[LaboratoryScene] 不能走路，檢測到碰撞於:" << item->pos();
        return true;
    }
}
