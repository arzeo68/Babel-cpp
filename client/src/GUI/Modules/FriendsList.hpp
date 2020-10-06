//
// Created by clementschmitte on 02/10/2020.
//

#ifndef BABEL_FRIENDSLIST_HPP
#define BABEL_FRIENDSLIST_HPP


#include "Container.hpp"

class MainScene;
class FriendsList : public Container
{
public:
    FriendsList(MainScene *scene);

private:
    MainScene *_scene;
};


#endif //BABEL_FRIENDSLIST_HPP
