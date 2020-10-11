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
class CallGUI : public Container
{
    Q_OBJECT
public:
    ~CallGUI() override;
    CallGUI(MainScene *scene, UserGUI *user, GUIController *guiController);

    void setFriendCall(FriendBox *friendBox);
    void runTimer();

private slots:
    void timerRefresh();
    void runTimerSlot();

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
