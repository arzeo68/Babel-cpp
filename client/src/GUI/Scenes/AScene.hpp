//
// Created by clementschmitte on 28/09/2020.
//

#ifndef BABEL_ASCENE_HPP
#define BABEL_ASCENE_HPP

#include <QWidget>
#include <QtWidgets/QGridLayout>

class AScene : public QWidget
{
    Q_OBJECT
public:
    AScene();

protected:
    QGridLayout *_layout;
};


#endif //BABEL_ASCENE_HPP
