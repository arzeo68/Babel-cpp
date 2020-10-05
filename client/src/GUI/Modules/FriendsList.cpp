//
// Created by clementschmitte on 02/10/2020.
//

#include "FriendsList.hpp"
#include "FriendBox.hpp"

FriendsList::FriendsList()
    : Container(new QHBoxLayout)
{
    Container *_overlay = new Container();
    QSpacerItem *spacer = new QSpacerItem(12, 10);

    setTitle("                    Friends List     ");
    for (int i = 1; i < 21; i++) {
        QString name = QString("BabelUser %1").arg(i);
        FriendBox *le_s = new FriendBox(name, FriendBox::UserState::CONNECTED);
        _overlay->addWidget(le_s);
    }

    _layout->addWidget(_overlay);
    _layout->addItem(spacer);
}
