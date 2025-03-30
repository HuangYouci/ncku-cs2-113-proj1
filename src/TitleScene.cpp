#include "TitleScene.h"

#include <QGraphicsTextItem>
#include <QFont>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>

TitleScene::TitleScene(QObject *parent) : QGraphicsScene(parent) {
    qDebug() << "[TitleScene] 已被建構";
    setupScene();
}

void TitleScene::setupScene() {
    // 建立背景圖片
    QPixmap background(":/images/scene/start_menu.png");
    QSize viewSize(525, 450);
    background = background.scaled(viewSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    setSceneRect(0, 0, 525, 450);
    setBackgroundBrush(QBrush(background));
    qDebug() << "[TitleScene] 背景圖片已載入";

    // 建立文字
    QGraphicsTextItem *welcomeText = new QGraphicsTextItem();
    welcomeText->setPlainText("點擊任意鍵以開始");
    welcomeText->setPos(50, 350);
    QFont welcomeTextFont("Arial", 30);
    welcomeText->setFont(welcomeTextFont);
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
