#include "src/core/ResourceManager.h"

#include <QFontDatabase>
#include <QDebug>

ResourceManager::ResourceManager(){
    int fontID = QFontDatabase::addApplicationFont(":/fonts/unifont.ttf");
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontID).at(0);
    defaultFont = QFont(fontFamily, 20);
}

ResourceManager::~ResourceManager(){

}

QFont ResourceManager::getFont(int size) const {
    QFont font = defaultFont;
    font.setPointSize(size);
    return font;
}
