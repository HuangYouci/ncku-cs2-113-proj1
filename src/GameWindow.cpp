#include "GameWindow.h"
#include "Constants.h"
#include <QKeyEvent>
#include <QPainter>

GameWindow::GameWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("[Game] " + QString(Constants::TITLE));
    setFixedSize(525, 450);
}

GameWindow::~GameWindow() {}

void GameWindow::keyPressEvent(QKeyEvent *event){
    switch (event->key()) {
    case Qt::Key_Up:
        playerY -= 10;
        switch (playerWalkingStatus) {
        case 3:
            playerWalkingStatus = 4;
            break;
        case 4:
            playerWalkingStatus = 5;
            break;
        case 5:
            playerWalkingStatus = 4;
            break;
        default:
            playerWalkingStatus = 3;
            break;
        }
        break;
    case Qt::Key_Down:
        playerY += 10;
        switch (playerWalkingStatus) {
        case 0:
            playerWalkingStatus = 1;
            break;
        case 1:
            playerWalkingStatus = 2;
            break;
        case 2:
            playerWalkingStatus = 1;
            break;
        default:
            playerWalkingStatus = 0;
            break;
        }
        break;
    case Qt::Key_Left:
        playerX -= 10;
        switch (playerWalkingStatus) {
        case 6:
            playerWalkingStatus = 7;
            break;
        case 7:
            playerWalkingStatus = 8;
            break;
        case 8:
            playerWalkingStatus = 7;
            break;
        default:
            playerWalkingStatus = 6;
            break;
        }
        break;
    case Qt::Key_Right:
        playerX += 10;
        switch (playerWalkingStatus) {
        case 9:
            playerWalkingStatus = 10;
            break;
        case 10:
            playerWalkingStatus = 11;
            break;
        case 11:
            playerWalkingStatus = 10;
            break;
        default:
            playerWalkingStatus = 9;
            break;
        }
        break;
    }
    playerImage = playerImageFromWalkingStatus(playerWalkingStatus);
    update();
}

void GameWindow::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.drawPixmap(playerX, playerY, 35, 48, playerImage);
}

QPixmap GameWindow::playerImageFromWalkingStatus(int status) {
    switch (status) {
    case 0: return QPixmap(":/images/player/player_F.png");
    case 1: return QPixmap(":/images/player/player_FW1.png");
    case 2: return QPixmap(":/images/player/player_FW2.png");
    case 3: return QPixmap(":/images/player/player_B.png");
    case 4: return QPixmap(":/images/player/player_BW1.png");
    case 5: return QPixmap(":/images/player/player_BW2.png");
    case 6: return QPixmap(":/images/player/player_L.png");
    case 7: return QPixmap(":/images/player/player_LW1.png");
    case 8: return QPixmap(":/images/player/player_LW2.png");
    case 9: return QPixmap(":/images/player/player_R.png");
    case 10: return QPixmap(":/images/player/player_RW1.png");
    case 11: return QPixmap(":/images/player/player_RW2.png");
    default: return QPixmap(":/images/player/player_F.png");
    }
}
