//
// Created by clementschmitte on 30/09/2020.
//

#ifndef BABEL_FRIENDBOX_HPP
#define BABEL_FRIENDBOX_HPP


#include <QtWidgets/QLabel>
#include "Container.hpp"
#include "Button.hpp"

class MainScene;
class FriendBox : public Container
{
    Q_OBJECT
public:
    typedef enum : int {
        DISCONNECTED = 0,
        CONNECTED,
        OCCUPIED,
    } UserState;


    explicit FriendBox(MainScene *scene, QString name, FriendBox::UserState state, int statePending = 1, Qt::Alignment alignment = Qt::AlignLeft);
    QString getName();
    QString getDesc();
    UserState getState();

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

};


#endif //BABEL_FRIENDBOX_HPP
