#include <iostream>
#include <QtWidgets/QApplication>
#include "client/src/GUI/GUIController/GUIController.hpp"


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
