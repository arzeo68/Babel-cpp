//
// Created by clementschmitte on 02/10/2020.
//

#include <iostream>
#include <client/src/Utils/Utils.hpp>
#include "FriendsList.hpp"
#include "client/src/GUI/Scenes/MainScene.hpp"

FriendsList::FriendsList(MainScene *scene, UserGUI *user, GUIController *guiController)
    :   Container(new QVBoxLayout),
        _scene(scene),
        _user(user),
        _response(new QLabel),
        _overlay(new Container),
        _friendAdd(new InputText("Add a new friend", 18)),
        _submitFriendAdd(new Button("Add", QSize(50, 20))),
        _guiController(guiController)
{
    QSpacerItem *spacer = new QSpacerItem(12, 10);
    Common::PackageServer *pkg = new Common::PackageServer;

    _response->setText("");

    pkg->magic = Common::g_MagicNumber;
    pkg->id = _user->_id;
    pkg->method = Common::HTTP_GET;
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

    _layout->addWidget(_friendAdd);
    _layout->addWidget(_submitFriendAdd);
    _layout->addWidget(_overlay);
    _layout->setAlignment(Qt::AlignTop);


    connect(_submitFriendAdd, SIGNAL(clicked()), this, SLOT(addNewFriend()));

    _guiController->call(Common::HTTP_GET, 4, pkg);
    Common::Response resp;
    strncpy(resp.msg, "FRIEND|LIST|Clément|Alexis|1|0-Clément|JG|1|1-Clem|Clément|1|0-Dems|Clément|2|1", Common::g_maxMessageLength);
    fillFriendsList(resp);
}

bool FriendsList::fillFriendsList(Common::Response response)
{
    std::string str(response.msg);
    int state;

    if (response.code != Common::HTTPCodes_e::HTTP_OK)
        return false;
    str = str.substr(12);
    std::vector<std::string> friends = Babel::Utils::split(str, "-");

    for (auto it : friends) {
        std::vector<std::string> newFriend = Babel::Utils::split(it, "|");
        if (newFriend[0] == _user->_name) {
            state = stoi(newFriend[2]) == 1 ? 0 : 2;
            _friends[newFriend[1]] = new FriendBox(_scene, QString::fromUtf8(newFriend[1].c_str()), (FriendBox::UserState)stoi(newFriend[3]), state);
            _overlay->addWidget(_friends[newFriend[1]]);
        } else {
            state = stoi(newFriend[2]) == 1 ? 1 : 2;
            _friends[newFriend[0]] = new FriendBox(_scene, QString::fromUtf8(newFriend[0].c_str()), (FriendBox::UserState)stoi(newFriend[3]), state);
            _overlay->addWidget(_friends[newFriend[0]]);
        }
    }
    return true;
}

bool FriendsList::fillFriend(Common::Response response)
{
    std::string str(response.msg);
    std::string name;
    size_t pos = 0;
    char delimiter = '|';

    if (response.code != Common::HTTPCodes_e::HTTP_OK)
        return false;
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
    pkg->method = Common::HTTP_GET;
    pkg->command = 1000; // FRIEND_INFO

    for (auto newFriend : _friendsNames) {
        strncpy(pkg->args, newFriend.c_str(), Common::g_maxMessageLength);
        // call avec le GUI CONTROLLER
        Common::Response response;
        response.code = Common::HTTPCodes_e::HTTP_OK;
        std::string str = newFriend;
        newFriend.append("|0");
        strncpy(response.msg, newFriend.c_str(), Common::g_maxMessageLength);
        fillFriend(response);
    }
}

void FriendsList::addNewFriend()
{
    Common::PackageServer *pkg = new Common::PackageServer;
    pkg->magic = Common::g_MagicNumber;
    pkg->id = _user->_id;
    pkg->method = Common::HTTP_PUT;
    pkg->command = 4; // FRIEND

    std::string str = _friendAdd->text().toStdString();
    if (str == "")
        return;
    _friendAdd->setText("");
    strncpy(pkg->args, str.c_str(), Common::g_maxMessageLength);
    _guiController->call(Common::HTTP_PUT, 4, pkg);
}

bool FriendsList::deleteFriend(Common::Response response) {
    std::string str(response.msg);
    std::map<std::string, FriendBox *>::iterator it;
    
    if (response.code != Common::HTTPCodes_e::HTTP_OK)
        return false;
    it = _friends.find(str);
    if (it == _friends.end())
        return false;
    _overlay->removeWidget(_friends[str]);
    _friends[str]->hide();
    _friends.erase(str);
    return true;
}

