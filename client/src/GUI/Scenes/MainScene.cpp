//
// Created by clementschmitte on 25/09/2020.
//

#include "MainScene.hpp"
#include <QGraphicsScene>
#include <QDebug>
#include <client/src/GUI/Modules/UserBox.hpp>
#include <iostream>
#include <common/TCP/CommonPackages.hpp>

MainScene::MainScene(GUIController *guiController, QWidget *parent)
    :   _containers({new Container(),
                     new Container(),
                     new Container(),
                     new Container(new QVBoxLayout, Qt::AlignTop),
                     new Container()}),
        _guiController(guiController)
{
    _layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    std::cout << "MainScene Constructor" << std::endl;

    setLayout(_layout.get());
}

void MainScene::initFriendList()
{
    QSpacerItem *spacer = new QSpacerItem(10, 25);

    std::cout << "before" << std::endl;
    _friendsList = new FriendsList(this, _user, _guiController, std::map<std::string, FriendBox *>());
    std::cout << "after" << std::endl;
    _scroll = new QScrollArea();

    _scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _scroll->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::MinimumExpanding);
    _scroll->setWidget(_friendsList);

    _layout->addItem(spacer, 1, 0);
    _layout->addWidget(_scroll, 2, 0);
}

void MainScene::initUser() {
    _userBox = new UserBox(_guiController, _user, this, QString::fromUtf8(_user->_name.c_str()), FriendBox::UserState::CONNECTED, Qt::AlignHCenter);

    _layout->addWidget(_userBox, 0, 0, 1, 2);
}

void MainScene::initFriendInfo()
{
    _friendInfo = new FriendInfo(this, new FriendBox(_guiController, _user, this, "name", FriendBox::UserState::CONNECTED), _user, _guiController);

    _containers.at(CONT_FRIEND_INFO)->setFixedSize(300, 450);
    _containers.at(CONT_FRIEND_INFO)->addWidget(_friendInfo);
    _containers.at(CONT_FRIEND_INFO)->hide();

    _layout->addWidget(_containers.at(CONT_FRIEND_INFO), 2, 1);
}


void MainScene::initCall()
{
    _call = new CallGUI(this, _user, _guiController);

    _call->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    _call->hide();
    _layout->addWidget(_call, 2, 2);

}

void MainScene::setFriendInfo(FriendBox *_friend) {
    if (_containers.at(CONT_FRIEND_INFO)->isHidden())
        _containers.at(CONT_FRIEND_INFO)->show();

    _friendInfo->setNewFriendInfo(_friend);
}
void MainScene::initScene(UserGUI *user)
{
    _user = user;
    initFriendList();
    std::cout << "initFriendList passed" << std::endl;
    initUser();
    std::cout << "initUser passed" << std::endl;
    initFriendInfo();
    std::cout << "initFriendInfo passed" << std::endl;
    initCall();
    std::cout << "initCall passed" << std::endl;
    initNotif();
}

FriendsList *MainScene::getFriendsList() {
    return _friendsList;
}

void MainScene::refreshFriendsList(std::map<std::string, FriendBox *> list) {
    _layout->removeWidget(_scroll);
    _friendsList = new FriendsList(this, _user, _guiController, list);
    _scroll = new QScrollArea();

    _scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _scroll->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::MinimumExpanding);
    _scroll->setWidget(_friendsList);

    _layout->addWidget(_scroll, 2, 0);
}

void MainScene::setCallInfo(FriendBox *friendBox) {
    _call->setFriendCall(friendBox);
}

bool MainScene::callNotification(Common::Response response) {
//    CALL|START|Clément|127.0.0.1|65281
    std::string str(response.msg);

    str = str.substr(11);
    std::vector<std::string> args = split(str, "|");
    _name = args[0];
    _ip = args[1];
    _port = args[2];
    notif->show();
    QString text = QString("Incoming call from ");
    text.append(args[0].c_str());
    notif->setText(text);
    anim->start();
    return true;
}

void MainScene::initNotif()
{
    notif = new QLineEdit("", this);
    notif->setReadOnly(true);
    notif->setTextMargins(50, 0, 0, 0);
    notif->setFixedSize(500, 100);

    accept_button = new QPushButton("Accept", notif);
    accept_button->setGeometry(QRect(QPoint(260, 25),
                                     QSize(100, 50)));

    refuse_button = new QPushButton("Refuse", notif);
    refuse_button->setGeometry(QRect(QPoint(380, 25),
                                     QSize(100, 50)));

    anim = new QPropertyAnimation(notif, "geometry");
    anim->setDuration(800);
    anim->setStartValue(QRect(368, -150, 500, 100));
    anim->setEndValue(QRect(368, 15, 500, 100));
    notif->hide();
    _layout->addWidget(notif, 0, 2, 1, 2);

    connect(accept_button, SIGNAL(clicked()), this, SLOT(acceptCall()));
    connect(refuse_button, SIGNAL(clicked()), this, SLOT(refuseCall()));
}

std::vector<std::string> MainScene::split(std::string str, std::string token){
    std::vector<std::string>result;
    while(str.size()){
        int index = str.find(token);
        if(index!=std::string::npos){
            result.push_back(str.substr(0,index));
            str = str.substr(index+token.size());
            if(str.size()==0)result.push_back(str);
        }else{
            result.push_back(str);
            str = "";
        }
    }
    return result;
}

void MainScene::acceptCall() {
    Common::PackageServer *pkg = new Common::PackageServer;

    pkg->magic = Common::g_MagicNumber;
    pkg->id = _user->_id;
    pkg->method = Common::HTTP_POST;
    pkg->command = 6; // START_CALL

    strncpy(pkg->args, _name.c_str(), Common::g_maxMessageLength);
    _guiController->call(Common::HTTP_POST, 6, pkg);
    notif->hide();
    _layout->removeWidget(notif);
    initNotif();
    setCallInfo(_friendsList->getFriends()[_name]);
//    std::string string = std::string("CALL|STATUS|");
//    string.append(_name);
//    string.append("|2");
//    Common::Response response;
//    response.code = Common::HTTPCodes_e::HTTP_OK;
//    strncpy(response.msg, string.c_str(), Common::g_maxMessageLength);
//    _call->acceptedCall(response);
    std::cout << _ip << "|" << _port << std::endl;
    _guiController->getUdp().startConnection(_ip, _port);
    _userBox->setState(FriendBox::OCCUPIED);
}

void MainScene::refuseCall() {
    Common::PackageServer *pkg = new Common::PackageServer;

    pkg->magic = Common::g_MagicNumber;
    pkg->id = _user->_id;
    pkg->method = Common::HTTP_POST;
    pkg->command = 7; // END_CALL

    strncpy(pkg->args, _name.c_str(), Common::g_maxMessageLength);
    _guiController->call(Common::HTTP_POST, 7, pkg);
    notif->hide();
    _layout->removeWidget(notif);
    initNotif();
}

CallGUI *MainScene::getCallGUI() {
    return _call;
}

bool MainScene::endCall(Common::Response response) {
    _call->hide();
    _layout->removeWidget(_call);
    initCall();
    _guiController->getUdp().stopConnection();
    return true;
}

void MainScene::startUdpCall() {
    std::cout << "INFOS CALL START UDP: " << _ip << "|" << _port << std::endl;

    _guiController->getUdp().startConnection(_ip, _port);
    _userBox->setState(FriendBox::OCCUPIED);
}

bool MainScene::infosCall(Common::Response response) {
    std::string str(response.msg);

    std::cout << "INFOS CALL:" << str << std::endl;
    if (str == "true") {
        _call->setGUICall(_name);
        return true;
    }
    std::vector<std::string> args = split(str, "|");
    _ip = args[0];
    _port = args[1];
    return true;
}

FriendInfo *MainScene::getFriendInfo() {
    return _friendInfo;
}

void MainScene::setFriendInfoState(FriendBox::UserState state) {
    std::cout << "state: " << state << std::endl;
    _friendInfo->setState(state);
}
