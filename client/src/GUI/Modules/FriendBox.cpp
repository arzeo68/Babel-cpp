//
// Created by clementschmitte on 30/09/2020.
//

#include <QtGui/QPainter>
#include <QtWidgets/QPushButton>
#include <QDebug>
#include <utility>
#include "FriendBox.hpp"
#include "client/src/GUI/Scenes/MainScene.hpp"

FriendBox::FriendBox(MainScene *scene, QString name, UserState state, Qt::Alignment alignment)
    :   _name(name),
        Container(new QHBoxLayout, alignment),
        _state(state),
        _scene(scene),
        _desc("Ceci est une description set sur le constructeur de FriendBox")
{
    _label = new QLabel();
    _box = new QGroupBox();

    setMinimumSize(220, 70);
    setMaximumSize(350, 70);

    setState();

    _label->setText(_name);
    _label->setContentsMargins(10, 0, 0, 0);
    _label->setFont(QFont("Arial", 12));

    addWidget(_box);
    addWidget(_label);
}

void FriendBox::setState()
{
    _box->setFixedSize(15, 15);
    if (_state == CONNECTED)
        _box->setStyleSheet("border: 1px solid gray; "
                            "background-color: green;");
    else if (_state == DISCONNECTED) {
        _box->setStyleSheet("border: 1px solid gray; "
                            "background-color: lightGray;");
        _label->setStyleSheet("QLabel {color : gray; }");
    } else if (_state == OCCUPIED)
        _box->setStyleSheet("border: 1px solid gray; "
                            "background-color: red;");
}

void FriendBox::mousePressEvent(QMouseEvent *event) {
    _scene->setFriendInfo(this);
    qDebug() << "clicked: " << _name;
}

QString FriendBox::getName() {
    return _name;
}


FriendBox::UserState FriendBox::getState() {
    return _state;
}

QString FriendBox::getDesc() {
    return _desc;
}
