//
// Created by clementschmitte on 27/09/2020.
//

#ifndef BABEL_SCENEMANAGER_HPP
#define BABEL_SCENEMANAGER_HPP

#include <QtWidgets/QStackedWidget>
#include <client/src/GUI/Modules/UserGUI.hpp>
#include "AScene.hpp"

class SceneManager : public QStackedWidget
{
public:
    ~SceneManager();
    /**
     * add new Scene
     * @param scene
     * @param name
     * @return
     */
    int addScene(AScene *scene, std::string name);

    /**
     * set current Scene
     * @param name
     * @param user
     */
    void setScene(std::string name, UserGUI *user);

    /**
     * Basic getter
     * @return
     */
    std::map<std::string, AScene *> getScenes();

private:
    std::map<std::string, AScene *> _scenes;
};


#endif //BABEL_SCENEMANAGER_HPP
