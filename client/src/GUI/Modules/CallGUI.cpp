//
// Created by clementschmitte on 11/10/2020.
//

#include "CallGUI.hpp"
#include <client/src/GUI/Scenes/MainScene.hpp>
#include <client/src/Utils/Utils.hpp>


CallGUI::CallGUI(MainScene *scene, UserGUI *user, GUIController *guiController)
    :   _text(new QLabel("Waiting for ")),
        _textTimer(new QLabel("")),
        _spacer(new QSpacerItem(10, 150)),
        _endCall(new Button("End call", QSize(120, 45))),
        _scene(scene),
        _user(user),
        _guiController(guiController)
{
    _time = QTime(0, 0, 0);
    _timer = new QTimer();

    _layout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    connect(_timer, SIGNAL(timeout()), this, SLOT(timerRefresh()));
    connect(_endCall, SIGNAL(clicked()), this, SLOT(endCall()));

    _text->setFont(QFont("Arial", 24));

    _layout->addItem(_spacer);
    _layout->addWidget(_text);
    _layout->addItem(_spacer);
    _layout->addWidget(_textTimer);
    _layout->addItem(_spacer);
    _layout->addWidget(_endCall);

    setLayout(_layout);
}

void CallGUI::setFriendCall(FriendBox *friendBox) {
    _friend = friendBox;

    show();
    QString str = _text->text();
    str.append(friendBox->getName());
    _text->setText(str);
}

void CallGUI::runTimer() {
    _timer->start(1000);
    _textTimer->setText(_time.toString("h:mm:ss"));
    timerRefresh();
}

void CallGUI::timerRefresh() {
    _time = _time.addSecs(1);

    _textTimer->setText(_time.toString("h:mm:ss"));
}

CallGUI::~CallGUI() {
    QLayoutItem *item;
    while ((item = _layout->takeAt(0)) != 0)
        _layout->removeItem (item);
}

bool CallGUI::acceptedCall(Common::Response response) {
    std::string str(response.msg);

    str = str.substr(12);
    std::vector<std::string> args = Babel::Utils::split(str, "|");

    if (args[1] == "2") {
        QString string  = QString("In call with ");
        string.append(args[0].c_str());
        _text->setText(string);
        runTimer();
    } else if (args[1] == "3") {
        QString string  = QString(args[0].c_str());
        string.append(" declined your call.");
        _text->setText(string);
    } else if (args[1] == "5") {
        _scene->endCall(response);
    }
}

void CallGUI::endCall() {
    Common::PackageServer *pkg = new Common::PackageServer;

    pkg->magic = Common::g_MagicNumber;
    pkg->id = _user->_id;
    pkg->method = Common::HTTP_POST;
    pkg->command = 7; // END_CALL

    strncpy(pkg->args, _friend->getName().toStdString().c_str(), Common::g_maxMessageLength);
    _guiController->call(Common::HTTP_POST, 7, pkg);
}

void CallGUI::setGUICall(std::string name) {
    QString string  = QString("In call with ");
    string.append(name.c_str());
    _text->setText(string);
    runTimer();
}
