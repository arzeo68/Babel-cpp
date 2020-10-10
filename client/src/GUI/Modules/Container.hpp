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
    Container(QBoxLayout *layout = new QVBoxLayout, Qt::Alignment alignment1 = Qt::AlignVCenter, Qt::Alignment alignment2 = Qt::AlignHCenter);
    QWidget *addWidget(QWidget *widget, Qt::Alignment alignment = Qt::AlignLeft);
    QLayoutItem *addItem(QLayoutItem *item, Qt::Alignment alignment = Qt::AlignLeft);

private:
    std::vector<QWidget *> _listWidget;
    std::vector<QLayoutItem *> _listItem;
protected:
    QBoxLayout *_layout;
};


#endif //BABEL_CONTAINER_HPP
