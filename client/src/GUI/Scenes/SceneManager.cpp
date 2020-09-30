//
// Created by clementschmitte on 27/09/2020.
//

#include "SceneManager.hpp"

int SceneManager::addScene(AScene *scene, std::string name)
{
    _scenes[name] = scene;
    return QStackedWidget::addWidget(scene);
}

void SceneManager::setScene(std::string name) {
    QStackedWidget::setCurrentWidget(_scenes.at(name));
}
