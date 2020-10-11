//
// Created by clementschmitte on 28/09/2020.
//

#ifndef BABEL_INPUTTEXT_HPP
#define BABEL_INPUTTEXT_HPP


#include <QtWidgets/QLineEdit>

class InputText : public QLineEdit
{
public:
    /**
     * Basic constructor for InputText
     * @param text
     * @param size
     */
    InputText(QString text, int size);
};


#endif //BABEL_INPUTTEXT_HPP
