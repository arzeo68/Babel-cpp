//
// Created by clementschmitte on 05/10/2020.
//

#include "FriendInfo.hpp"
#include <QDebug>
#include <QtWidgets/QLineEdit>
#include <QtCore/QPropertyAnimation>
#include "client/src/GUI/Scenes/MainScene.hpp"

FriendInfo::FriendInfo(MainScene *scene, FriendBox *friendBox, UserGUI *user, GUIController *guiController)
    :   _scene(scene),
        _containers({new Container(new QHBoxLayout),
                     new Container(new QHBoxLayout)}),
         _buttons({new QPushButton("Start a call"),
                   new QPushButton("Delete friend")}),
        _friend(friendBox),
        _guiController(guiController),
        _user(user)
{
    initWidgets();
}

void FriendInfo::initWidgets()
{
    _name = new QLabel();
    _desc = new QLabel();
    _box = new QGroupBox();

    _name->setText(_friend->getName());
    _name->setContentsMargins(10, 0, 0, 0);
    _name->setFont(QFont("Arial", 20));
    _name->setStyleSheet(_friend->getState() == FriendBox::DISCONNECTED ?
         "QLabel {color : gray; }" : "QLabel {color : black; }");

    _desc->setText(_friend->getDesc());
    _desc->setContentsMargins(0, 30, 0, 0);
    _desc->setFont(QFont("Arial", 12));
    _desc->setWordWrap(true);

    _box->setFixedSize(30, 30);
    _box->setStyleSheet(setFriendStyleSheet(_friend->getState()));

    _containers.at(CONT_NAME_STATUT)->addWidget(_box);
    _containers.at(CONT_NAME_STATUT)->addWidget(_name);
    _containers.at(CONT_BUTTONS)->addWidget(_buttons.at(BT_CALL));
    _containers.at(CONT_BUTTONS)->addWidget(_buttons.at(BT_DELETE));

    _containers.at(CONT_NAME_STATUT)->setStyleSheet("border:none");

    _layout->addWidget(_containers.at(CONT_NAME_STATUT));
    _layout->addWidget(_desc);
    _layout->addWidget(_containers.at(CONT_BUTTONS));
    setLayout(_layout);

    connect(_buttons.at(BT_DELETE), SIGNAL(clicked()), this, SLOT(deleteFriend()));
    connect(_buttons.at(BT_CALL), SIGNAL(clicked()), this, SLOT(callFriend()));
}

QString FriendInfo::setFriendStyleSheet(FriendBox::UserState state)
{
    return state == FriendBox::CONNECTED ?
           "border: 1px solid gray; background-color: green;" :
           state == FriendBox::DISCONNECTED ?
           "border: 1px solid gray; background-color: lightGray;" :
           state == FriendBox::OCCUPIED ?
           "border: 1px solid gray; background-color: red;" : "";
}

void FriendInfo::setNewFriendInfo(FriendBox *friendBox)
{
    _name->setText(friendBox->getName());
    _name->setStyleSheet(friendBox->getState() == FriendBox::DISCONNECTED ?
                         "QLabel {color : gray; }" : "QLabel {color : black; }");
    _desc->setText(friendBox->getDesc());
    _box->setStyleSheet(setFriendStyleSheet(friendBox->getState()));
    if (friendBox->getState() != FriendBox::CONNECTED)
        _buttons.at(BT_CALL)->hide();
    else
        _buttons.at(BT_CALL)->show();
    _friend = friendBox;
    show();
}

void FriendInfo::deleteFriend()
{
    qDebug() << "deleted: " << _friend->getName() << endl;
    Common::PackageServer *pkg = new Common::PackageServer;
    pkg->magic = Common::g_MagicNumber;
    pkg->id = _user->_id;
    pkg->method = Common::HTTP_DELETE;
    pkg->command = 4; // FRIEND

    strncpy(pkg->args, _friend->getName().toStdString().c_str(), Common::g_maxMessageLength);
    _guiController->call(Common::HTTP_DELETE, 4, pkg);
    hide();
}

void FriendInfo::callFriend()
{
    Common::PackageServer *pkg = new Common::PackageServer;
    pkg->magic = Common::g_MagicNumber;
    pkg->id = _user->_id;
    pkg->method = Common::HTTP_POST;
    pkg->command = 6; // START_CALL

    strncpy(pkg->args, _friend->getName().toStdString().c_str(), Common::g_maxMessageLength);
    _guiController->call(Common::HTTP_POST, 6, pkg);
    _scene->setCallInfo(_friend);
}

FriendBox *FriendInfo::getFriend() {
    return _friend;
}

void FriendInfo::setState(FriendBox::UserState state) {
    _friend->setState(state);
}
