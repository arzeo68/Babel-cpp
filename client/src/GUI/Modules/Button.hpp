//
// Created by clementschmitte on 28/09/2020.
//

#ifndef BABEL_BUTTON_HPP
#define BABEL_BUTTON_HPP


#include <QtWidgets/QPushButton>

/**
 * Encapsulation of QPushButton
 */
class Button : public QPushButton
{
public:
    /**
     * Constructor for Button
     * @param name
     * @param size
     */
    Button(QString name, QSize size);
};


#endif //BABEL_BUTTON_HPP
