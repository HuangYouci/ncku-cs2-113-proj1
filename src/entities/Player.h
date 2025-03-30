#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QKeyEvent>

class Player : public QGraphicsPixmapItem
{
public:
    Player(QGraphicsItem *parent = nullptr);
    ~Player() override;

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

private:
    QPixmap playerImage;
    int moveSpeed = 10;
    int movingStatus = 0;
    QPixmap changeMoveImage(int status);
};

#endif // PLAYER_H
