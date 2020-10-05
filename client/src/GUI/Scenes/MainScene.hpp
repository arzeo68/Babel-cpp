//
// Created by clementschmitte on 25/09/2020.
//

#ifndef BABEL_MAINSCENE_HPP
#define BABEL_MAINSCENE_HPP

#include <client/src/GUI/MainWindow.hpp>
#include <client/src/GUI/Modules/Container.hpp>
#include <client/src/GUI/Modules/FriendBox.hpp>
#include <client/src/GUI/Modules/FriendsList.hpp>
#include <client/src/GUI/Modules/UserBox.hpp>

class MainScene : public AScene
{
    Q_OBJECT
public:
    explicit MainScene(QObject *parent = Q_NULLPTR);

private:
    void initFriendList();
    void initUser();
    void initFriendInfo();
    void initCall();

    enum ContainerList {
        CONT_USER_INFO,
        CONT_FRIENDS,
        CONT_CHANNELS,
        CONT_FRIEND_INFO,
        CONT_CALL
    };

    std::array<Container *, 5> _containers;
    QScrollArea *_scroll;
    FriendsList *_friendsList;
    UserBox *_user;
};

#endif //BABEL_MAINSCENE_HPP
