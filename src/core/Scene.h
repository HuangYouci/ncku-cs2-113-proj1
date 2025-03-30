#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include "src/core/ResourceManager.h"

class Scene : public QGraphicsScene {
    Q_OBJECT

public:
    Scene(QObject *parent = nullptr, ResourceManager *resourceManager = nullptr);
    virtual ~Scene();

protected:
    ResourceManager *resourceManager;
};

#endif // SCENE_H
