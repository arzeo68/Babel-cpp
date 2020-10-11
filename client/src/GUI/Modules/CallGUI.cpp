//
// Created by clementschmitte on 11/10/2020.
//

#include "CallGUI.hpp"
#include <client/src/GUI/Scenes/MainScene.hpp>


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

    _text->setFont(QFont("Arial", 24));

    _layout->addItem(_spacer);
    _layout->addWidget(_text);
    _layout->addItem(_spacer);
    _layout->addWidget(_textTimer);
    _layout->addItem(_spacer);
    _layout->addWidget(_endCall);

    Button *_butt = new Button("timer start", QSize(70, 25));

    connect(_butt, SIGNAL(clicked()), this, SLOT(runTimerSlot()));
    _layout->addWidget(_butt);

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

void CallGUI::runTimerSlot() {
    _timer->start(1000);
    _textTimer->setText(_time.toString("h:mm:ss"));
    timerRefresh();
}

CallGUI::~CallGUI() {
    QLayoutItem *item;
    while ((item = _layout->takeAt(0)) != 0)
        _layout->removeItem (item);
}
