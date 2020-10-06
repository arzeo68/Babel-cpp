//
// Created by clementschmitte on 25/09/2020.
//

#include "LoginScene.hpp"
#include <QDebug>
#include <iostream>


LoginScene::LoginScene(MainWindow *parent)
    :   _buttons({std::make_unique<Button>("Submit", QSize(80, 50)),
                  std::make_unique<Button>("Reset", QSize(80, 50))}),
        _inputs({std::make_unique<InputText>("Username", 20),
                 std::make_unique<InputText>("Password", 20),
                 std::make_unique<InputText>("Confirm Password", 20)}),
        _containers({new Container(), new Container(new QHBoxLayout(), Qt::AlignHCenter)}),
        _parent(parent),
        _info(new QLabel)
{
    _inputs.at(IN_PASS)->setEchoMode(QLineEdit::Password);
    _inputs.at(IN_CONF_PASS)->setEchoMode(QLineEdit::Password);
    _inputs.at(IN_PASS)->hide();
    _inputs.at(IN_CONF_PASS)->hide();

    _state = STATE_USER;
    _info.setText("");
    _layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    _info.setStyleSheet("QLabel {color : green; }");



    initWidgets();
    initConnect();
    std::cout << "Login Scene" << std::endl;
}

void LoginScene::initWidgets()
{
    QSpacerItem *spacer = new QSpacerItem(_parent->size().width() / 2 - 150,
                                          _parent->size().height() / 2 - 150);

    _containers.at(CONT_INPUT)->addWidget(_inputs.at(IN_USERNAME).get());
    _containers.at(CONT_INPUT)->addWidget(_inputs.at(IN_PASS).get());
    _containers.at(CONT_INPUT)->addWidget(_inputs.at(IN_CONF_PASS).get());
    _containers.at(CONT_INPUT_BTS)->addWidget(_buttons.at(BT_SUBMIT).get(), Qt::AlignCenter);
    _containers.at(CONT_INPUT_BTS)->addWidget(_buttons.at(BT_RESET).get(), Qt::AlignCenter);
    _containers.at(CONT_INPUT)->addWidget(_containers.at(CONT_INPUT_BTS ), Qt::AlignCenter);
    _containers.at(CONT_INPUT)->addWidget(&_info);
    _layout->addWidget(_containers.at(CONT_INPUT), 1, 1);
    _layout->addItem(spacer, 0, 0);
    _layout->addItem(spacer, 0, 2);

    _buttons.at(BT_RESET)->hide();

    setLayout(_layout);
}

void LoginScene::initConnect() {
    connect(_buttons.at(BT_SUBMIT).get(), SIGNAL(clicked()), this, SLOT(submitLogin()));
    connect(_buttons.at(BT_RESET).get(), SIGNAL(clicked()), this, SLOT(resetLogin()));
}

void LoginScene::submitLogin() {
    std::cout << "SubmitLogin" << std::endl;
    if (_state == STATE_USER) {

        // test with username: Clément
        if (_inputs.at(IN_USERNAME)->text() == "Clément") {
            _info.setStyleSheet("QLabel {color : green; }");
            _inputs.at(IN_PASS)->show();
            _inputs.at(IN_CONF_PASS)->show();
            _buttons.at(BT_RESET)->show();
            QString welcome = "Hello ";
            welcome.append(_inputs.at(IN_USERNAME)->text());
            welcome.append(", you're new there.");
            _info.setText(welcome);
            _state = STATE_NOREG;
        }

        if (_inputs.at(IN_USERNAME)->text() == "JG") {
            _info.setStyleSheet("QLabel {color : green; }");
            _inputs.at(IN_PASS)->show();
            _buttons.at(BT_RESET)->show();
            QString welcome = "Welcome back, ";
            welcome.append(_inputs.at(IN_USERNAME)->text());
            _info.setText(welcome);
            _state = STATE_REG;
        }

        // call to API to know if user is register or not
        /*

        if (user is register)
            _inputs.at(IN_PASS)->show();
        else if (user is not register) {
            _inputs.at(IN_PASS)->show();
            _inputs.at(IN_CONF_PASS)->show()
        }

        */
    } else if (_state == STATE_REG) {
        if (_inputs.at(IN_PASS)->text() == "test")
            _parent->setScene("main");
        else {
            _info.setStyleSheet("QLabel {color : red; }");
            _info.setText("Wrong password");
            _inputs.at(IN_PASS)->setText("");
        }
    } else {
        if (_inputs.at(IN_PASS)->text().length() >= 8) {
            if (_inputs.at(IN_PASS)->text() == _inputs.at(IN_CONF_PASS)->text())
                _parent->setScene("main");
            else {
                _info.setStyleSheet("QLabel {color : red; }");
                _info.setText("Passwords must match !");
                _inputs.at(IN_PASS)->setText("");
                _inputs.at(IN_CONF_PASS)->setText("");
            }
        } else {
            _info.setStyleSheet("QLabel {color : red; }");
            _info.setText("Password needs 8 or more characters");
            _inputs.at(IN_PASS)->setText("");
            _inputs.at(IN_CONF_PASS)->setText("");
        }
    }
}

void LoginScene::resetLogin() {
    _inputs.at(IN_USERNAME)->setText("");
    _inputs.at(IN_PASS)->setText("");
    _inputs.at(IN_CONF_PASS)->setText("");
    _info.setText("");

    _inputs.at(IN_PASS)->hide();
    _inputs.at(IN_CONF_PASS)->hide();
    _buttons.at(BT_RESET)->hide();

    _state = STATE_USER;
}
