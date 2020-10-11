//
// Created by clementschmitte on 05/10/2020.
//

#ifndef BABEL_USERBOX_HPP
#define BABEL_USERBOX_HPP


#include "FriendBox.hpp"

class UserBox : public FriendBox
{
public:
    /**
     * Basic constructor UserBox
     * @param guiController
     * @param user
     * @param scene
     * @param name
     * @param state
     * @param alignment
     */
    UserBox(GUIController *guiController, UserGUI *user, MainScene *scene, QString name, FriendBox::UserState state, Qt::Alignment alignment = Qt::AlignLeft);
};


#endif //BABEL_USERBOX_HPP
