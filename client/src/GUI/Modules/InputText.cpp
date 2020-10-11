//
// Created by clementschmitte on 28/09/2020.
//

#include "InputText.hpp"

InputText::InputText(QString text, int size)
{
    setPlaceholderText(text);
    setAlignment(Qt::AlignHCenter);
    auto tmp = QStringLiteral("QLineEdit {"
                              "margin: 10px;"
                              "border-radius: 15px;"
                              "min-width:%1px;"
                              "min-height:30px;}").arg(size);
}
