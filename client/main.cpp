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
    if (argc == 1) {
        std::cerr << "./babel_client [SERVER_IP]" << std::endl << "Example: ./babel_client 127.0.0.1" << std::endl;
        return 84;
    }
    QApplication app(argc, argv);

    GUIController guiController(argv[1]);
    guiController.run();
    return app.exec();
}
