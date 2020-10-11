//
// Created by clementschmitte on 28/09/2020.
//

#ifndef BABEL_ASCENE_HPP
#define BABEL_ASCENE_HPP

#include <QWidget>
#include <QtWidgets/QGridLayout>
#include <client/src/GUI/Modules/UserGUI.hpp>

class AScene : public QWidget
{
    Q_OBJECT
public:
    /**
     * Constructor for AScene
     */
    AScene();

    /**
     * Destructor for AScene
     */
    virtual ~AScene();

    /**
     * initScene for init widget
     * @param user
     */
    virtual void initScene(UserGUI *user) = 0;

protected:
    std::shared_ptr<QGridLayout> _layout;
};


#endif //BABEL_ASCENE_HPP
