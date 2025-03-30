#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <QFont>

class ResourceManager
{
public:
    ResourceManager();
    ~ResourceManager();

    // 像素字體
    QFont getFont(int size) const;

private:
    // 像素字體
    QFont defaultFont;
};

#endif // RESOURCEMANAGER_H
