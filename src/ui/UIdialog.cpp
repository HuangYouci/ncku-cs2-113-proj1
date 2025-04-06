#include "UIdialog.h"
#include <QPainter>
#include <QGraphicsScene>
#include <QDebug>

UIdialog::UIdialog(const QFont &font, const QColor &textColor, QGraphicsItem *parent) : QGraphicsWidget(parent), font(font), textColor(textColor)
{
    setFlag(QGraphicsItem::ItemIsMovable, false);
    setFlag(QGraphicsItem::ItemIsFocusable, true);

    QPixmap backgroundImage(":/images/other/dialog.png");
    background = new QGraphicsPixmapItem(backgroundImage, this);

    // Set the position and size
    background->setPos(-245, 100);

    dialogueText = new QGraphicsTextItem(this);
    dialogueText->setFont(this->font);
    dialogueText->setDefaultTextColor(this->textColor);
    dialogueText->setPos(-235,110);

}

UIdialog::~UIdialog(){}

void UIdialog::setDialogues(const QStringList &dialogues){
    this->dialogues = dialogues;
    currentDialogueIndex = 0;
    updateDialogueText();
}

void UIdialog::showDialogue() {
    currentDialogueIndex = 0;
    updateDialogueText();

    QGraphicsScene* scene = this->scene();
    if (scene && scene->focusItem()) {
        scene->focusItem()->clearFocus(); // Clear focus from other items
    }

    setVisible(true);
    grabKeyboard(); // Grab keyboard input
    setFocus(Qt::OtherFocusReason); // Explicitly set focus on the dialog
}

void UIdialog::hideDialogue(){
    setVisible(false);
    ungrabKeyboard();
}

void UIdialog::keyPressEvent(QKeyEvent *event) {
    qDebug() << "[UIdialog] Key pressed:" << event->key();
    if (event->key() == Qt::Key_A) {
        currentDialogueIndex++;
        if (currentDialogueIndex >= dialogues.size()) {
            hideDialogue();
        } else {
            updateDialogueText();
        }
    }
}

void UIdialog::updateDialogueText(){
    if (dialogues.isEmpty()){
        dialogueText->setPlainText("");
        return;
    }
    dialogueText->setPlainText(dialogues.at(currentDialogueIndex % dialogues.size()));
}
