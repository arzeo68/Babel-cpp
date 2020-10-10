//
// Created by clementschmitte on 28/09/2020.
//

#include "Container.hpp"

Container::Container(QBoxLayout *layout, Qt::Alignment alignment1, Qt::Alignment alignment2) {
    _layout = layout;
    _layout->setAlignment(alignment1 | alignment2);
    setLayout(layout);
}

QWidget *Container::addWidget(QWidget *widget, Qt::Alignment alignment) {
    setAlignment(alignment);
    _layout->addWidget(widget);
    _listWidget.push_back(widget);
    return (widget);
}

QLayoutItem *Container::addItem(QLayoutItem *item, Qt::Alignment alignment) {
    setAlignment(alignment);
    _layout->addItem(item);
    _listItem.push_back(item);
    return (item);
}
