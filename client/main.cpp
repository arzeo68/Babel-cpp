#include <iostream>
#include "src/Audio/portAudio/PortAudio.hpp"
#include "src/Audio/Opus/Opus.hpp"
#include <QApplication>
#include <QPushButton>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QDesktopWidget>
#include <client/src/GUI/MainWindow.hpp>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QButtonGroup>
#include <zconf.h>
#include <QtCore/QTimer>
#include <client/src/GUI/GUIController/GUIController.hpp>


int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    GUIController guiController;
    Common::Response msg;
    msg.code = Common::HTTPCodes_e::HTTP_OK;
    strncpy(msg.msg, "FRIEND|REQUEST|TestTestTest", Common::g_maxMessageLength);
    guiController.handleNotifications(msg);
    guiController.run();
    return app.exec();
}
