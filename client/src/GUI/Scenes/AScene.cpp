//
// Created by clementschmitte on 28/09/2020.
//

#include "AScene.hpp"
#include <qdebug.h>

AScene::AScene()
    : _layout(new QGridLayout())
{
    _layout->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    setLayout(_layout.get());
}

AScene::~AScene() {
    QLayoutItem *item;
    while ((item = _layout->takeAt(0)) != 0)
            _layout->removeItem (item);
}
