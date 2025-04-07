#include "GrasslandScene.h"
#include "src/GameWindow.h"

#include <QRandomGenerator>

GrasslandScene::GrasslandScene(QObject *parent, ResourceManager *resourceManager) : Scene(parent, resourceManager)
{
    qDebug() << "[GrasslandScene] 草地場景已構建";
    setupScene();
}

void GrasslandScene::keyPressEvent(QKeyEvent *event){
    if (uiDialog->isVisible() || uiBag->isVisible()){
        QGraphicsScene::keyPressEvent(event);
        return;
    }

    switch(event->key()){
    case Qt::Key_Up:
        qDebug() << "[GrasslandScene] 已按下「↑」";
        player->moveUp();
        move(0, -10);
        break;
    case Qt::Key_Down:
        qDebug() << "[GrasslandScene] 已按下「↓」";
        player->moveDown();

        // CHECK IF PLAYER WANT LEAVE THE SCENE.
        if ((playerX > 1470) && (playerX < 1580) && (playerY > 2580)){
            resourceManager->setPreviousScene("GRASSLAND");
            switchScene(2); // 去town
        }

        move(0, 10);
        break;
    case Qt::Key_Left:
        qDebug() << "[GrasslandScene] 已按下「←」";
        player->moveLeft();
        move(-10, 0);
        break;
    case Qt::Key_Right:
        qDebug() << "[GrasslandScene] 已按下「→」";
        player->moveRight();
        move(10, 0);
        break;
    case Qt::Key_A:
        qDebug() << "[GrasslandScene] 已按下「A」";
        if (showBulletinDialog(playerX, playerY)) { break; }
        break;
    case Qt::Key_B:
        qDebug() << "[GrasslandScene] 已按下「B」";
        uiBag->showBag();
        uiBag->setPos(anchorCenter->pos().x(),anchorCenter->pos().y());
        break;
    case Qt::Key_P:
        qDebug() << "[GrasslandScene] 已按下「P」（測試用，開啟戰鬥）";
        switchScene(4);

        break;
    default:
        qDebug() << "[GrasslandScene] 按下未知鍵" << event->key();
        QGraphicsScene::keyPressEvent(event);
        return;
    }

    qDebug() << "[GrasslandScene] 玩家目前位置 (" << playerX << "," << playerY << ")";
    event->accept();
}

void GrasslandScene::setupScene(){

    // 絕對背景
    setSceneRect(0, 0, 3000, 3000);
    setBackgroundBrush(Qt::black);

    // 背景圖片
    bgItem = new QGraphicsPixmapItem(QPixmap(":/images/scene/GrassLand.png"));
    addItem(bgItem);
    bgItem->setPos(1000,1000);

    // 玩家建立
    player = new Player();
    addItem(player);
    playerX = 1530;
    playerY = 2580;
    player->setPos(playerX, playerY);

    // 對話框建立
    uiDialog = new UIdialog(resourceManager->getFont(25), QColor(Qt::black));
    addItem(uiDialog);
    uiDialog->hideDialogue();

    // 定位錨點建立
    anchorCenter = new QGraphicsPixmapItem(QPixmap(":/images/player/player_F.png"));
    addItem(anchorCenter);
    anchorCenter->hide();
    anchorCenter->setPos(playerX, 2420);

    // 屏障建立
    barriers.append(new Barrier(1000, 1000, 416, 71)); // 左上樹叢
    barriers.append(new Barrier(1586, 1000, 416, 71)); // 右上樹叢
    barriers.append(new Barrier(1000, 1000, 77, 1670)); // 左排樹叢
    barriers.append(new Barrier(1925, 1000, 77, 1670)); // 右排樹叢
    barriers.append(new Barrier(1331, 1134, 84, 366)); // 中上樹叢
    barriers.append(new Barrier(1417, 1599, 241, 107)); // 中間樹叢
    barriers.append(new Barrier(1083, 1603, 85, 100)); // 右排樹叢
    barriers.append(new Barrier(1078, 2014, 420, 110)); // 中下樹叢
    barriers.append(new Barrier(1077, 2514, 415, 155)); // 下左樹叢
    barriers.append(new Barrier(1584, 2514, 415, 155)); // 下右樹叢
    for (Barrier *barrier : barriers){
        addItem(barrier);
    }

    // Ledge 建立
    ledges.append(new Ledge(1378, 2316, 540, 15)); // 下右例舉
    ledges.append(new Ledge(1070, 2316, 180, 15)); // 下左例舉
    ledges.append(new Ledge(1752, 2097, 180, 20)); // 中下右例舉
    ledges.append(new Ledge(1456, 1848, 461, 30)); // 中右例舉
    ledges.append(new Ledge(1210, 1844, 165, 30)); // 中例舉
    ledges.append(new Ledge(1079, 1850, 90, 30)); // 中左例舉
    ledges.append(new Ledge(1080, 1432, 257, 30)); // 中上例舉
    ledges.append(new Ledge(1080, 1225, 254, 30)); // 上左例舉
    ledges.append(new Ledge(1411, 1225, 254, 30)); // 上右例舉
    ledges.append(new Ledge(1168, 1640, 248, 30)); // 樹叢中例舉
    for (Ledge *ledge : ledges){
        addItem(ledge);
    }

    // 草地狀元建立
    tallgrasses.append(new Tallgrass(1405, 1248, 522, 212)); // 上
    tallgrasses.append(new Tallgrass(1660, 1536, 257, 210)); // 中
    tallgrasses.append(new Tallgrass(1497, 2005, 255, 200)); // 中下
    tallgrasses.append(new Tallgrass(1070, 2337, 384, 155)); // 下左
    tallgrasses.append(new Tallgrass(1483, 2446, 121, 221)); // 下
    tallgrasses.append(new Tallgrass(1619, 2345, 288, 152)); // 下右

    // 背包建立
    uiBag = new UIbag(resourceManager);
    addItem(uiBag);
    uiBag->hideBag();

}


void GrasslandScene::move(int x, int y){
    int stepX = (x > 0 ) ? -1 : ((x<0) ? 1 : 0);
    int stepY = (y > 0 ) ? -1 : ((y<0) ? 1 : 0);

    // 碰撞測試 (屏障)

    while(true) {
        if (!barrierTest(x, y)){
            qDebug() << "[GrasslandScene] 碰撞測試成功 (" << x << "," << y << ")";
            break;
        }

        if (x == 0 && y == 0){
            break;
        }

        if (abs(x) > abs(y) && x != 0){
            x += stepX;
        } else if (y != 0){
            y += stepY;
        } else if (x != 0){
            x += stepX;
        }
    }

    // 例舉 (ledge) 測試

    while(true) {
        if (!ledgeTest(x, y)){
            qDebug() << "[GrasslandScene] 碰撞 Ledge 測試成功 (" << x << "," << y << ")";
            break;
        }

        if (x == 0 && y == 0){
            break;
        }

        if (abs(x) > abs(y) && x != 0){
            x += stepX;
        } else if (y != 0){
            y += stepY;
        } else if (x != 0){
            x += stepX;
        }
    }

    playerX += x;
    playerY += y;

    // 草地狀元觸發
    for (Tallgrass *grass : tallgrasses ) {

        QRectF playerFutureRect = player->boundingRect().translated(player->pos() + QPointF(x, y));
        QRectF grassRect = grass->boundingRect().translated(grass->pos());
        if (playerFutureRect.intersects(grassRect)) {
            int triggeredChance = QRandomGenerator::global()->bounded(0, 101);
            qDebug() << "[GrasslandScene] 目前在草地狀元裡面！要進行隨機觸發！觸發值" << triggeredChance;
            if(triggeredChance > 84 && (grass->triggered == false)){
                // 15%機率中獎
                grass->triggered = true;
                switchScene(4);
            }
        } else {
            grass->triggered = false; // 離開時清除觸發過了的標籤
        }

    }

    // 更改位置
    player->setPos(playerX, playerY);

    // 大場景特殊判定：要不要繼續至中？他要在一定情況下才符合 建立定位錨點
    anchorCenter->setPos(playerX, playerY);

    if (playerX < 1250){
        anchorCenter->setPos(1250, anchorCenter->pos().y());
    } else if (playerX > 1720){
        anchorCenter->setPos(1720, anchorCenter->pos().y());
    }
    if (playerY > 2420){
        anchorCenter->setPos(anchorCenter->pos().x(), 2420);
    } else if (playerY < 1200){
        anchorCenter->setPos(anchorCenter->pos().x(), 1200);
    }

    centerOnAnchor();
}

bool GrasslandScene::barrierTest(int x, int y){

    for (Barrier *barrier : barriers ) {

        QRectF playerFutureRect = player->boundingRect().translated(player->pos() + QPointF(x, y));
        QRectF barrierRect = barrier->boundingRect().translated(barrier->pos());
        if (playerFutureRect.intersects(barrierRect)) {
            qDebug() << "[GrasslandScene] 不能走路 (barrier)";
            return true; // 沒通過
        }

    }
    return false;
}

bool GrasslandScene::ledgeTest(int x, int y){

    // 只有下 可以無視
    if ((y>0)){
        qDebug() << "[GrasslandScene] show(ledge)";
        return false;
    } else {
        for (Ledge *ledge : ledges ) {

            QRectF playerFutureRect = player->boundingRect().translated(player->pos() + QPointF(x, y));
            QRectF ledgeRect = ledge->boundingRect().translated(ledge->pos());
            if (playerFutureRect.intersects(ledgeRect)) {
                qDebug() << "[GrasslandScene] 不能走路 (ledge)";
                return true; // 沒通過
            }
        }
    }
    return false;
}

void GrasslandScene::centerOnAnchor(){
    GameWindow *gameWindow = qobject_cast<GameWindow*>(parent());
    if (gameWindow) {
        gameWindow->centerOnAnchor();
    }
}

bool GrasslandScene::showBulletinDialog(int x, int y){
    if ((x > 1352) && (x < 1444) && (y > 2270) && (y < 2360)){
        qDebug() << "[GrasslandScene] 顯示布告欄公告（起點）";
        dialogues.clear();
        dialogues << "警告！\n本片區域大量野生寶可夢出沒！\n請注意隨時可能的戰鬥！";
        uiDialog->setDialogues(dialogues);
        uiDialog->setPos(anchorCenter->pos().x(), anchorCenter->pos().y());
        uiDialog->showDialogue();
        return true;
    }
    return false;
}
