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

// 上一個場景
QString ResourceManager::getPreviousScene(){
    return previousScene;
}
void ResourceManager::setPreviousScene(QString target){
    previousScene = target;
}

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

// 是否有小火龍
bool ResourceManager::getCharmander(){
    return charmander;
}

void ResourceManager::toggleCharmander(){
    if (charmander){
        qDebug() << "[ResourceManager] 觸發小火龍更新，更新為：沒有";
        charmander = false;
    } else {
        qDebug() << "[ResourceManager] 觸發小火龍更新，更新為：有";
        charmander = true;
    }
}

// 是否有妙哇種子
bool ResourceManager::getBulbasaur(){
    return bulbasaur;
}
void ResourceManager::toggleBulbasaur(){
    if (bulbasaur){
        bulbasaur = false;
    } else {
        bulbasaur = true;
    }
}

// 是否有水箭龜
bool ResourceManager::getSquirtle(){
    return squirtle;
}

void ResourceManager::toggleSquirtle(){
    if (squirtle){
        squirtle = false;
    } else {
        squirtle = true;
    }
}
