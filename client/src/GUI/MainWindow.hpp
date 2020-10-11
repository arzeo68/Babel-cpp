//
// Created by clementschmitte on 24/09/2020.
//

#ifndef BABEL_MAINWINDOW_HPP
#define BABEL_MAINWINDOW_HPP

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtCore/QPropertyAnimation>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QStackedWidget>
#include "client/src/GUI/Scenes/SceneManager.hpp"

namespace Ui {
    class MainWindow;
}

class GUIController;
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    ~MainWindow() = default;
    /**
     * Basic constructor for MainWindow
     * @param guiController
     */
    explicit MainWindow(GUIController *guiController);

    /**
     * set current Scene
     * @param name
     * @param user
     */
    void setScene(std::string name, UserGUI *user);

    /**
     * Basic getter
     * @return
     */
    SceneManager &getSceneManager();

    /**
     * Basic getter
     * @return
     */
    uint16_t getID();

public slots:

private slots:

private:
    SceneManager _sceneManager;
    uint16_t _userID;
    GUIController *_guiController;
};


#endif //BABEL_MAINWINDOW_HPP
