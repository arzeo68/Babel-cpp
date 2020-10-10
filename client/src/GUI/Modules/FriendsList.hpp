//
// Created by clementschmitte on 02/10/2020.
//

#ifndef BABEL_FRIENDSLIST_HPP
#define BABEL_FRIENDSLIST_HPP


#include <common/TCP/CommonPackages.hpp>
#include "Container.hpp"
#include "UserGUI.hpp"
#include "FriendBox.hpp"

class MainScene;
class FriendsList : public Container
{
public:
    FriendsList(MainScene *scene, UserGUI *user);

    bool fillFriendsList(Common::Response response);
    bool addFriend(Common::Response response);

private:
    MainScene *_scene;
    UserGUI *_user;
    std::vector<std::string> _friendsNames;
    QList<FriendBox *> _friend;
    Container *_overlay;

    void loopFriendInfo();
};


#endif //BABEL_FRIENDSLIST_HPP
