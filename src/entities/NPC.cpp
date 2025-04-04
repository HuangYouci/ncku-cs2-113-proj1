#include "NPC.h"

NPC::NPC(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    npcImage = QPixmap(":/images/other/NPC.png");
    setPixmap(npcImage);
}

NPC::~NPC(){}
