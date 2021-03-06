//
// Created by clementschmitte on 30/09/2020.
//

#ifndef BABEL_FRIENDBOX_HPP
#define BABEL_FRIENDBOX_HPP

#include <array>
#include <QtWidgets/QLabel>
#include <client/src/GUI/GUIController/GUIController.hpp>
#include "Container.hpp"
#include "Button.hpp"
#include "UserGUI.hpp"

class MainScene;
class FriendBox : public Container
{
    Q_OBJECT
public:
    /**
     * Userstate for interface color
     */
    typedef enum : int {
        DISCONNECTED = 0,
        CONNECTED,
        OCCUPIED,
    } UserState;

    /**
     * Constructor for FriendBox
     * @param guiController
     * @param _user
     * @param scene
     * @param name
     * @param state
     * @param statePending
     * @param alignment
     */
    explicit FriendBox(GUIController *guiController, UserGUI *_user, MainScene *scene, QString name, FriendBox::UserState state, int statePending = 1, Qt::Alignment alignment = Qt::AlignLeft);

    /**
     * Basic getter
     * @return
     */
    QString getName();

    /**
     * Basic getter
     * @return
     */
    QString getDesc();

    /**
     * Basic getter
     * @return
     */
    UserState getState();

    /**
     * Basic setter
     * @param state
     */
    void setState(UserState state);

    /**
     * Basic setter
     * @param state
     */
    void setPendingState(int state);

protected:
    enum StatePending {
        STATE_PENDING_SENDER,
        STATE_PENDING_RECEIVER,
        STATE_FRIEND
    };

    enum ButtonList {
        BT_ACCEPT,
        BT_REFUSE
    };

    GUIController *_guiController;
    UserGUI *_user;
    QString _name;
    QString _desc;
    QLabel *_label;
    QGroupBox *_box;
    std::array<std::unique_ptr<Button>, 2> _buttons;
    UserState _state;
    MainScene *_scene;
    int _statePending;

    void setState();
    void mousePressEvent(QMouseEvent *event) override;

private slots:
    void acceptFriend();
    void refuseFriend();

};


#endif //BABEL_FRIENDBOX_HPP
