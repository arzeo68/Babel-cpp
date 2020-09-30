//
// Created by clementschmitte on 28/09/2020.
//

#ifndef BABEL_CONTAINER_HPP
#define BABEL_CONTAINER_HPP


#include <QtWidgets/QGroupBox>
#include <QtWidgets/QBoxLayout>

class Container : public QGroupBox
{
public:
    Container(QBoxLayout *layout = new QVBoxLayout);
    QWidget *addWidget(QWidget *widget, Qt::Alignment alignment = Qt::AlignLeft);

private:
    QBoxLayout *_layout;
    std::vector<QWidget *> _list;
};


#endif //BABEL_CONTAINER_HPP
