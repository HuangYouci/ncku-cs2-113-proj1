#include "TownBox.h"
#include <QDebug>

TownBox::TownBox(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    boxImage = QPixmap(":/images/other/box.png");
    setPixmap(boxImage);
}

TownBox::~TownBox(){}
