//
// Created by clementschmitte on 25/09/2020.
//

#ifndef BABEL_LOGINSCENE_HPP
#define BABEL_LOGINSCENE_HPP

#include <client/src/GUI/MainWindow.hpp>
#include <QtWidgets/QGroupBox>
#include <client/src/GUI/Modules/Button.hpp>
#include <client/src/GUI/Modules/Container.hpp>
#include <client/src/GUI/Modules/InputText.hpp>
#include <QtWidgets/QLabel>
#include <common/TCP/CommonPackages.hpp>


class LoginScene : public AScene
{
    Q_OBJECT

public:
    ~LoginScene() = default;
    explicit LoginScene(MainWindow *parent = Q_NULLPTR);

    bool userExist(Common::Response response);

    bool userLogin(Common::Response response);

private slots:
    void submitLogin();
    void resetLogin();

private:
    void initWidgets();
    void initConnect();

    enum InputList {
        IN_USERNAME,
        IN_PASS,
        IN_CONF_PASS
    };

    enum ContainerList {
        CONT_INPUT,
        CONT_INPUT_BTS
    };

    enum ButtonList {
        BT_SUBMIT,
        BT_RESET
    };
public:
    void initScene(UserGUI user) override;

private:

    typedef enum {
        STATE_USER,
        STATE_REG,
        STATE_NOREG
    } LoginState;

    std::array<std::unique_ptr<Button>, 2> _buttons;
    std::array<std::unique_ptr<InputText>, 3> _inputs;
    std::array<Container *, 2> _containers;
    QLabel _info;
    MainWindow *_parent;
    LoginState _state;
};


#endif //BABEL_LOGINSCENE_HPP
