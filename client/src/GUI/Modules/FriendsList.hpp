//
// Created by clementschmitte on 02/10/2020.
//

#ifndef BABEL_FRIENDSLIST_HPP
#define BABEL_FRIENDSLIST_HPP


#include <common/TCP/CommonPackages.hpp>
#include <client/src/GUI/GUIController/GUIController.hpp>
#include "Container.hpp"
#include "UserGUI.hpp"
#include "FriendBox.hpp"
#include "InputText.hpp"

class MainScene;
class FriendsList : public Container
{
    Q_OBJECT
public:
    FriendsList(MainScene *scene, UserGUI *user, GUIController *guiController);

    bool fillFriendsList(Common::Response response);
    bool fillFriend(Common::Response response);
    
private:
    MainScene *_scene;
    UserGUI *_user;
    std::vector<std::string> _friendsNames;
    QList<FriendBox *> _friend;
    Container *_overlay;
    InputText *_friendAdd;
    QLabel *_response;
    Button *_submitFriendAdd;
    GUIController *_guiController;

    void loopFriendInfo();

private slots:
    void addNewFriend();
};


#endif //BABEL_FRIENDSLIST_HPP
