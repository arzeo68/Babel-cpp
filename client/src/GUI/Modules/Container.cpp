//
// Created by clementschmitte on 28/09/2020.
//

#include "Container.hpp"

Container::Container(QBoxLayout *layout) {
    _layout = layout;
    _layout->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    setLayout(layout);
}

QWidget *Container::addWidget(QWidget *widget, Qt::Alignment alignment) {
    setAlignment(alignment);
    _layout->addWidget(widget);
    _list.push_back(widget);
    return (widget);
}
