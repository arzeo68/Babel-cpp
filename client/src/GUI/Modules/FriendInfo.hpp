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
    /**
     * Constructor for FriendInfo
     * @param scene
     * @param friendBox
     * @param user
     * @param guiController
     */
    FriendInfo(MainScene *scene, FriendBox *friendBox, UserGUI *user, GUIController *guiController);

    /**
     * Set new friend info for update interface
     * @param friendBox
     */
    void setNewFriendInfo(FriendBox *friendBox);

    /**
     * Basic getter
     * @return
     */
    FriendBox *getFriend();

    /**
     * Basic setter
     * @param state
     */
    void setState(FriendBox::UserState state);

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
