//
// Created by clementschmitte on 05/10/2020.
//

#ifndef BABEL_USERBOX_HPP
#define BABEL_USERBOX_HPP


#include "FriendBox.hpp"

class UserBox : public FriendBox
{
public:
    UserBox(QString name, FriendBox::UserState state, Qt::Alignment alignment = Qt::AlignLeft);
};


#endif //BABEL_USERBOX_HPP
