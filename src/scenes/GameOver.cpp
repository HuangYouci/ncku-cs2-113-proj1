#include "GameOver.h"

#include <QGraphicsTextItem>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>

GameOver::GameOver(QObject *parent, ResourceManager *resourceManager) : Scene(parent, resourceManager) {
    qDebug() << "[GameOver] 已被建構";
    setupScene();
}

void GameOver::keyPressEvent(QKeyEvent *event){
    switch (event->key()){
    case Qt::Key_Q:
        qDebug() << "[GameOver] 已按下「Q」";
        resourceManager->resetData();
        switchScene(0);
        break;
    default:
        qDebug() << "[TitleScene] 任意鍵已被按下";
        break;
    }
}

void GameOver::setupScene() {
    // 建立背景圖片
    QGraphicsPixmapItem *bgItem = new QGraphicsPixmapItem(QPixmap(":/images/scene/game_over.png").scaled(525, 450, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    addItem(bgItem);
    qDebug() << "[GameOver] 背景圖片已載入";

    // 建立文字
    QGraphicsTextItem *overText = new QGraphicsTextItem();
    overText->setPlainText("按下「Q」以重新開始");
    overText->setPos(50, 350);
    overText->setFont(resourceManager->getFont(25));
    overText->setDefaultTextColor(QColor(Qt::white));
    addItem(overText);
    qDebug() << "[GameOver] 文字已建立";

    // 建立動畫
    QGraphicsOpacityEffect *opacity = new QGraphicsOpacityEffect();
    overText->setGraphicsEffect(opacity);
    QPropertyAnimation *animationForward = new QPropertyAnimation(opacity, "opacity");
    QPropertyAnimation *animationBackward = new QPropertyAnimation(opacity, "opacity");
    animationForward->setDuration(1500);
    animationForward->setStartValue(0.2);
    animationForward->setEndValue(1.0);
    animationForward->setEasingCurve(QEasingCurve::InOutSine);
    animationBackward->setDuration(1500);
    animationBackward->setStartValue(1.0);
    animationBackward->setEndValue(0.2);
    animationBackward->setEasingCurve(QEasingCurve::InOutSine);
    QSequentialAnimationGroup *animationGroup = new QSequentialAnimationGroup();
    animationGroup->addAnimation(animationForward);
    animationGroup->addAnimation(animationBackward);
    animationGroup->setLoopCount(-1);
    animationGroup->start();

}
