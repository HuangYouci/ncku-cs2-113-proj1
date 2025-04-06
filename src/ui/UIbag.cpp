#include "UIbag.h"
#include <QPainter>
#include <QGraphicsScene>
#include <QDebug>

UIbag::UIbag(ResourceManager *resourceManager, QGraphicsItem *parent) : QGraphicsWidget(parent), resourceManager(resourceManager)
{
    setFlag(QGraphicsItem::ItemIsMovable, false);
    setFlag(QGraphicsItem::ItemIsFocusable, true);

    // 背景
    QPixmap backgroundImage(":/images/other/bag.png");
    background01 = new QGraphicsPixmapItem(backgroundImage, this);
    background02 = new QGraphicsPixmapItem(backgroundImage, this);

    background01->setPos(-245, 100);
    background02->setPos(-245, -5);

    // 文字
    titleText = new QGraphicsTextItem(this);
    titleText->setPlainText("背包");
    titleText->setPos(-240, 0);
    titleText->setFont(resourceManager->getFont(25));
    titleText->setDefaultTextColor(QColor(Qt::black));

    // 更新數量
    pokeballBag = nullptr;
    pokeballText = nullptr;
    updateItem();
}

UIbag::~UIbag(){}

void UIbag::showBag() {

    QGraphicsScene* scene = this->scene();
    if (scene && scene->focusItem()) {
        scene->focusItem()->clearFocus(); // Clear focus from other items
    }

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

void UIbag::updateItem(){
    // 累加
    int itemCount = 0;

    // 寶可夢球
    itemCount++;
    QPixmap pokeballImage(":/images/icon/Pokeball_bag.png");
    pokeballBag = new QGraphicsPixmapItem(pokeballImage, this);
    pokeballBag->setPos(-235, itemCount*37);
    pokeballBag->setScale(1.4);
    pokeballText = new QGraphicsTextItem(this);
    pokeballText->setPlainText(QString("寶可夢球 %1").arg(resourceManager->getPokeballCount()));
    pokeballText->setPos(-210, itemCount*37 + 3);
    pokeballText->setFont(resourceManager->getFont(15));
    pokeballText->setDefaultTextColor(QColor(Qt::black));

    // 傷藥球
    itemCount++;
    QPixmap potionImage(":/images/icon/Potion_bag.png");
    potionBag = new QGraphicsPixmapItem(potionImage, this);
    potionBag->setPos(-235, itemCount*37);
    potionBag->setScale(1.4);
    potionText = new QGraphicsTextItem(this);
    potionText->setPlainText(QString("傷藥 %1").arg(resourceManager->getPotionCount()));
    potionText->setPos(-210, itemCount*37 + 3);
    potionText->setFont(resourceManager->getFont(15));
    potionText->setDefaultTextColor(QColor(Qt::black));

    // 復活藥
    itemCount++;
    QPixmap etherImage(":/images/icon/Ether_bag.png");
    etherBag = new QGraphicsPixmapItem(etherImage, this);
    etherBag->setPos(-235, itemCount*37);
    etherBag->setScale(1.4);
    etherText = new QGraphicsTextItem(this);
    etherText->setPlainText(QString("補藥 %1").arg(resourceManager->getEtherCount()));
    etherText->setPos(-210, itemCount*37 + 3);
    etherText->setFont(resourceManager->getFont(15));
    etherText->setDefaultTextColor(QColor(Qt::black));

}
