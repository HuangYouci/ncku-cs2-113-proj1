#include "UIbag.h"
#include <QPainter>
#include <QGraphicsScene>
#include <QDebug>

UIbag::UIbag(ResourceManager *resourceManager, QGraphicsItem *parent) : QGraphicsWidget(parent), resourceManager(resourceManager) {
    setFlag(QGraphicsItem::ItemIsMovable, false);
    setFlag(QGraphicsItem::ItemIsFocusable, true);

    // 背景
    QPixmap backgroundImage(":/images/other/bag.png");
    background01 = new QGraphicsPixmapItem(backgroundImage, this);
    background02 = new QGraphicsPixmapItem(backgroundImage, this);
    background01->setPos(-245, 105);
    background02->setPos(-245, -5);

    // 文字
    titleText = new QGraphicsTextItem(this);
    titleText->setPlainText("背包");
    titleText->setPos(-240, 0);
    titleText->setFont(resourceManager->getFont(25));
    titleText->setDefaultTextColor(QColor(Qt::black));

    // 初始化所有物品
    pokeballBag = new QGraphicsPixmapItem(QPixmap(":/images/icon/Pokeball_bag.png"), this);
    pokeballText = new QGraphicsTextItem(this);
    potionBag = new QGraphicsPixmapItem(QPixmap(":/images/icon/Potion_bag.png"), this);
    potionText = new QGraphicsTextItem(this);
    etherBag = new QGraphicsPixmapItem(QPixmap(":/images/icon/Ether_bag.png"), this);
    etherText = new QGraphicsTextItem(this);
    charmanderBag = nullptr;
    charmanderText = nullptr;
    bulbasaurBag = nullptr;
    bulbasaurText = nullptr;
    squirtleBag = nullptr;
    squirtleText = nullptr;

    updateItem(); // 初次更新
}

UIbag::~UIbag(){}

void UIbag::showBag() {

    QGraphicsScene* scene = this->scene();
    if (scene && scene->focusItem()) {
        scene->focusItem()->clearFocus(); // Clear focus from other items
    }

    updateItem();
    setVisible(true);
    grabKeyboard(); // Grab keyboard input
    setFocus(Qt::OtherFocusReason); // Explicitly set focus on the dialog
}

void UIbag::hideBag(){
    setVisible(false);
    ungrabKeyboard();
}

void UIbag::keyPressEvent(QKeyEvent *event) {
    qDebug() << "[UIbag] Key pressed:" << event->key();
    if (event->key() == Qt::Key_B) {
        hideBag();
    }
}

void UIbag::updateItem() {
    int itemCount = 0;

    // 寶可夢球
    itemCount++;
    pokeballBag->setPos(-235, itemCount * 37);
    pokeballBag->setScale(1.4);
    pokeballText->setPlainText(QString("寶可夢球 %1").arg(resourceManager->getPokeballCount()));
    pokeballText->setPos(-210, itemCount * 37 + 3);
    pokeballText->setFont(resourceManager->getFont(15));
    pokeballText->setDefaultTextColor(QColor(Qt::black));

    // 傷藥
    itemCount++;
    potionBag->setPos(-235, itemCount * 37);
    potionBag->setScale(1.4);
    potionText->setPlainText(QString("傷藥 %1").arg(resourceManager->getPotionCount()));
    potionText->setPos(-210, itemCount * 37 + 3);
    potionText->setFont(resourceManager->getFont(15));
    potionText->setDefaultTextColor(QColor(Qt::black));

    // 復活藥
    itemCount++;
    etherBag->setPos(-235, itemCount * 37);
    etherBag->setScale(1.4);
    etherText->setPlainText(QString("補藥 %1").arg(resourceManager->getEtherCount()));
    etherText->setPos(-210, itemCount * 37 + 3);
    etherText->setFont(resourceManager->getFont(15));
    etherText->setDefaultTextColor(QColor(Qt::black));

    // 小火龍（動態顯示）
    if (resourceManager->getCharmander()) {
        qDebug() << "[UIbag] 目前小火龍狀態為：有";
        if (!charmanderBag) {
            charmanderBag = new QGraphicsPixmapItem(QPixmap(":/images/battle/charmander.png").scaled(22, 22, Qt::KeepAspectRatio, Qt::SmoothTransformation), this);
            charmanderText = new QGraphicsTextItem(this);
        }
        itemCount++;
        charmanderBag->setPos(-235, itemCount * 37);
        charmanderBag->setScale(1.4);
        charmanderText->setPlainText("小火龍");
        charmanderText->setPos(-210, itemCount * 37 + 3);
        charmanderText->setFont(resourceManager->getFont(15));
        charmanderText->setDefaultTextColor(QColor(Qt::black));
    } else {
        qDebug() << "[UIbag] 目前小火龍狀態為：無";
        if (charmanderBag) {
            delete charmanderBag;
            charmanderBag = nullptr;
        }
        if (charmanderText) {
            delete charmanderText;
            charmanderText = nullptr;
        }
    }

    // 妙蛙種子（動態顯示）
    if (resourceManager->getBulbasaur()) {
        qDebug() << "[UIbag] 目前妙蛙種子狀態為：有";
        if (!bulbasaurBag) {
            bulbasaurBag = new QGraphicsPixmapItem(QPixmap(":/images/battle/bulbasaur.png").scaled(22, 22, Qt::KeepAspectRatio, Qt::SmoothTransformation), this);
            bulbasaurText = new QGraphicsTextItem(this);
        }
        itemCount++;
        bulbasaurBag->setPos(-235, itemCount * 37);
        bulbasaurBag->setScale(1.4);
        bulbasaurText->setPlainText("妙蛙種子");
        bulbasaurText->setPos(-210, itemCount * 37 + 3);
        bulbasaurText->setFont(resourceManager->getFont(15));
        bulbasaurText->setDefaultTextColor(QColor(Qt::black));
    } else {
        qDebug() << "[UIbag] 目前妙蛙種子狀態為：無";
        if (bulbasaurBag) {
            delete bulbasaurBag;
            bulbasaurBag = nullptr;
        }
        if (bulbasaurText) {
            delete bulbasaurText;
            bulbasaurText = nullptr;
        }
    }

    // 水箭龜（動態）
    if (resourceManager->getSquirtle()) {
        qDebug() << "[UIbag] 目前水箭龜狀態為：有";
        if (!squirtleBag) {
            squirtleBag = new QGraphicsPixmapItem(QPixmap(":/images/battle/squirtle.png").scaled(22, 22, Qt::KeepAspectRatio, Qt::SmoothTransformation), this);
            squirtleText = new QGraphicsTextItem(this);
        }
        itemCount++;
        squirtleBag->setPos(-235, itemCount * 37);
        squirtleBag->setScale(1.4);
        squirtleText->setPlainText("水箭龜");
        squirtleText->setPos(-210, itemCount * 37 + 3);
        squirtleText->setFont(resourceManager->getFont(15));
        squirtleText->setDefaultTextColor(QColor(Qt::black));
    } else {
        qDebug() << "[UIbag] 目前水箭龜狀態為：無";
        if (squirtleBag) {
            delete squirtleBag;
            squirtleBag = nullptr;
        }
        if (squirtleText) {
            delete squirtleText;
            squirtleText = nullptr;
        }
    }
}
