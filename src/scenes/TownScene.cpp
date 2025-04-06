#include <QVector>
#include <QRandomGenerator>
#include <QPointF>

#include "TownScene.h"
#include "src/GameWindow.h"

TownScene::TownScene(QObject *parent, ResourceManager *resourceManager) : Scene(parent, resourceManager)
{
    qDebug() << "[TownScene] 主城場景已構建";
    setupScene();
}

void TownScene::keyPressEvent(QKeyEvent *event){

    if (uiDialog->isVisible() || uiBag->isVisible()) {
        QGraphicsScene::keyPressEvent(event); // Pass the event to UI
        return;
    }

    switch(event->key()){
    case Qt::Key_Up:
        qDebug() << "[TownScene] 已按下「↑」";
        player->moveUp();
        move(0, -10);

        if ((playerX > 1639) && (playerX < 1701) && (playerY < 1700) && (playerY > 1690)){
            resourceManager->setPreviousScene("TOWN");
            switchScene(1);
        }
        break;
    case Qt::Key_Down:
        qDebug() << "[TownScene] 已按下「↓」";
        player->moveDown();
        move(0, 10);
        break;
    case Qt::Key_Left:
        qDebug() << "[TownScene] 已按下「←」";
        player->moveLeft();
        move(-10, 0);
        break;
    case Qt::Key_Right:
        qDebug() << "[TownScene] 已按下「→」";
        player->moveRight();
        move(10, 0);
        break;
    case Qt::Key_A:
        qDebug() << "[TownScene] 已按下「A」";
        if (showBulletinDialog(playerX, playerY)) { break; }
        break;
    case Qt::Key_B:
        qDebug() << "[TownScene] 已按下「B」";
        uiBag->showBag();
        uiBag->setPos(anchorCenter->pos().x(), anchorCenter->pos().y());
        break;
    default:
        qDebug() << "[TownScene] 按下未知鍵:" << event->key();
        QGraphicsScene::keyPressEvent(event);
        return;
    }

    qDebug() << "[TownScene] 玩家目前位置 (" << playerX << "," << playerY << ")";
    event->accept();
}

void TownScene::setupScene(){

    // 絕對背景
    setSceneRect(0, 0, 3000, 3000);
    setBackgroundBrush(Qt::black);

    // 背景圖片
    bgItem = new QGraphicsPixmapItem(QPixmap(":/images/scene/Town.png"));
    addItem(bgItem);
    bgItem->setPos(1000, 1000);

    // 玩家建立
    player = new Player();
    addItem(player);
    playerX = 1670;
    playerY = 1700;
    player->setPos(playerX, playerY);

    // 對話匡建立
    uiDialog = new UIdialog(resourceManager->getFont(25), QColor(Qt::black));
    addItem(uiDialog);
    uiDialog->hideDialogue();

    // 定位錨建立
    anchorCenter = new QGraphicsPixmapItem(QPixmap(":/images/player/player_F.png"));
    addItem(anchorCenter);
    anchorCenter->hide();
    anchorCenter->setPos(playerX, playerY);

    // 屏障建立
    barriers.append(new Barrier(1200, 1180, 206, 217)); // 左房
    barriers.append(new Barrier(1585, 1176, 200, 219)); // 右房
    barriers.append(new Barrier(1171, 1335, 33, 64)); // 左房信箱
    barriers.append(new Barrier(1546, 1333, 34, 69)); // 右房信箱
    barriers.append(new Barrier(1000, 1000, 493, 98)); // 螞蟻上樹（左邊）
    barriers.append(new Barrier(1589, 1000, 411, 93)); // 螞蟻上樹（右邊）
    barriers.append(new Barrier(1000, 1000, 81, 1000)); // 螞蟻左樹
    barriers.append(new Barrier(1915, 1000, 85, 1000)); // 螞蟻右樹
    barriers.append(new Barrier(1181, 1999, 850, 1)); // 螞蟻下樹
    barriers.append(new Barrier(1290, 1851, 166, 149)); // 螞蟻游泳池
    barriers.append(new Barrier(1212, 1555, 200, 37)); // 可愛小花圃（左）
    barriers.append(new Barrier(1544, 1797, 246, 55)); // 可惡小柵欄（右）
    barriers.append(new Barrier(1542, 1474, 290, 225)); // 實驗室

    // 箱子建立
    QVector<QPointF> positions = {
        QPointF(1100, 1130),
        QPointF(1100, 1230),
        QPointF(1100, 1330),
        QPointF(1100, 1400),
        QPointF(1100, 1530),
        QPointF(1100, 1630),
        QPointF(1100, 1730),
        QPointF(1100, 1830),
        QPointF(1200, 1130),
        QPointF(1300, 1130),
        QPointF(1450, 1130),
        QPointF(1500, 1130),
        QPointF(1600, 1130),
        QPointF(1700, 1130),
        QPointF(1800, 1130),
        QPointF(1450, 1230),
        QPointF(1450, 1330),
        QPointF(1450, 1400),
        QPointF(1450, 1530),
        QPointF(1450, 1630),
        QPointF(1450, 1730),
        QPointF(1450, 1830),
        QPointF(1850, 1130),
        QPointF(1850, 1230),
        QPointF(1850, 1330),
        QPointF(1850, 1400),
        QPointF(1850, 1530),
        QPointF(1850, 1630),
        QPointF(1850, 1730),
        QPointF(1850, 1830),
        QPointF(1200, 1460),
        QPointF(1300, 1460),
        QPointF(1700, 1400),
        QPointF(1770, 1330)
    };

    for (int i = 0; i < 15; ++i) {
        TownBox *townBox = new TownBox();
        townBoxes.append(townBox);
    }

    for (TownBox *townBox : townBoxes) {
        addItem(townBox);
        townBox->setPos(positions[QRandomGenerator::global()->bounded(positions.size())]);
    }

    for (Barrier *barrier : barriers){
        addItem(barrier);
    }

    // 背包建立
    uiBag = new UIbag(resourceManager);
    addItem(uiBag);
    uiBag->hideBag();

}

void TownScene::move(int x, int y){
    int stepX = (x > 0 ) ? -1 : ((x<0) ? 1 : 0);
    int stepY = (y > 0 ) ? -1 : ((y<0) ? 1 : 0);

    // 碰撞測試

    while(true) {
        if (!barrierTest(x, y)){
            qDebug() << "[TownScene] 碰撞測試成功（於" << x << "," << y << ")";
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

    // 箱子測試
    boxTest(playerX, playerY); // (輸入玩家座標)

    // 更改位置
    player->setPos(playerX, playerY);

    // 大場景特殊判定：要不要繼續至中？他要在一定情況下才符合 建立定位錨點
    anchorCenter->setPos(playerX, playerY);

    if (playerX < 1250){
        anchorCenter->setPos(1250, anchorCenter->pos().y());
    } else if (playerX > 1720){
        anchorCenter->setPos(1720, anchorCenter->pos().y());
    }
    if (playerY > 1758){
        anchorCenter->setPos(anchorCenter->pos().x(), 1758);
    } else if (playerY < 1218){
        anchorCenter->setPos(anchorCenter->pos().x(), 1218);
    }

    centerOnAnchor();
}

bool TownScene::barrierTest(int x, int y){

    for (Barrier *barrier : barriers ) {

        QRectF playerFutureRect = player->boundingRect().translated(player->pos() + QPointF(x, y));
        QRectF barrierRect = barrier->boundingRect().translated(barrier->pos());
        if (playerFutureRect.intersects(barrierRect)) {
            qDebug() << "[TownScene] 不能走路";
            return true; // 沒通過
        }

    }

    return false;
}

bool TownScene::boxTest(int x, int y){
    for (TownBox *townBox : townBoxes) {
        QRectF playerFutureRect = player->boundingRect().translated(player->pos());
        QRectF boxRect = townBox->boundingRect().translated(townBox->pos());
        if (playerFutureRect.intersects(boxRect)){
            qDebug() << "[TownScene] 碰到箱子";
            townBox->setPos(500, 500);

            // 獲得道具
            QString boxMessage;
            switch (QRandomGenerator::global()->bounded(0, 3)){
            case 0:
                switch (QRandomGenerator::global()->bounded(0, 3)){
                case 0:
                    resourceManager->addPokeballCount(1);
                    boxMessage = "從箱子獲得 1 個寶可夢球！";
                    break;
                case 1:
                    resourceManager->addPokeballCount(2);
                    boxMessage = "從箱子獲得 1 個寶可夢球！";
                    break;
                case 2:
                    resourceManager->addPokeballCount(3);
                    boxMessage = "從箱子獲得 1 個寶可夢球！";
                    break;
                default:
                    break;
                }
                break;
            case 1:
                resourceManager->addPotionCount(1);
                boxMessage = "從箱子獲得 1 個傷藥！";
                break;
            case 2:
                resourceManager->addEtherCount(1);
                boxMessage = "從箱子獲得 1 個補藥！";
                break;
            default:
                break;
            }

            dialogues.clear();
            dialogues << boxMessage << "繼續冒險吧！";
            uiDialog->setDialogues(dialogues);
            uiDialog->setPos(anchorCenter->pos().x(), anchorCenter->pos().y());
            uiDialog->showDialogue();
            return true;
        }
    }
    return false;
}

void TownScene::centerOnAnchor(){
    GameWindow *gameWindow = qobject_cast<GameWindow*>(parent());
    if (gameWindow) {
        gameWindow->centerOnAnchor();
    }
}

bool TownScene::showBulletinDialog(int x, int y){
    if ((x > 1360) && (x < 1410) && (y > 1590) && (y < 1602)){
        qDebug() << "[TownScene] 顯示布告欄公告（左花園）";
        dialogues.clear();
        dialogues << "妙蛙種子即將和水箭龜舉行結婚典禮！" << "典禮將舉辦於 2105 年 1 月 17 日\n在成功大飯店 57 樓火焰廳" << "11:00 開始，歡迎蒞臨！";
        uiDialog->setDialogues(dialogues);
        uiDialog->setPos(anchorCenter->pos().x(), anchorCenter->pos().y());
        uiDialog->showDialogue();
        return true;
    } else if ((x > 1182) && (x < 1282) && (y > 1666) && (y < 1766)){
        qDebug() << "[TownScene] 顯示布告欄公告（左花園孤獨下）";
        dialogues.clear();
        dialogues << "終於看開 愛回不來\n我們面前 太多阻礙" << "你的手卻放不開\n寧願沒出息 求我別離開" << "登報人：妙蛙花";
        uiDialog->setDialogues(dialogues);
        uiDialog->setPos(anchorCenter->pos().x(), anchorCenter->pos().y());
        uiDialog->showDialogue();
        return true;
    } else if ((x > 1644) && (x < 1735) && (y > 1772) && (y < 1885)){
        qDebug() << "[TownScene] 顯示布告欄公告（左花園孤獨下）";
        dialogues.clear();
        dialogues << "我們的故事愛就愛到值得\n錯也錯得值得\n愛到翻天覆地也會有結果" << "用盡所有力氣不是為我\n那是為你才這麼做" << "登報人：噴火龍";
        uiDialog->setDialogues(dialogues);
        uiDialog->setPos(anchorCenter->pos().x(), anchorCenter->pos().y());
        uiDialog->showDialogue();
        return true;
    }
    return false;
}
