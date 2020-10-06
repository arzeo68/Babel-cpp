//
// Created by clementschmitte on 05/10/2020.
//

#ifndef BABEL_FRIENDINFO_HPP
#define BABEL_FRIENDINFO_HPP


#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include "Container.hpp"
#include "FriendBox.hpp"

class FriendInfo : public Container
{
public:
    FriendInfo(FriendBox *friendBox);

    void setNewFriendInfo(FriendBox *friendBox);

private:
    void initWidgets();
    QString setFriendStyleSheet(FriendBox::UserState state);

    enum ContainerList {
        CONT_NAME_STATUT,
        CONT_BUTTONS
    };

    enum ButtonList {
        BT_CALL,
        BT_DELETE
    };

    QLabel *_name;
    QLabel *_desc;
    QGroupBox *_box;
    FriendBox *_friend;
    std::array<Container *, 2> _containers;
    std::array<QPushButton *, 2> _buttons;
};


#endif //BABEL_FRIENDINFO_HPP
