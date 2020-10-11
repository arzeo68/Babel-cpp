//
// Created by clementschmitte on 28/09/2020.
//

#include "Button.hpp"

Button::Button(QString name, QSize size)
{
    setText(name);
    setFixedSize(size);
}
