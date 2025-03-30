#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>

class GameWindow: public QMainWindow {
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    int playerX = 245;
    int playerY = 201;

    // 玩家走路狀態 //
    QPixmap playerImage = QPixmap(":/images/player/player_F.png");
    int playerWalkingStatus = 0;
    QPixmap playerImageFromWalkingStatus(int playerWalkingStatus);
};

#endif
