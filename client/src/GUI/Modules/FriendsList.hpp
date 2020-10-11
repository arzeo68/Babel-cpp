//
// Created by clementschmitte on 02/10/2020.
//

#ifndef BABEL_FRIENDSLIST_HPP
#define BABEL_FRIENDSLIST_HPP


#include <common/TCP/CommonPackages.hpp>
#include <client/src/GUI/GUIController/GUIController.hpp>
#include "Container.hpp"
#include "UserGUI.hpp"
#include "FriendBox.hpp"
#include "InputText.hpp"

class MainScene;
class FriendsList : public Container
{
    Q_OBJECT
public:
    /**
     * Constructor for FriendsList
     * @param scene
     * @param user
     * @param guiController
     * @param friends
     */
    FriendsList(MainScene *scene, UserGUI *user, GUIController *guiController, std::map<std::string, FriendBox *> friends);

    /**
     * Basic getter
     * @return
     */
    std::map<std::string, FriendBox *> &getFriends();

    /**
     * Notification friend list
     * @param response
     * @return
     */
    bool fillFriendsList(Common::Response response);

    /**
     * Put Friend callback
     * @param response
     * @return
     */
    bool fillFriend(Common::Response response);

    /**
     * Delete Friend callback
     * @param response
     * @return
     */
    bool deleteFriend(Common::Response response);

    /**
     * Notification friend request
     * @param response
     * @return
     */
    bool requestFriend(Common::Response response);

    /**
     * Notification status
     * @param response
     * @return
     */
    bool statusFriend(Common::Response response);

    /**
     * Notification Delete Friend
     * @param response
     * @return
     */
    bool deleteFriendNotif(Common::Response response);

    /**
     * Post Friend callback
     * @param response
     * @return
     */
    bool responseRequest(Common::Response response);

    /**
     * Friend is connected callback
     * @param response
     * @return
     */
    bool friendIsConnected(Common::Response response);

    /**
     * Notification friend status
     * @param response
     * @return
     */
    bool responseRequestFriend(Common::Response response);

    /**
     * Notification call connect
     * @param response
     * @return
     */
    bool friendConnectedNotif(Common::Response response);

    /**
     * Notification call disconnect
     * @param response
     * @return
     */
    bool friendDisonnectedNotif(Common::Response response);

    /**
     * Notification call busy
     * @param response
     * @return
     */
    bool friendBusyNotif(Common::Response response);

private:
    MainScene *_scene;
    UserGUI *_user;
    std::vector<std::string> _friendsNames;
    QList<FriendBox *> _friend;
    std::map<std::string, FriendBox *> _friends;
    Container *_overlay;
    InputText *_friendAdd;
    QLabel *_response;
    Button *_submitFriendAdd;
    GUIController *_guiController;

private slots:
    void addNewFriend();
    bool deleteFriend(std::string name);

    void initList(std::map<std::string, FriendBox *> friends);
};


#endif //BABEL_FRIENDSLIST_HPP
