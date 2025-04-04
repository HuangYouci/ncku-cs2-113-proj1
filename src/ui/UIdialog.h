#ifndef UIDIALOG_H
#define UIDIALOG_H

#include <QGraphicsWidget>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QKeyEvent>
#include <QStringList>
#include <QFont>
#include <QColor>


class UIdialog : public QGraphicsWidget
{
   Q_OBJECT

public:
    UIdialog(const QFont &font, const QColor &textColor, QGraphicsItem *parent = nullptr);
    ~UIdialog() override;

    void setDialogues(const QStringList &dialogues);
    void showDialogue();
    void hideDialogue();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    QGraphicsPixmapItem *background;
    QGraphicsTextItem *dialogueText;
    QStringList dialogues;
    int currentDialogueIndex;
    QFont font;
    QColor textColor;
    QGraphicsPixmapItem *backgroundImage;

    void updateDialogueText();

};

#endif // UIDIALOG_H
