//
// Created by clementschmitte on 05/10/2020.
//

#include "UserBox.hpp"

UserBox::UserBox(GUIController *guiController, UserGUI *user, MainScene *scene, QString name, FriendBox::UserState state, Qt::Alignment alignment)
    : FriendBox(guiController, user, scene, name, state, 2, alignment)
{
    setFixedSize(350, 90);
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    _label->setFont(QFont("Arial", 24));
    _label->setStyleSheet("font-weight: bold;");
}
