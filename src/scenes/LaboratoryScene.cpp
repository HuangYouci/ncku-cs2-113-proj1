#include "LaboratoryScene.h"
#include "src/GameWindow.h"

LaboratoryScene::LaboratoryScene(QObject *parent, ResourceManager *resourceManager) : Scene(parent, resourceManager) {
    qDebug() << "[LaboratoryScene] 實驗室場景已構建";
    setupScene();
}

void LaboratoryScene::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Up:
            qDebug() << "[LaboratoryScene] 已按鍵「↑」";
            player->moveUp();
            move(0, -10);
            break;
        case Qt::Key_Down:
            qDebug() << "[LaboratoryScene] 已按鍵「↓」";
            player->moveDown();
            move(0, 10);
            break;
        case Qt::Key_Left:
            qDebug() << "[LaboratoryScene] 已按鍵「←」";
            player->moveLeft();
            move(-10, 0);
            break;
        case Qt::Key_Right:
            qDebug() << "[LaboratoryScene] 已按鍵「→」";
            player->moveRight();
            move(10, 0);
            break;
        case Qt::Key_A:
            showNPCdialog(playerX, playerY);
            break;
        default:
            qDebug() << "[LaboratoryScene] 按下未知鍵:" << event->key();
            QGraphicsScene::keyPressEvent(event);
            return;
        }

        event->accept(); // 標記事件已被處理
}

void LaboratoryScene::setupScene() {

    // 絕對背景（2000x2000）
    setSceneRect(0, 0, 3000, 3000);
    setBackgroundBrush(Qt::black);


    // 背景圖片
    QPixmap background(":/images/scene/lab.png");
    bgItem = new QGraphicsPixmapItem(background);
    addItem(bgItem);
    bgItem->setPos(1000, 1000);
    qDebug() << "[LaboratoryScene] 背景圖片已載入";

    // 玩家建立
    player = new Player();
    addItem(player);
    playerX = 1100;
    playerY = 1100;
    player->setPos(playerX, playerY);

    // NPC 建立
    npc = new NPC();
    addItem(npc);
    npc->setPos(1210,1100);

    // 屏障建立
    barriers.append(new Barrier(1000, 1000, 455, 70)); // 最上方一排
    barriers.append(new Barrier(1000, 1087, 34, 70)); // 打勾桌
    barriers.append(new Barrier(1033, 1105, 75, 90)); // 孵化器
    barriers.append(new Barrier(1279, 1128, 108, 61)); // 寶可夢球檯
    barriers.append(new Barrier(1000, 1248, 174, 72)); // 左書桌
    barriers.append(new Barrier(1279, 1248, 176, 72)); // 寶可夢球檯
    barriers.append(new Barrier(1000, 1375, 34, 63)); // 左樹
    barriers.append(new Barrier(1420, 1375, 35, 63)); // 右樹
    barriers.append(new Barrier(1000, 1000, 1, 438)); // 左邊界
    barriers.append(new Barrier(1455, 1000, 1, 438)); // 右邊界
    barriers.append(new Barrier(1000, 1438, 455, 1)); // 下邊界
    barriers.append(new Barrier(1210, 1100, 30, 40)); // 博士NPC

    for (Barrier *barrier : barriers ) {
        addItem(barrier);
    }

}

void LaboratoryScene::move(int x, int y) {

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

    playerX += x;
    playerY += y;

    player->setPos(playerX, playerY);

    centerOnPlayer();

}

bool LaboratoryScene::barrierTest(int x, int y) {

    for (Barrier *barrier : barriers ) {

        QRectF playerFutureRect = player->boundingRect().translated(player->pos() + QPointF(x, y));
        QRectF barrierRect = barrier->boundingRect().translated(barrier->pos());
        if (playerFutureRect.intersects(barrierRect)) {
            qDebug() << "[LaboratoryScene] 不能走路，檢測到碰撞於:" << barrier->pos();
            return true; // 沒通過
        }

    }

    return false;
}

void LaboratoryScene::centerOnPlayer(){
    GameWindow *gameWindow = qobject_cast<GameWindow*>(parent());
        if (gameWindow) {
            gameWindow->centerOnPlayer();
        }
}

void LaboratoryScene::showNPCdialog(int x, int y){
    if ( ( x > 1110 ) && ( x < 1310 ) && ( y > 1000 ) && ( y < 1200 ) ){
        qDebug() << "[LaboratoryScene] 觸發對話！";
    }
}
