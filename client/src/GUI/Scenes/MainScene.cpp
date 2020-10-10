//
// Created by clementschmitte on 25/09/2020.
//

#include "MainScene.hpp"
#include <QGraphicsScene>
#include <QDebug>
#include <client/src/GUI/Modules/UserBox.hpp>
#include <iostream>
#include <common/TCP/CommonPackages.hpp>

MainScene::MainScene(QObject *parent)
    :   _containers({new Container(),
                     new Container(),
                     new Container(),
                     new Container(new QVBoxLayout, Qt::AlignTop),
                     new Container()}),
        _friendInfo(new FriendInfo(new FriendBox(this, "name", FriendBox::UserState::CONNECTED)))
{
    _layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    std::cout << "MainScene Constructor" << std::endl;

    setLayout(_layout);
}

void MainScene::initFriendList()
{
    QSpacerItem *spacer = new QSpacerItem(10, 25);

    _friendsList = new FriendsList(this, _user);
    _scroll = new QScrollArea();

    _scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _scroll->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::MinimumExpanding);
    _scroll->setWidget(_friendsList);

    _layout->addItem(spacer, 1, 0);
    _layout->addWidget(_scroll, 2, 0);
}

void MainScene::initUser() {
    _userBox = new UserBox(this, QString::fromUtf8(_user->_name.c_str()), FriendBox::UserState::CONNECTED, Qt::AlignHCenter);

    _layout->addWidget(_userBox, 0, 0, 1, 2);
}

void MainScene::initFriendInfo()
{
    _containers.at(CONT_FRIEND_INFO)->setFixedSize(300, 450);
    _containers.at(CONT_FRIEND_INFO)->addWidget(_friendInfo);
    _containers.at(CONT_FRIEND_INFO)->hide();

    _layout->addWidget(_containers.at(CONT_FRIEND_INFO), 2, 1);
}


void MainScene::initCall()
{
    _containers.at(CONT_CALL)->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    _layout->addWidget(_containers.at(CONT_CALL), 2, 2);

}

void MainScene::setFriendInfo(FriendBox *_friend) {
    if (_containers.at(CONT_FRIEND_INFO)->isHidden())
        _containers.at(CONT_FRIEND_INFO)->show();

    _friendInfo->setNewFriendInfo(_friend);

//    notif->show();
//    QString name = QString("New call from ");
//    name.append(_friend->getName());
//    notif->setText(name);
//    anim->start();

}
void MainScene::initScene(UserGUI user)
{
    _user = new UserGUI(user);
    initFriendList();
    std::cout << "initFriendList passed" << std::endl;
    initUser();
    std::cout << "initUser passed" << std::endl;
    initFriendInfo();
    std::cout << "initFriendInfo passed" << std::endl;
    initCall();
    std::cout << "initCall passed" << std::endl;
//    notifCall();
}





//void MainScene::notifCall()
//{
//    notif = new QLineEdit("", this);
//    notif->setReadOnly(true);
//    notif->setTextMargins(50, 0, 0, 0);
//    notif->setFixedSize(500, 100);
//
//    accept_button = new QPushButton("Accept", notif);
//    accept_button->setGeometry(QRect(QPoint(260, 25),
//                                     QSize(100, 50)));
//
//    refuse_button = new QPushButton("Refuse", notif);
//    refuse_button->setGeometry(QRect(QPoint(380, 25),
//                                     QSize(100, 50)));
//
//    anim = new QPropertyAnimation(notif, "geometry");
//    anim->setDuration(800);
//    anim->setStartValue(QRect(368, -150, 500, 100));
//    qDebug() << "x: " << notif->pos().x() << " && y: " <<notif->pos().y();
//    anim->setEndValue(QRect(368, 15, 500, 100));
//    notif->hide();
//    _layout->addWidget(notif, 0, 2, 1, 2);
//}
