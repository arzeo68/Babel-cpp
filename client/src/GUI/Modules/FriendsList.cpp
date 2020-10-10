//
// Created by clementschmitte on 02/10/2020.
//

#include <iostream>
#include "FriendsList.hpp"
#include "client/src/GUI/Scenes/MainScene.hpp"

FriendsList::FriendsList(MainScene *scene, UserGUI *user)
    :   Container(new QHBoxLayout),
        _scene(scene),
        _user(user)
{
    QSpacerItem *spacer = new QSpacerItem(12, 10);
    Common::PackageServer *pkg = new Common::PackageServer;

    _overlay = new Container();

    pkg->magic = Common::g_MagicNumber;
    pkg->id = _user->_id;
    pkg->method = Common::GET;
    pkg->command = 4; //FRIEND

    setTitle("                    Friends List     ");
//    for (int i = 1; i < 21; i++) {
//        QString name = QString("BabelUser %1").arg(i);
//        FriendBox *le_s = new FriendBox(_scene, name, FriendBox::UserState::CONNECTED);
//        _overlay->addWidget(le_s);
//    }
//
//    QString name = QString("BabelUser déco");
//    FriendBox *le_s = new FriendBox(_scene, name, FriendBox::UserState::DISCONNECTED);
//    _overlay->addWidget(le_s);
    _layout->addWidget(_overlay);
    _layout->addItem(spacer);


    // en dessouse : call gui controller
    Common::Response response;

    response.code = Common::HTTPCodes_e::OK;
    strncpy(response.msg, "Clément|JG_la_famax|Arzeo|1", Common::g_maxMessageLength);
    fillFriendsList(response);
}

bool FriendsList::fillFriendsList(Common::Response response)
{
    std::string str(response.msg);
    std::string token;
    size_t pos = 0;
    char delimiter = '|';

    while (str.length() != 0) {
        pos = str.find(delimiter);
        token = str.substr(0, pos);
        if (token == "1") {
            loopFriendInfo();
            break;
        } else if (token == "0") {
            loopFriendInfo();
            break;
            // A CHANGER
        }
        _friendsNames.push_back(token);
        str.erase(0, pos + 1);
    }
    return true;
}

bool FriendsList::addFriend(Common::Response response)
{
    std::string str(response.msg);
    std::string name;
    size_t pos = 0;
    char delimiter = '|';

    pos = str.find(delimiter);
    name = str.substr(0, pos);
    str.erase(0, pos + 1);

    _friend.push_back(new FriendBox(_scene, QString::fromUtf8(name.c_str()), str == "0" ? FriendBox::DISCONNECTED : FriendBox::CONNECTED));
    _overlay->addWidget(_friend.back());
    // Définir avec les autres sous quel format est reçu le friend
    return true;
}

void FriendsList::loopFriendInfo()
{
    Common::PackageServer *pkg = new Common::PackageServer;
    pkg->magic = Common::g_MagicNumber;
    pkg->id = _user->_id;
    pkg->method = Common::GET;
    pkg->command = 1000; // FRIEND_INFO

    for (auto newFriend : _friendsNames) {
        strncpy(pkg->args, newFriend.c_str(), Common::g_maxMessageLength);
        // call avec le GUI CONTROLLER
        Common::Response response;
        response.code = Common::HTTPCodes_e::OK;
        std::string str = newFriend;
        newFriend.append("|0");
        strncpy(response.msg, newFriend.c_str(), Common::g_maxMessageLength);
        addFriend(response);
    }
}
