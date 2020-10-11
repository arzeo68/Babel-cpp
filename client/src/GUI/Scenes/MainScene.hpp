//
// Created by clementschmitte on 25/09/2020.
//

#ifndef BABEL_MAINSCENE_HPP
#define BABEL_MAINSCENE_HPP

#include <array>
#include <client/src/GUI/MainWindow.hpp>
#include <client/src/GUI/Modules/Container.hpp>
#include <client/src/GUI/Modules/FriendBox.hpp>
#include <client/src/GUI/Modules/FriendsList.hpp>
#include <client/src/GUI/Modules/UserBox.hpp>
#include <client/src/GUI/Modules/CallGUI.hpp>
#include "client/src/GUI/Modules/FriendInfo.hpp"

class MainScene : public AScene
{
    Q_OBJECT
public:
    /**
     * Constructor for MainScene
     * @param guiController
     * @param parent
     */
    explicit MainScene(GUIController *guiController, QWidget *parent = Q_NULLPTR);

    /**
     * Basic getter
     * @return
     */
    FriendsList *getFriendsList();

    /**
     * Basic getter
     * @return
     */
    CallGUI *getCallGUI();

    /**
     * init every widgets
     * @param user
     */
    void initScene(UserGUI *user) override;

    /**
     * Basic setter
     * @param friendBox
     */
    void setFriendInfo(FriendBox *friendBox);

    /**
     * refresh interface friends list
     * @param list
     */
    void refreshFriendsList(std::map<std::string, FriendBox *> list);

    /**
     * Basic setter
     * @param friendBox
     */
    void setCallInfo(FriendBox *friendBox);

    /**
     * start udp call with guiController->udp
     */
    void startUdpCall();

    /**
     * Basic getter
     * @return
     */
    FriendInfo *getFriendInfo();

    /**
     * Basic setter
     * @param state
     */
    void setFriendInfoState(FriendBox::UserState state);

    /**
     * Notification for incoming call
     * @param response
     * @return
     */
    bool callNotification(Common::Response response);

    /**
     * end call callback
     * @param response
     * @return
     */
    bool endCall(Common::Response response);

    /**
     * infos for call callback
     * @param response
     * @return
     */
    bool infosCall(Common::Response response);

private slots:
    void acceptCall();
    void refuseCall();

private:
    void initFriendList();
    void initUser();
    void initFriendInfo();
    void initCall();
    void initNotif();
    std::vector<std::string> split(std::string str, std::string token);

//    void notifCall();

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
    UserBox *_userBox;
    FriendInfo *_friendInfo;
    UserGUI *_user;
    CallGUI *_call;
    GUIController *_guiController;
    QLineEdit *notif;
    QPushButton *accept_button;
    QPushButton *refuse_button;
    std::string _name;
    std::string _ip;
    std::string _port;
    QPropertyAnimation *anim;
};

#endif //BABEL_MAINSCENE_HPP
