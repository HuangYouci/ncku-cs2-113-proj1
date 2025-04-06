#include "UIchoose.h"
#include <QPainter>
#include <QGraphicsScene>
#include <QDebug>

UIchoose::UIchoose(ResourceManager *resourceManager, QGraphicsItem *parent) : QGraphicsWidget(parent), resourceManager(resourceManager)
{
    setFlag(QGraphicsItem::ItemIsMovable, false);
    setFlag(QGraphicsItem::ItemIsFocusable, true);

    // 背景
    QPixmap backgroundImage(":/images/other/item_bag_background.png");
    background = new QGraphicsPixmapItem(backgroundImage.scaled(420, 190, Qt::IgnoreAspectRatio, Qt::SmoothTransformation), this);

    background->setPos(-200, -20);

    // 文字
    titleText = new QGraphicsTextItem(this);
    titleText->setPlainText("選擇你的初始寶可夢\n透過「→」來選擇、按下「A」來決定");
    titleText->setPos(-190, -10);
    titleText->setFont(resourceManager->getFont(15));
    titleText->setDefaultTextColor(QColor(Qt::black));
    chooseText = new QGraphicsTextItem(this);
    chooseText->setPlainText("小火龍");
    chooseText->setPos(-70, 40);
    chooseText->setFont(resourceManager->getFont(15));
    chooseText->setDefaultTextColor(QColor(Qt::black));

    // 寶可夢
    QPixmap pk1Image(":/images/battle/charmander.png");
    QPixmap pk2Image(":/images/battle/squirtle.png");
    QPixmap pk3Image(":/images/battle/bulbasaur.png");
    QPixmap pk4Image(":/images/player/player_L.png");
    pk1 = new QGraphicsPixmapItem(pk1Image.scaled(128, 128, Qt::KeepAspectRatio, Qt::SmoothTransformation), this);
    pk2 = new QGraphicsPixmapItem(pk2Image.scaled(128, 128, Qt::KeepAspectRatio, Qt::SmoothTransformation), this);
    pk3 = new QGraphicsPixmapItem(pk3Image.scaled(128, 128, Qt::KeepAspectRatio, Qt::SmoothTransformation), this);
    pk4 = new QGraphicsPixmapItem(pk4Image.scaled(128, 128, Qt::KeepAspectRatio, Qt::SmoothTransformation), this);
    pk1->setPos(-200, 30);
    pk2->hide();
    pk2->setPos(-200, 30);
    pk3->hide();
    pk3->setPos(-200, 30);
    pk4->hide();
    pk4->setPos(-200, 30);
}

UIchoose::~UIchoose(){}

void UIchoose::show() {

    QGraphicsScene* scene = this->scene();
    if (scene && scene->focusItem()) {
        scene->focusItem()->clearFocus(); // Clear focus from other items
    }

    setVisible(true);
    grabKeyboard(); // Grab keyboard input
    setFocus(Qt::OtherFocusReason); // Explicitly set focus on the dialog
}

void UIchoose::hide(){
    setVisible(false);
    ungrabKeyboard();
}

void UIchoose::keyPressEvent(QKeyEvent *event) {
    qDebug() << "[UIchoose] Key pressed:" << event->key();
    if (event->key() == Qt::Key_A) {
        switch (currentPK){
        case 0:
            qDebug() << "[UIchoose] 選擇「0」離開";
            hide();
            break;
        case 1:
            qDebug() << "[UIchoose] 選擇「1」獲得小火龍";
            resourceManager->toggleCharmander();
            hide();
            break;
        case 2:
            qDebug() << "[UIchoose] 選擇「2」獲得水箭龜";
            resourceManager->toggleSquirtle();
            hide();
            break;
        case 3:
            qDebug() << "[UIchoose] 選擇「3」獲得妙蛙種子";
            resourceManager->toggleBulbasaur();
            hide();
            break;
        default:
            qDebug() << "[UIchoose] 選擇「N/A」離開";
            hide();
        }
    }
    if (event->key() == Qt::Key_Right){
        switch (currentPK){
        case 0:
            pk1->show();
            pk2->hide();
            pk3->hide();
            pk4->hide();
            chooseText->setPlainText("小火龍");
            currentPK = 1;
            break;
        case 1:
            pk1->hide();
            pk2->show();
            pk3->hide();
            pk4->hide();
            chooseText->setPlainText("水箭龜");
            currentPK = 2;
            break;
        case 2:
            pk1->hide();
            pk2->hide();
            pk3->show();
            pk4->hide();
            chooseText->setPlainText("妙蛙種子");
            currentPK = 3;
            break;
        case 3:
            pk1->hide();
            pk2->hide();
            pk3->hide();
            pk4->show();
            chooseText->setPlainText("不選擇離開");
            currentPK = 0;
            break;
        default:
            currentPK = 0;
        }
    }
}
