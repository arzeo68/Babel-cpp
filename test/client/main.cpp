#include <iostream>
#include "portAudio/PortAudio.hpp"
#include "Opus/Opus.hpp"
#include <QApplication>
#include <QPushButton>


int main(int argc, char **argv)
{
    std::cout << "Hello, World!" << std::endl;
    Opus p;
    PortAudio m;
    QApplication app (argc, argv);

    QPushButton button ("Hello world !");
    button.show();

    return app.exec();
}
