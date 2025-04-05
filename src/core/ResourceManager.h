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
    // 和實驗室的大木博士交談次數
    int getTalkToLabNPCTimes();
    void addTalkToLabNPCTimes();

private:
    // === 系統資料 === //
    // 像素字體
    QFont defaultFont;

    // === 玩家資料 === //
    // 和實驗室的大木博士交談次數
    int talkToLabNPCTimes = 0;

};

#endif // RESOURCEMANAGER_H
