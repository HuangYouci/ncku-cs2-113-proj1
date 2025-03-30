#include "src/scenes/TitleScene.h"

#include <QGraphicsTextItem>
#include <QFont>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QFontDatabase>
#include <QKeyEvent>

TitleScene::TitleScene(QObject *parent, ResourceManager *resourceManager) : Scene(parent, resourceManager) {
    qDebug() << "[TitleScene] 已被建構";
    setupScene();
}

void TitleScene::keyPressEvent(QKeyEvent *event){
    switch (event->key()){
    default:
        qDebug() << "[TitleScene] 任意鍵已被按下";
        emit startGame();
        break;
    }
}

void TitleScene::setupScene() {
    // 建立背景圖片
    QPixmap background(":/images/scene/start_menu.png");
    QSize viewSize(525, 450);
    background = background.scaled(viewSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QGraphicsPixmapItem *bgItem = new QGraphicsPixmapItem(background);
    addItem(bgItem);
    setBackgroundBrush(QBrush(background));
    qDebug() << "[TitleScene] 背景圖片已載入";

    // 建立文字
    QGraphicsTextItem *welcomeText = new QGraphicsTextItem();
    welcomeText->setPlainText("點擊任意鍵以開始");
    welcomeText->setPos(50, 350);
    welcomeText->setFont(resourceManager->getFont(25));
    welcomeText->setDefaultTextColor(QColor(Qt::white));
    addItem(welcomeText);
    qDebug() << "[TitleScene] 文字已建立";

    // 建立動畫
    QGraphicsOpacityEffect *opacity = new QGraphicsOpacityEffect();
    welcomeText->setGraphicsEffect(opacity);
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
