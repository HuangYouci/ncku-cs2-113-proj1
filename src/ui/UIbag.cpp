#include "UIbag.h"
#include <QGraphicsScene>
#include <QDebug>

UIbag::UIbag(ResourceManager *resourceManager, QGraphicsItem *parent) : QGraphicsWidget(parent), resourceManager(resourceManager) {
    setFlag(QGraphicsItem::ItemIsMovable, false);
    setFlag(QGraphicsItem::ItemIsFocusable, true);

    updateItem(); // 更新
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
    // 先刪掉舊的

    for (QGraphicsPixmapItem *item : pokemonsImage){
        if (item) {
            scene()->removeItem(item);
            delete item;
        }
    }
    pokemonsImage.clear();

    for (QGraphicsTextItem *item : pokemonsText){
        if (item) {
            scene()->removeItem(item);
            delete item;
        }
    }
    pokemonsText.clear();

    for (QGraphicsRectItem *item : pokemonsBackground){
        if (item) {
            scene()->removeItem(item);
            delete item;
        }
    }
    pokemonsBackground.clear();

    int itemCount = -1;

    // 背包標題
    if(true){
        qDebug() << "[UIbag] 建立標題";
        itemCount++;

        QGraphicsRectItem *whiteSquare = new QGraphicsRectItem(0, 0 , 200, 38, this);
        whiteSquare->setPos(-250, -200 + itemCount * 37);
        whiteSquare->setBrush(QBrush(Qt::white));
        whiteSquare->setPen(QPen(Qt::NoPen));
        pokemonsBackground.append(whiteSquare);

        QGraphicsTextItem *pokemonText = new QGraphicsTextItem(this);
        pokemonText->setPlainText("背包");
        pokemonText->setPos(-240, -197 + itemCount * 37);
        pokemonText->setFont(resourceManager->getFont(25));
        pokemonText->setDefaultTextColor(QColor(Qt::black));
        pokemonsText.append(pokemonText);
    }

    // 寶可夢球
    if(true){
        qDebug() << "[UIbag] 建立寶可夢球";
        itemCount++;

        QGraphicsRectItem *whiteSquare = new QGraphicsRectItem(0, 0 , 200, 38, this);
        whiteSquare->setPos(-250, -200 + itemCount * 37);
        whiteSquare->setBrush(QBrush(Qt::white));
        whiteSquare->setPen(QPen(Qt::NoPen));
        pokemonsBackground.append(whiteSquare);

        QGraphicsPixmapItem *pokemonImage = new QGraphicsPixmapItem(QPixmap(":/images/icon/Pokeball_bag.png").scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation), this);
        pokemonImage->setPos(-240, -200 + itemCount * 37);
        pokemonsImage.append(pokemonImage);

        QGraphicsTextItem *pokemonText = new QGraphicsTextItem(this);
        pokemonText->setPlainText(QString("寶可夢球 %1").arg(resourceManager->getPokeballCount()));
        pokemonText->setPos(-210, -197 + itemCount * 37);
        pokemonText->setFont(resourceManager->getFont(15));
        pokemonText->setDefaultTextColor(QColor(Qt::black));
        pokemonsText.append(pokemonText);
    }

    // 傷藥
    if(true){
        qDebug() << "[UIbag] 建立傷藥";
        itemCount++;

        QGraphicsRectItem *whiteSquare = new QGraphicsRectItem(0, 0 , 200, 38, this);
        whiteSquare->setPos(-250, -200 + itemCount * 37);
        whiteSquare->setBrush(QBrush(Qt::white));
        whiteSquare->setPen(QPen(Qt::NoPen));
        pokemonsBackground.append(whiteSquare);

        QGraphicsPixmapItem *pokemonImage = new QGraphicsPixmapItem(QPixmap(":/images/icon/Potion_bag.png").scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation), this);
        pokemonImage->setPos(-240, -200 + itemCount * 37);
        pokemonsImage.append(pokemonImage);

        QGraphicsTextItem *pokemonText = new QGraphicsTextItem(this);
        pokemonText->setPlainText(QString("傷藥 %1").arg(resourceManager->getPotionCount()));
        pokemonText->setPos(-210, -197 + itemCount * 37);
        pokemonText->setFont(resourceManager->getFont(15));
        pokemonText->setDefaultTextColor(QColor(Qt::black));
        pokemonsText.append(pokemonText);
    }

    // 補藥
    if(true){
        qDebug() << "[UIbag] 建立補藥";
        itemCount++;

        QGraphicsRectItem *whiteSquare = new QGraphicsRectItem(0, 0 , 200, 38, this);
        whiteSquare->setPos(-250, -200 + itemCount * 37);
        whiteSquare->setBrush(QBrush(Qt::white));
        whiteSquare->setPen(QPen(Qt::NoPen));
        pokemonsBackground.append(whiteSquare);

        QGraphicsPixmapItem *pokemonImage = new QGraphicsPixmapItem(QPixmap(":/images/icon/Ether_bag.png").scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation), this);
        pokemonImage->setPos(-240, -200 + itemCount * 37);
        pokemonsImage.append(pokemonImage);

        QGraphicsTextItem *pokemonText = new QGraphicsTextItem(this);
        pokemonText->setPlainText(QString("補藥 %1").arg(resourceManager->getEtherCount()));
        pokemonText->setPos(-210, -197 + itemCount * 37);
        pokemonText->setFont(resourceManager->getFont(15));
        pokemonText->setDefaultTextColor(QColor(Qt::black));
        pokemonsText.append(pokemonText);
    }

    // 寶可夢列表
    for (Pokemon pokemon: resourceManager->pokemons){
        qDebug() << "[UIbag] 建立寶可夢：" << pokemon.name;
        itemCount++;

        QGraphicsRectItem *whiteSquare = new QGraphicsRectItem(0, 0 , 200, 38, this);
        whiteSquare->setPos(-250, -200 + itemCount * 37);
        whiteSquare->setBrush(QBrush(Qt::white));
        whiteSquare->setPen(QPen(Qt::NoPen));
        pokemonsBackground.append(whiteSquare);

        QGraphicsPixmapItem *pokemonImage = new QGraphicsPixmapItem(pokemon.image.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation), this);
        pokemonImage->setPos(-240, -200 + itemCount * 37);
        pokemonsImage.append(pokemonImage);

        QGraphicsTextItem *pokemonText = new QGraphicsTextItem(this);
        pokemonText->setPlainText(QString("%1").arg(pokemon.name));
        pokemonText->setPos(-210, -197 + itemCount * 37);
        pokemonText->setFont(resourceManager->getFont(15));
        pokemonText->setDefaultTextColor(QColor(Qt::black));
        pokemonsText.append(pokemonText);

        QGraphicsTextItem *pokemonText2 = new QGraphicsTextItem(this);
        pokemonText2->setPlainText(QString("Lv.%1  HP:%2/%3  %4屬性").arg(pokemon.level).arg(pokemon.hp).arg(pokemon.maxhp).arg(tellType(pokemon.type)));
        pokemonText2->setPos(-210, -180 + itemCount * 37);
        pokemonText2->setFont(resourceManager->getFont(10));
        pokemonText2->setDefaultTextColor(QColor(Qt::black));
        pokemonsText.append(pokemonText2);
    }
}

QString UIbag::tellType(int type){
    switch (type){
    case 1:
        return "火";
    case 2:
        return "水";
    case 3:
        return "草";
    default:
        return "一般";
    }
}
