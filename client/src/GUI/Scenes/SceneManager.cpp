//
// Created by clementschmitte on 27/09/2020.
//

#include <iostream>
#include "SceneManager.hpp"

int SceneManager::addScene(AScene *scene, std::string name)
{
    _scenes[name] = scene;
    return QStackedWidget::addWidget(scene);
}

void SceneManager::setScene(std::string name, UserGUI user) {
    std::cout << "init scene started" << std::endl;
    _scenes.at(name)->initScene(user);
    std::cout << "init scene finished" << std::endl;
    QStackedWidget::setCurrentWidget(_scenes.at(name));
}

std::map<std::string, AScene *> SceneManager::getScenes() {
    return _scenes;
}

SceneManager::~SceneManager()
{
    for (auto it = _scenes.begin() ; it != _scenes.end(); it++)
        delete it->second;
    _scenes.clear();
}
