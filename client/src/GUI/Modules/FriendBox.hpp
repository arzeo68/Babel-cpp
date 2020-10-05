//
// Created by clementschmitte on 30/09/2020.
//

#ifndef BABEL_FRIENDBOX_HPP
#define BABEL_FRIENDBOX_HPP


#include <QtWidgets/QLabel>
#include "Container.hpp"

class FriendBox : public Container
{
    Q_OBJECT
public:
    typedef enum {
        CONNECTED,
        DISCONNECTED,
        OCCUPIED
    } UserState;

    explicit FriendBox(QString name, FriendBox::UserState state, Qt::Alignment alignment = Qt::AlignLeft);

protected:
    QString _name;
    QLabel *_label;
    QGroupBox *_box;
    UserState _state;

    void setState();
    void mousePressEvent(QMouseEvent *event) override;

private:

};


#endif //BABEL_FRIENDBOX_HPP
