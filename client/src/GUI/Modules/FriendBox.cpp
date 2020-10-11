//
// Created by clementschmitte on 30/09/2020.
//

#include <QtGui/QPainter>
#include <QtWidgets/QPushButton>
#include <QDebug>
#include <utility>
#include "FriendBox.hpp"
#include "client/src/GUI/Scenes/MainScene.hpp"

FriendBox::FriendBox(GUIController *guiController, UserGUI *user, MainScene *scene, QString name, UserState state, int statePending, Qt::Alignment alignment)
    :   _guiController(guiController),
        _user(user),
        _name(name),
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

    connect(_buttons.at(BT_ACCEPT).get(), SIGNAL(clicked()), this, SLOT(acceptFriend()));
    connect(_buttons.at(BT_REFUSE).get(), SIGNAL(clicked()), this, SLOT(refuseFriend()));
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
    if (_statePending == STATE_FRIEND)
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

void FriendBox::setPendingState(int state) {
    _statePending = state;
    setState();
}

void FriendBox::acceptFriend() {
    Common::PackageServer *pkg = new Common::PackageServer;

    pkg->magic = Common::g_MagicNumber;
    pkg->id = _user->_id;
    pkg->method = Common::HTTP_POST;
    pkg->command = 4; //FRIEND

    std::string arg = _name.toStdString();
    arg.append("|1");
    strncpy(pkg->args, arg.c_str(), Common::g_maxMessageLength);
    _guiController->call(Common::HTTP_POST, 4, pkg);
}

void FriendBox::refuseFriend() {
    Common::PackageServer *pkg = new Common::PackageServer;

    pkg->magic = Common::g_MagicNumber;
    pkg->id = _user->_id;
    pkg->method = Common::HTTP_POST;
    pkg->command = 4; //FRIEND

    std::string arg = _name.toStdString();
    arg.append("|0");
    strncpy(pkg->args, arg.c_str(), Common::g_maxMessageLength);
    _guiController->call(Common::HTTP_POST, 4, pkg);
}
