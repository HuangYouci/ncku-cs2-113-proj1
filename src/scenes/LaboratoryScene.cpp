#include "LaboratoryScene.h"
#include "src/GameWindow.h"
#include <QRandomGenerator>

LaboratoryScene::LaboratoryScene(QObject *parent, ResourceManager *resourceManager) : Scene(parent, resourceManager) {
    qDebug() << "[LaboratoryScene] 實驗室場景已構建";
    setupScene();
}

void LaboratoryScene::keyPressEvent(QKeyEvent *event) {

    if (uiDialog->isVisible() || uiBag->isVisible() || uiChoose->isVisible()) {
        QGraphicsScene::keyPressEvent(event); // Pass the event to UI
        return;
    }

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

            // CHECK IF PLAYER WANT LEAVE THE SCENE.
            if ((playerX > 1180) && (playerX < 1240) && (playerY > 1360)){
                resourceManager->setPreviousScene("LAB");
                switchScene(2); // 去town
            }

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
            qDebug() << "[LaboratoryScene] 已按鍵「A」";
            if (showNPCdialog(playerX, playerY)) { break; }
            showUIchoose(playerX, playerY);
            break;
        case Qt::Key_B:
            qDebug() << "[LaboratoryScene] 已按鍵「B」";
            uiBag->showBag();
            uiBag->setPos(playerX, playerY);
            break;
        default:
            qDebug() << "[LaboratoryScene] 按下未知鍵:" << event->key();
            QGraphicsScene::keyPressEvent(event);
            return;
        }

        qDebug() << "[LaboratoryScene] 玩家目前位置 (" << playerX << "," << playerY << ")";
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
    playerX = 1210;
    playerY = 1360;
    player->setPos(playerX, playerY);
    qDebug() << "[LaboratoryScene] 玩家已載入";

    // NPC 建立
    npc = new NPC();
    addItem(npc);
    npc->setPos(1210,1100);
    qDebug() << "[LaboratoryScene] NPC 已載入";
    npcMoveTimer = new QTimer(this);
    connect(npcMoveTimer, &QTimer::timeout, this, &LaboratoryScene::npcRandomMove);

    // 三個寶貝球
    QPixmap pokeball(":/images/other/ball.png");
    pokeball01 = new QGraphicsPixmapItem(pokeball);
    pokeball02 = new QGraphicsPixmapItem(pokeball);
    pokeball03 = new QGraphicsPixmapItem(pokeball);
    addItem(pokeball01);
    addItem(pokeball02);
    addItem(pokeball03);
    pokeball01->setPos(1290,1135);
    pokeball01->setScale(0.8);
    pokeball02->setPos(1320,1135);
    pokeball02->setScale(0.8);
    pokeball03->setPos(1350,1135);
    pokeball03->setScale(0.8);
    qDebug() << "[LaboratoryScene] 寶貝球已載入";

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
//    barriers.append(new Barrier(1210, 1100, 30, 40)); // 博士NPC

    for (Barrier *barrier : barriers ) {
        addItem(barrier);
    }

    // 對話匡建立
    uiDialog = new UIdialog(resourceManager->getFont(25), QColor(Qt::black));
    addItem(uiDialog);
    uiDialog->hideDialogue();

    // 背包建立
    uiBag = new UIbag(resourceManager);
    addItem(uiBag);
    uiBag->hideBag();

    // 選擇初始寶可夢建立
    uiChoose = new UIchoose(resourceManager);
    addItem(uiChoose);
    uiChoose->hide();
}

void LaboratoryScene::move(int x, int y) {

    // 處理正負方向（變小的方向）
    int stepX = (x > 0) ? -1 : ((x < 0) ? 1 : 0);
    int stepY = (y > 0) ? -1 : ((y < 0) ? 1 : 0);

    while (true) {
        if (!barrierTest(x, y)) {
            // 找到可移動距離（從 10 逐漸變小）
            qDebug() << "[LaboratoryScene] 碰撞測試成功 (" << x << "," << y << "）";
            break;
        }

        // 如果有碰撞，逐步調整
        // qDebug() << "[LaboratoryScene] 碰撞測試失敗（於" << x << "," << y << "）";

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
            qDebug() << "[LaboratoryScene] 不能走路";
            return true; // 沒通過
        }

    }

    // 測試 NPC 的碰撞
    QRectF playerFutureRect = player->boundingRect().translated(player->pos() + QPointF(x, y));
    QRectF npcRect = npc->boundingRect().translated(npc->pos());
    if (playerFutureRect.intersects(npcRect)) {
        qDebug() << "[LaboratoryScene] 撞到 NPC";
        return true; // 沒通過
    }

    return false;
}

void LaboratoryScene::centerOnPlayer(){
    GameWindow *gameWindow = qobject_cast<GameWindow*>(parent());
        if (gameWindow) {
            gameWindow->centerOnPlayer();
        }
}

bool LaboratoryScene::showNPCdialog(int x, int y){
    if ( ( x > 1170 ) && ( x < 1250 ) && ( y > 1070 ) && ( y < 1150 ) ){
        qDebug() << "[LaboratoryScene] 觸發對話！";
        dialogues.clear();

        if (resourceManager->getTalkToLabNPCTimes() > 0){
            dialogues << "你還有什麼問題嗎？" << "趕快去進行你的冒險。";
        } else {
            dialogues << "我是大木博士，歡迎來到我的實驗室！" << "你可以在實驗室選擇三個寶可夢球中\n的一個作為你的初始寶可夢。";
            npcMoveTimer->start(1000); // 每秒移動一次 博士開始走
        }

        uiDialog->setDialogues(dialogues);
        uiDialog->setPos(playerX, playerY);
        uiDialog->showDialogue();


        resourceManager->addTalkToLabNPCTimes();
        return true;
    }
    return false;
}

bool LaboratoryScene::showUIchoose(int x, int y){
    if ( ( x > 1240 ) && ( x < 1390 ) && ( y > 1085 ) && ( y < 1190 ) ){
        qDebug() << "[LaboratoryScene] 觸發選擇寶可夢！";

        if (resourceManager->getReceivedInitPokemon()){
            // 已經取得過
            dialogues.clear();
            dialogues << "你已經取得過初始寶可夢了！\n不可以再次獲得。" << "趕快出去冒險吧！";
            uiDialog->setDialogues(dialogues);
            uiDialog->setPos(playerX, playerY);
            uiDialog->showDialogue();
        } else {
            // 尚未取得任一初始寶可夢
            uiChoose->show();
            uiChoose->setPos(playerX, playerY);
        }

        return true;

    }
    return false;
}

void LaboratoryScene::npcRandomMove() {
    static const QVector<QPoint> directions = {
        QPoint(0, -10),  // 上
        QPoint(0, 10),   // 下
        QPoint(-10, 0),  // 左
        QPoint(10, 0)    // 右
    };

    int index = QRandomGenerator::global()->bounded(directions.size());
    int dx = directions[index].x();
    int dy = directions[index].y();

    // 碰撞偵測（不讓 NPC 走進障礙物）
    QRectF futureRect = npc->boundingRect().translated(npc->pos() + QPointF(dx, dy));

    for (Barrier *barrier : barriers) {
        QRectF barrierRect = barrier->boundingRect().translated(barrier->pos());
        if (futureRect.intersects(barrierRect)) return;
    }

    // 檢查是否會撞到玩家
    QRectF playerRect = player->boundingRect().translated(player->pos());
    if (futureRect.intersects(playerRect)) return;

    // 移動 NPC
    npc->moveBy(dx, dy);
}
