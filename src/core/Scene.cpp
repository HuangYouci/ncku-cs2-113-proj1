#include "Scene.h"

Scene::Scene(QObject *parent, ResourceManager *resourceManager) : QGraphicsScene(parent), resourceManager(resourceManager)
{

}

Scene::~Scene(){}
