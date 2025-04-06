#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <QFont>

class ResourceManager
{
public:
    ResourceManager();
    ~ResourceManager();

    // === 系統資料 === //
    // 像素字體
    QFont getFont(int size) const;

    // === 玩家資料 === //
    // 上一個場景
    QString getPreviousScene();
    void setPreviousScene(QString target);
    // 和實驗室的大木博士交談次數
    int getTalkToLabNPCTimes();
    void addTalkToLabNPCTimes();
    // 寶可夢球數量
    int getPokeballCount();
    // 傷藥數量
    int getPotionCount();
    // 復活數量
    int getEtherCount();
    // 是否有小火龍
    bool getCharmander();
    void toggleCharmander();
    // 是否有妙哇種子
    bool getBulbasaur();
    void toggleBulbasaur();
    // 是否有水箭龜
    bool getSquirtle();
    void toggleSquirtle();

private:
    // === 系統資料 === //
    // 像素字體
    QFont defaultFont;

    // === 玩家資料 === //
    // 上一個場景
    QString previousScene = "TITLE";
    // 和實驗室的大木博士交談次數
    int talkToLabNPCTimes = 0;
    // 寶可夢球數量
    int pokeballCount = 0;
    // 傷藥數量
    int potionCount = 0;
    // 復活數量
    int etherCount = 0;
    // 是否有小火龍
    bool charmander = false;
    // 是否有妙蛙種子
    bool bulbasaur = false;
    // 是否有水箭龜
    bool squirtle = false;

};

#endif // RESOURCEMANAGER_H
