//
// Created by clementschmitte on 28/09/2020.
//

#include "AScene.hpp"

AScene::AScene()
    : _layout(new QGridLayout())
{
    _layout->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    setLayout(_layout);
}