//
// Created by clementschmitte on 05/10/2020.
//

#ifndef BABEL_FRIENDINFO_HPP
#define BABEL_FRIENDINFO_HPP


#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <client/src/GUI/GUIController/GUIController.hpp>
#include "Container.hpp"
#include "FriendBox.hpp"
#include "UserGUI.hpp"

class FriendInfo : public Container
{
    Q_OBJECT
public:
    FriendInfo(MainScene *scene, FriendBox *friendBox, UserGUI *user, GUIController *guiController);

    void setNewFriendInfo(FriendBox *friendBox);

public slots:
    void deleteFriend();
    void callFriend();

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

    MainScene *_scene;
    QLabel *_name;
    QLabel *_desc;
    QGroupBox *_box;
    FriendBox *_friend;
    std::array<Container *, 2> _containers;
    std::array<QPushButton *, 2> _buttons;
    GUIController *_guiController;
    UserGUI *_user;
};


#endif //BABEL_FRIENDINFO_HPP
