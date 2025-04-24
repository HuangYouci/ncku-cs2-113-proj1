#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <QFont>
#include <QPixmap>

// Pokemon Data

struct PokemonAttack {
    QString name;
    int power;
};

struct Pokemon {
    QString name;
    QPixmap image;
    QPixmap imageback;
    int level;
    int defense;
    int attack;
    int maxhp;
    int hp;
    int pp;
    QList<PokemonAttack> attacks;
    int type = 0; // 0 = NORMAL
};

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
    // 是否領取初始寶可夢
    bool getReceivedInitPokemon();
    void playerReceivedInitPokemon();
    // 寶可夢球數量
    int getPokeballCount();
    void addPokeballCount(int count);
    // 傷藥數量
    int getPotionCount();
    void addPotionCount(int count);
    // 復活數量
    int getEtherCount();
    void addEtherCount(int count);
    // 寶可夢列表
    QList<Pokemon> pokemons;
    // 重置
    void resetData();

private:
    // === 系統資料 === //
    // 像素字體
    QFont defaultFont;

    // === 玩家資料 === //
    // 上一個場景
    QString previousScene = "TITLE";
    // 和實驗室的大木博士交談次數
    int talkToLabNPCTimes = 0;
    // 是否領取初始寶可夢
    bool receivedInitPokemon = false;
    // 寶可夢球數量
    int pokeballCount = 0;
    // 傷藥數量
    int potionCount = 0;
    // 復活數量
    int etherCount = 0;

};

#endif // RESOURCEMANAGER_H

// This program is written by HuangYouci
