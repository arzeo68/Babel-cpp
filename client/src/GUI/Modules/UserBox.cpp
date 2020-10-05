//
// Created by clementschmitte on 05/10/2020.
//

#include "UserBox.hpp"

UserBox::UserBox(QString name, FriendBox::UserState state, Qt::Alignment alignment)
    : FriendBox(name, state, alignment)
{
    setMinimumSize(220, 90);
    setMaximumSize(350, 90);
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    _label->setFont(QFont("Arial", 24));
    _label->setStyleSheet("font-weight: bold;");
}
