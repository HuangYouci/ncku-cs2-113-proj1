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

// === 系統資料 === //
// 像素字體

QFont ResourceManager::getFont(int size) const {
    QFont font = defaultFont;
    font.setPointSize(size);
    return font;
}


// === 玩家資料 === //
// 和實驗室的大木博士交談次數
int ResourceManager::getTalkToLabNPCTimes() {
    return talkToLabNPCTimes;
}

void ResourceManager::addTalkToLabNPCTimes() {
    talkToLabNPCTimes++;
}

// 寶可夢球數量
int ResourceManager::getPokeballCount(){
    return pokeballCount;
}

// 傷藥數量
int ResourceManager::getPotionCount(){
    return potionCount;
}

// 復活數量
int ResourceManager::getEtherCount(){
    return etherCount;
}
