//
// Created by clementschmitte on 02/10/2020.
//

#include <iostream>
#include <client/src/Utils/Utils.hpp>
#include "FriendsList.hpp"
#include "client/src/GUI/Scenes/MainScene.hpp"

FriendsList::FriendsList(MainScene *scene, UserGUI *user, GUIController *guiController, std::map<std::string, FriendBox *> friends)
    :   Container(new QVBoxLayout),
        _scene(scene),
        _user(user),
        _response(new QLabel),
        _friends(friends),
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
//        FriendBox *le_s = new FriendBox(_guiController, user, _scene, name, FriendBox::UserState::CONNECTED, 2);
//        _overlay->addWidget(le_s);
//    }
//
//    QString name = QString("BabelUser déco");
//    FriendBox *le_s = new FriendBox(_guiController, _user ,_scene, name, FriendBox::UserState::DISCONNECTED);
//    _overlay->addWidget(le_s);

    _layout->addWidget(_friendAdd);
    _layout->addWidget(_submitFriendAdd);
    _layout->addWidget(_overlay);
    connect(_submitFriendAdd, SIGNAL(clicked()), this, SLOT(addNewFriend()));

    if (!friends.empty())
        initList(friends);
    else
        _guiController->call(Common::HTTP_GET, 4, pkg);
//    Common::Response resp;
//    resp.code = Common::HTTPCodes_e::HTTP_OK;
//    strncpy(resp.msg, "FRIEND|LIST|Clément|Alexis|1|0-Clément|JG|1|1-Clem|Clément|1|0-Dems|Clément|2|1", Common::g_maxMessageLength);
//    fillFriendsList(resp);
}

bool FriendsList::fillFriendsList(Common::Response response)
{
    std::string str(response.msg);
    int state;

    str = str.substr(12);
    std::vector<std::string> friends = Babel::Utils::split(str, "-");

    std::cout << "USERNAME: " << _user->_name << std::endl;
    if (friends.empty())
        return false;
    for (auto it : friends) {
        std::vector<std::string> newFriend = Babel::Utils::split(it, "|");
        if (newFriend[0] == _user->_name) {
            state = stoi(newFriend[2]) == 1 ? 0 : 2;
            _friends[newFriend[1]] = new FriendBox(_guiController, _user ,_scene, QString::fromUtf8(newFriend[1].c_str()), (FriendBox::UserState)stoi(newFriend[3]), state);
            _overlay->addWidget(_friends[newFriend[1]]);
        } else if (newFriend[1] == _user->_name) {
            state = stoi(newFriend[2]) == 1 ? 1 : 2;
            _friends[newFriend[0]] = new FriendBox(_guiController, _user ,_scene, QString::fromUtf8(newFriend[0].c_str()), (FriendBox::UserState)stoi(newFriend[3]), state);
            _overlay->addWidget(_friends[newFriend[0]]);
        } else {
            return false;
        }
    }
    _scene->refreshFriendsList(_friends);
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

    _friends[name] = new FriendBox(_guiController, _user ,_scene, QString::fromUtf8(name.c_str()), str == "0" ? FriendBox::DISCONNECTED : FriendBox::CONNECTED, 0);
    _overlay->addWidget(_friends[name]);
    _scene->refreshFriendsList(_friends);
    return true;
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
//    Common::Response resp;
//    resp.code = Common::HTTPCodes_e::HTTP_OK;
//    strncpy(resp.msg, str.c_str(), Common::g_maxMessageLength);
//    fillFriend(resp);
}


bool FriendsList::deleteFriend(Common::Response response) {
    std::string str(response.msg);

    if (response.code != Common::HTTPCodes_e::HTTP_OK) {
        std::cout << "Bad request." << std::endl;
        return false;
    }
    return deleteFriend(str);
}

bool FriendsList::requestFriend(Common::Response response) {
    std::string str(response.msg);
    std::string name;
    size_t pos = 0;

    str = str.substr(15);
    if (response.code != Common::HTTPCodes_e::HTTP_OK)
        return false;

    _friend.push_back(new FriendBox(_guiController, _user, _scene, QString::fromUtf8(name.c_str()), str == "0" ? FriendBox::DISCONNECTED : FriendBox::CONNECTED, 1));
    _overlay->addWidget(_friend.back());
    return true;
}

bool FriendsList::statusFriend(Common::Response response) {
    std::string str(response.msg);

    str = str.substr(14);
    if (response.code != Common::HTTPCodes_e::HTTP_OK)
        return false;
    std::vector<std::string> args = Babel::Utils::split(str, "|");

    if (args[1] == "2") {
        _friends[args[0]]->setPendingState(2);
    } else if (args[1] == "3") {
        deleteFriend(args[0]);
    }

}

bool FriendsList::deleteFriend(std::string name) {
    std::map<std::string, FriendBox *>::iterator it;

    it = _friends.find(name);
    if (it == _friends.end())
        return false;
    _overlay->removeWidget(_friends[name]);
    _friends[name]->hide();
    _friends.erase(name);
}

bool FriendsList::deleteFriendNotif(Common::Response response) {
    std::string str(response.msg);

    str = str.substr(14);
    return deleteFriend(str);
}

void FriendsList::initList(std::map<std::string, FriendBox *> friends) {
    for (auto it : friends)
        _overlay->addWidget(it.second);
}

bool FriendsList::responseRequest(Common::Response response) {
    std::string str(response.msg);

    if (response.code != Common::HTTPCodes_e::HTTP_OK)
        return false;

    if (str == "false") {
        return false;
    } else {
        std::vector<std::string> args = Babel::Utils::split(str, "|");
        if (args[1] == "0")
            deleteFriend(args[0]);
        else if (args[1] == "1") {
            _friends[args[0]]->setPendingState(2);
            Common::PackageServer *pkg = new Common::PackageServer;
            pkg->magic = Common::g_MagicNumber;
            pkg->id = _user->_id;
            pkg->method = Common::HTTP_GET;
            pkg->command = 5; // FRIEND_IS_CONNECTED
            strncpy(pkg->args, args[0].c_str(), Common::g_maxMessageLength);
            _guiController->call(Common::HTTP_GET, 5, pkg);
        }
    }
    return true;
}

bool FriendsList::friendIsConnected(Common::Response response) {
    std::string str(response.msg);

    if (response.code != Common::HTTPCodes_e::HTTP_OK)
        return false;
    std::vector<std::string> args = Babel::Utils::split(str, "|");
    if (args[1] == "0")
        _friends[args[0]]->setState(FriendBox::DISCONNECTED);
    else if (args[1] == "1")
        _friends[args[0]]->setState(FriendBox::CONNECTED);
    return false;
}

