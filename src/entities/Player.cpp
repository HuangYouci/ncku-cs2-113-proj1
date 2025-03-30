#include "Player.h"
#include <QDebug>

Player::Player(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    playerImage = QPixmap(":/images/player/player_F.png");
    setPixmap(playerImage);
}

Player::~Player(){}

void Player::moveUp() {
    qDebug() << "[Player] 向上走";
    switch (movingStatus){
    case 0:
        movingStatus = 1;
        break;
    case 1:
        movingStatus = 2;
        break;
    case 2:
        movingStatus = 1;
        break;
    default:
        movingStatus = 0;
    }
    setPixmap(changeMoveImage(movingStatus));
}

void Player::moveDown(){
    qDebug() << "[Player] 向下走";
    switch (movingStatus){
    case 3:
        movingStatus = 4;
        break;
    case 4:
        movingStatus = 5;
        break;
    case 5:
        movingStatus = 4;
        break;
    default:
        movingStatus = 4;
    }
    setPixmap(changeMoveImage(movingStatus));
}

void Player::moveLeft(){
    qDebug() << "[Player] 向左走";
    switch (movingStatus){
    case 6:
        movingStatus = 7;
        break;
    case 7:
        movingStatus = 8;
        break;
    case 8:
        movingStatus = 7;
        break;
    default:
        movingStatus = 7;
    }
    setPixmap(changeMoveImage(movingStatus));
}

void Player::moveRight(){
    qDebug() << "[Player] 向右走";
    switch (movingStatus){
    case 9:
        movingStatus = 10;
        break;
    case 10:
        movingStatus = 11;
        break;
    case 11:
        movingStatus = 10;
        break;
    default:
        movingStatus = 10;
    }
    setPixmap(changeMoveImage(movingStatus));
}

QPixmap Player::changeMoveImage(int status){
    switch (status){
    case 0: return QPixmap(":/images/player/player_B.png");
    case 1: return QPixmap(":/images/player/player_BW1.png");
    case 2: return QPixmap(":/images/player/player_BW2.png");
    case 3: return QPixmap(":/images/player/player_F.png");
    case 4: return QPixmap(":/images/player/player_FW1.png");
    case 5: return QPixmap(":/images/player/player_FW2.png");
    case 6: return QPixmap(":/images/player/player_L.png");
    case 7: return QPixmap(":/images/player/player_LW1.png");
    case 8: return QPixmap(":/images/player/player_LW2.png");
    case 9: return QPixmap(":/images/player/player_R.png");
    case 10: return QPixmap(":/images/player/player_RW1.png");
    case 11: return QPixmap(":/images/player/player_RW2.png");
    default: return QPixmap(":/images/player/player_F.png");
    }
}
