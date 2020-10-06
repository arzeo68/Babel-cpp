//
// Created by clementschmitte on 30/09/2020.
//

#ifndef BABEL_FRIENDBOX_HPP
#define BABEL_FRIENDBOX_HPP


#include <QtWidgets/QLabel>
#include "Container.hpp"

class MainScene;
class FriendBox : public Container
{
    Q_OBJECT
public:
    typedef enum {
        CONNECTED,
        DISCONNECTED,
        OCCUPIED
    } UserState;

    explicit FriendBox(MainScene *scene, QString name, FriendBox::UserState state, Qt::Alignment alignment = Qt::AlignLeft);
    QString getName();
    QString getDesc();
    UserState getState();

protected:
    QString _name;
    QString _desc;
    QLabel *_label;
    QGroupBox *_box;
    UserState _state;
    MainScene *_scene;

    void setState();
    void mousePressEvent(QMouseEvent *event) override;

private:
};


#endif //BABEL_FRIENDBOX_HPP
