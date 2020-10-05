//
// Created by clementschmitte on 25/09/2020.
//

#include "MainScene.hpp"
#include <QGraphicsScene>
#include <client/src/GUI/Modules/UserBox.hpp>

MainScene::MainScene(QObject *parent)
    :   _containers({new Container(),
                     new Container(),
                     new Container(),
                     new Container(new QVBoxLayout, Qt::AlignTop),
                     new Container()})
{
    _layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    initFriendList();
    initUser();
    initFriendInfo();
    initCall();
    setLayout(_layout);
}

void MainScene::initFriendList()
{
    QSpacerItem *spacer = new QSpacerItem(10, 25);

    _friendsList = new FriendsList();
    _scroll = new QScrollArea();

    _scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _scroll->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::MinimumExpanding);
    _scroll->setWidget(_friendsList);

    _layout->addItem(spacer, 1, 0);
    _layout->addWidget(_scroll, 2, 0);
}

void MainScene::initUser() {
    _user = new UserBox("Clement", FriendBox::UserState::CONNECTED, Qt::AlignHCenter);

    _layout->addWidget(_user, 0, 0, 1, 2);
}

void MainScene::initFriendInfo()
{
    _containers.at(CONT_FRIEND_INFO)->setFixedSize(250, 450);
//    _containers.at(CONT_FRIEND_INFO)->hide();

    _layout->addWidget(_containers.at(CONT_FRIEND_INFO), 2, 1);
}


void MainScene::initCall()
{
    _containers.at(CONT_CALL)->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    _layout->addWidget(_containers.at(CONT_CALL), 2, 2);
}

