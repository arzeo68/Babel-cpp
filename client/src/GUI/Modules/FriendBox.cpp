//
// Created by clementschmitte on 30/09/2020.
//

#include <QtGui/QPainter>
#include <QtWidgets/QPushButton>
#include <QDebug>
#include <utility>
#include "FriendBox.hpp"

FriendBox::FriendBox(QString name, UserState state, Qt::Alignment alignment)
    :   _name(std::move(name)),
        Container(new QHBoxLayout, alignment),
        _state(state)
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
    qDebug() << "clicked: " << _name;
}
