//
// Created by clementschmitte on 30/09/2020.
//

#include <QtGui/QPainter>
#include <QtWidgets/QPushButton>
#include <QDebug>
#include <utility>
#include "FriendBox.hpp"
#include "client/src/GUI/Scenes/MainScene.hpp"

FriendBox::FriendBox(MainScene *scene, QString name, UserState state, int statePending, Qt::Alignment alignment)
    :   _name(name),
        Container(new QHBoxLayout, alignment),
        _buttons({std::make_unique<Button>("o", QSize(25, 25)),
                  std::make_unique<Button>("x", QSize(25, 25))}),
        _state(state),
        _scene(scene),
        _desc("Ceci est une description set sur le constructeur de FriendBox"),
        _statePending(statePending)
{
    _label = new QLabel();
    _box = new QGroupBox();

    setMinimumSize(220, 70);
    setMaximumSize(350, 70);

    setState();

    if (_statePending == STATE_PENDING_RECEIVER) {
        _buttons.at(BT_ACCEPT).get()->show();
        _buttons.at(BT_REFUSE).get()->show();
    } else {
        _buttons.at(BT_ACCEPT).get()->hide();
        _buttons.at(BT_REFUSE).get()->hide();
    }

    _label->setText(_name);
    _label->setContentsMargins(10, 0, 0, 0);
    _label->setFont(QFont("Arial", 12));

    addWidget(_box);
    addWidget(_label);
    addWidget(_buttons.at(BT_ACCEPT).get());
    addWidget(_buttons.at(BT_REFUSE).get());
}

void FriendBox::setState()
{
    _box->setFixedSize(15, 15);
    if (_statePending == STATE_PENDING_SENDER || _statePending == STATE_PENDING_RECEIVER) {
        _box->setStyleSheet("border: 1px solid gray; "
                            "background-color: orange;");
        _label->setStyleSheet("QLabel {color : gray; }");
        return;
    }
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
