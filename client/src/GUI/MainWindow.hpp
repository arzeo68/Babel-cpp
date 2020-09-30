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

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    void setScene(std::string name);

public slots:

private slots:

private:
    SceneManager _sceneManager;
};


#endif //BABEL_MAINWINDOW_HPP
