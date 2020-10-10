//
// Created by clementschmitte on 05/10/2020.
//

#include "FriendInfo.hpp"
#include <QDebug>
#include <QtWidgets/QLineEdit>
#include <QtCore/QPropertyAnimation>

FriendInfo::FriendInfo(FriendBox *friendBox)
    :   _containers({new Container(new QHBoxLayout),
                     new Container(new QHBoxLayout)}),
         _buttons({new QPushButton("Start a call"),
                   new QPushButton("Delete friend")}),
        _friend(friendBox)
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
    _friend = friendBox;
}