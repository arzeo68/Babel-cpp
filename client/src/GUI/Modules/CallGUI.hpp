//
// Created by clementschmitte on 11/10/2020.
//

#ifndef BABEL_CALLGUI_HPP
#define BABEL_CALLGUI_HPP


#include <QtCore/QTime>
#include <QtCore/QTimer>
#include <qwindowdefs.h>
#include <client/src/GUI/GUIController/GUIController.hpp>
#include "Container.hpp"
#include "UserGUI.hpp"
#include "FriendBox.hpp"

class MainScene;
/**
 * Call interface on MainScene
 */
class CallGUI : public Container
{
    Q_OBJECT
public:
    ~CallGUI() override;
    /**
     * Constructor for CallGUI
     * @param scene MainScene
     * @param user User connected
     * @param guiController
     */
    CallGUI(MainScene *scene, UserGUI *user, GUIController *guiController);

    /**
     * set friend info on gui
     * @param friendBox
     */
    void setFriendCall(FriendBox *friendBox);

    /**
     * start timer for first time
     */
    void runTimer();

    /**
     * switch gui to call accepted gui
     * @param response
     * @return
     */
    bool acceptedCall(Common::Response response);

    void setGUICall(std::string name);

private slots:
    void timerRefresh();

    void endCall();

private:
    FriendBox *_friend;
    QLabel *_text;
    QLabel *_textTimer;
    QSpacerItem *_spacer;
    Button *_endCall;
    MainScene *_scene;
    UserGUI *_user;
    QTimer *_timer;
    QTime _time;
    GUIController *_guiController;
};


#endif //BABEL_CALLGUI_HPP
